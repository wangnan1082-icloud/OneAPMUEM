
Pod::Spec.new do |s|


  s.name         = "OneAPMUEM"
  s.version      = "5.4.1.4"
  s.summary      = "OneAPM UEM lib for iOS."

  s.description  = <<-DESC
                   OneAPM UEM lib for iOS, supports armv7 armv7s i386 x86_64 arm64.

                   DESC

  s.homepage     = "https://www.oneapm.com"


  s.license      = "MIT"

  s.author             = { "王文照" => "wangwenzhao@oneapm.com" }

  s.platform     = :ios, "7.0"
  s.requires_arc     = true


  s.source       = { :git => "https://github.com/wwzAwen/OneAPMUEM.git", :tag => s.version.to_s }

  s.vendored_framework = 'OneAPMUEM.framework'
  s.frameworks         = 'SystemConfiguration', 'CoreTelephony'
  s.libraries          = "z", "c++"

end
