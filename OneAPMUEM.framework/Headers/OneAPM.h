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
 启动 OneAPM，当前版本 5.4.1.0
 
 @param token OneAPM 的授权码
 */
+ (void)startWithApplicationToken:(NSString *)token;

/**
 设置但不持久化 userName
 需要持久化 userName 时，请使用 saveUserName: 方法
 */
+ (void)setUserName:(NSString *)userName;

/**
 设置并持久化 userName, SDK 启动后都使用该 userName 标识当前用户
 @param userName 需要持久化的 userName 值
 */
+ (void)saveUserName:(NSString *)userName;

/**
 删除本地持久化的 userName, 与 saveUserName: 配合使用
 例如，用户退出登录时不再使用之前持久化的 userName 作为登录用户
 */
+ (void)deleteUserName;

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
 * 设置获取地理位置信息的服务器地址
 * @param geoURL 服务器地址
 */
+ (void)setGeoURL:(NSString *)geoURL;

/**
 * 信任 OneAPM 服务器的自签名证书（默认不信任自签名证书）
 */
+ (void)trustAnyCertification;

/**
 OneAPM 上传数据时，禁止压缩数据
 */
+ (void)disableZlib DEPRECATED_ATTRIBUTE;

/**
 * 取消与 AI 打通 (默认打通)。
 */
+ (void)disableAssociateWithAI;

@end
