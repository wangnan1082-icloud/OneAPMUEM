#!/bin/bash
#
# Shell script to upload an iOS build's debug symbols to OneAPM.
#
# usage:
# This script needs to be invoked during an XCode build
#
# 1. In XCode, select your project in the navigator, then click on the application target.
# 2. Select the Build Phases tab in the settings editor.
# 3. Click the + icon above Target Dependencies and choose New Run Script Build Phase.
# 4. Add the following two lines of code to the new phase,
#     removing the '#' at the start of each line and pasting in the
#     application token from your OneAPM dashboard for the app in question.
#
#SCRIPT=`/usr/bin/find "${SRCROOT}" -name oneapm_postbuild.sh | head -n 1`
#/bin/sh "${SCRIPT}" "PUT_ONEAPM_APP_TOKEN_HERE"
#
# Optional:
# DSYM_UPLOAD_URL - define this environment variable to override the OneAPM server hostname
# ENABLE_SIMULATOR_DSYM_UPLOAD - enable automatic upload of simulator build symbols
# ENABLE_DEBUG_DSYM_UPLOAD - enable automatic upload of debug build symbols

not_in_xcode_env() {
  echo "OneAPM: $0 must be run from an XCode build"
  exit -2
}

get_app_version() {
  APP_VERSION=`/usr/libexec/PlistBuddy -c 'Print :CFBundleShortVersionString' "$TARGET_BUILD_DIR/$INFOPLIST_PATH"`
  APP_BUILD=`/usr/libexec/PlistBuddy -c 'Print :CFBundleVersion' "$TARGET_BUILD_DIR/$INFOPLIST_PATH"`
}

upload_dsym_archive_to_oneapm() {
  let RETRY_LIMIT=3
  let RETRY_COUNT=0

  if [ ! -f "$DSYM_ARCHIVE_PATH" ]; then
    echo "OneAPM: Failed to archive \"$DSYM_SRC\" to \"$DSYM_ARCHIVE_PATH\""
    exit -3
  fi

  while [ "$RETRY_COUNT" -lt "$RETRY_LIMIT" ]
  do
    let RETRY_COUNT=$RETRY_COUNT+1
    echo "dSYM archive upload attempt #$RETRY_COUNT (of $RETRY_LIMIT)"

    echo "curl --write-out %{http_code} --silent --output /dev/null -F dsymFile=@\"$DSYM_ARCHIVE_PATH\" -F appName=\"$EXECUTABLE_NAME\" -F appVersion=\"$APP_VERSION\" -F appBuild=\"$APP_BUILD\" -F dsymMD5=\"$DSYM_MD5\" -F dsymUUID=\"$DSYM_UUIDS\" -H \"appKey=$API_KEY\" \"$DSYM_UPLOAD_URL\""
    SERVER_RESPONSE=$(curl --write-out %{http_code} --silent --output /dev/null -F dsymFile=@\"$DSYM_ARCHIVE_PATH\" -F appName="$EXECUTABLE_NAME" -F appVersion="$APP_VERSION" -F appBuild="$APP_BUILD" -F dsymMD5="$DSYM_MD5" -F dsymUUID="$DSYM_UUIDS" -H appKey:"$API_KEY" "$DSYM_UPLOAD_URL")

    if [ $SERVER_RESPONSE -eq 200 ]; then
      echo "OneAPM: Successfully uploaded debug symbols"
      break
    else
      if [ $SERVER_RESPONSE -eq 409 ]; then
        echo "OneAPM: dSYM \"$DSYM_UUIDS\" already uploaded"
        break
      else
        echo "OneAPM: ERROR \"$SERVER_RESPONSE\" while uploading \"$DSYM_ARCHIVE_PATH\" to \"$DSYM_UPLOAD_URL\""
      fi
    fi
  done

  /bin/rm -f "$DSYM_ARCHIVE_PATH"
}

if [ ! $1 ]; then
  echo "usage: $0 <ONEAPM_APP_TOKEN>"
  exit -1
fi

if [ ! "$DWARF_DSYM_FOLDER_PATH" -o ! "$DWARF_DSYM_FILE_NAME" -o ! "$INFOPLIST_FILE" -o ! "$TARGET_BUILD_DIR" ]; then
  not_in_xcode_env
fi

if [ "$ENABLE_BITCODE" == "YES" ]; then
  echo "OneAPM: Bitcode enabled. No dSYM has been uploaded."
  exit 0
fi

if [ ! "$DSYM_UPLOAD_URL" ]; then
  DSYM_UPLOAD_URL="https://miv2dc.oneapm.com/mi/dc/v2/symbol_files"
fi

#Check DEBUG_INFORMATION_FORMAT
if [ "$DEBUG_INFORMATION_FORMAT" == "dwarf" ]; then
  echo "OneAPM: No dSYM info. No dSYM has been uploaded."
  exit 0
fi

#save and set IFS to only trigger on \n\b
SAVEIFS=$IFS
IFS=$(echo -en "\n\b")

get_app_version

for dSYM in `ls -d $DWARF_DSYM_FOLDER_PATH/*.dSYM`
do
  API_KEY=$1
  echo processing $dSYM
  DSYM_SRC="$dSYM"

  if [ "$EFFECTIVE_PLATFORM_NAME" == "-iphonesimulator" -a ! "$ENABLE_SIMULATOR_DSYM_UPLOAD" ]; then
    echo "OneAPM: Skipping automatic upload of simulator build symbols"
    exit 0
  fi

  if [ "$CONFIGURATION" == "Debug" -a ! "$ENABLE_DEBUG_DSYM_UPLOAD" ]; then
    echo "OneAPM: Skipping automatic upload of debug build symbols"
    exit 0
  fi

  echo generating dSYM UUIDs
  echo "DSYM_UUIDS='xcrun dwarfdump --uuid "$DSYM_SRC" | awk '{print $3 $2}' | xargs | sed 's/ /,/g' | sed 's/)/\|/g' | sed 's/(//g''"
  DSYM_UUIDS=`xcrun dwarfdump --uuid "$DSYM_SRC" | awk '{print $3 $2}' | xargs | sed 's/ /,/g' | sed 's/)/\|/g' | sed 's/(//g'`
  echo gathered UUID: $DSYM_UUIDS

  # TODO: Add pid/timestamp to tmp file name
  DSYM_TIMESTAMP=`date +%s`
  DSYM_ARCHIVE_PATH="/tmp/${DSYM_SRC##*/}-$DSYM_TIMESTAMP.zip"

  # Loop until upload success or retry limit is exceeded

  echo "OneAPM: Archiving \"$DSYM_SRC\" to \"$DSYM_ARCHIVE_PATH\""
  echo /usr/bin/zip --recurse-paths --quiet "$DSYM_ARCHIVE_PATH" "$DSYM_SRC"
  /usr/bin/zip --recurse-paths --quiet "$DSYM_ARCHIVE_PATH" "$DSYM_SRC"

  echo "DSYM_MD5='md5 \"$DSYM_ARCHIVE_PATH\" | awk '{print \$4}''"
  DSYM_MD5=`md5 "$DSYM_ARCHIVE_PATH" | awk '{print $4}'`

  echo calling : upload_dsym_archive_to_oneapm
  upload_dsym_archive_to_oneapm

done

#revert IFS
IFS=$SAVEIFS

exit 0
