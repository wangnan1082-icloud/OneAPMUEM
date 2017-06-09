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
 启动 OneAPM
 
 @param token OneAPM 的授权码
 */
+ (void)startWithApplicationToken:(NSString *)token;

+ (void)setUserName:(NSString *)userName;

+ (void)setSearchKey:(NSString *)searchKey;

+ (void)setCustomInfo:(NSDictionary *)extra;

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
 
 @param host OneAPM 的服务器地址
 */
+ (void)setHost:(NSString *)host;

@end
