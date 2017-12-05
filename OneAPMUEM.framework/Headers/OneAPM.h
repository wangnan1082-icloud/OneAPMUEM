//
//  OneAPM.h
//  nbl_agent_ios
//
//  Created by 6Spring on 2016/10/17.
//  Copyright © 2016年 OneAPM. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface OneAPM : NSObject

/**
 启动 OneAPM，当前版本 5.3.0.1
 
 @param token OneAPM 的授权码
 */
+ (void)startWithApplicationToken:(NSString *)token;

+ (void)setUserName:(NSString *)userName;

+ (void)setSearchKey:(NSString *)searchKey;

+ (void)setCustomInfo:(NSDictionary *)extra;

+ (NSString *)getSDKVersion;

/**
 是否在控制台上显示 OneAPM 的日志

 @param isPrintLog YES: 显示  NO: 不显示
 */
+ (void)setPrintLog:(BOOL)isPrintLog;

@end


/**
 企业版专用
 */
@interface OneAPM (Enterprise)

/**
 设置 OneAPM 服务器地址
 
 @param host SDK 的服务器地址
 @param withSecurity 与服务器的通信使用 https 协议时该值为 YES，使用 http 协议时改值为 NO。根据苹果的审核要求，推荐使用 https 协议。
 */
+ (void)setHost:(NSString *)host withSecurity:(BOOL)withSecurity;

/**
 设置 OneAPM 服务器地址
 
 @param host SDK 的服务器地址
 @param port SDK 端口地址
 @param withSecurity 与服务器的通信使用 https 协议时该值为 YES，使用 http 协议时改值为 NO。根据苹果的审核要求，推荐使用 https 协议。
 */
+ (void)setHost:(NSString *)host port:(int)port withSecurity:(BOOL)withSecurity;

/**
 OneAPM 上传数据时，禁止压缩数据
 */
+ (void)disableZlib;

@end
