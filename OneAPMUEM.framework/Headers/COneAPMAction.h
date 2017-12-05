//
//  COneAPMAction.h
//  nbl_agent_ios
//
//  Created by Li Sai on 5/7/2017.
//  Copyright © 2017 OneAPM. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef enum : NSUInteger {
    COneAPMAction_OK = 0,
    COneAPMAction_UEM_Off,
    COneAPMAction_Invalid_Param,
    COneAPMAction_NotFound
} COneAPMAction_StatusCode;

@interface COneAPMAction : NSObject

/*
 @brief 生成一个有耗时时长的用户自定义动作
 
 生成的用户自定义动作会根据动作的开始时间显示在用户操作轨迹中。动作开始时调用类方法 enterActionInView:actionName: 开始计时并返回实例，动作结束时调用实例方法 endAction  停止计时。
 
 @param viewName 动作发生的界面
 
 @param actionName 动作名称
 
 @return 返回用户自定义动作的实例，如果发生错误则返回 nil
 */
+ (instancetype _Nullable)enterActionInView:( NSString * _Nullable)viewName
                                 actionName:( NSString * _Nonnull)actionName;

/*
 @brief 结束一个有耗时时长的用户自定义动作并计算动作的耗时
 
 @return COneAPMAction_StatusCode 返回操作成功或者失败的状态码
 */
- (COneAPMAction_StatusCode)endAction;

/*
 @brief 创建一个可以添加说明信息的用户自定义动作
 
 调用 createActionInView:actionName 创建并返回动作实例，用户可以 reportValue:intValue: 等实例方法添加说明信息
 
 @param viewName 动作发生的界面
 
 @param actionName 动作名称
 
 @return 返回用户自定义动作的实例，如果发生错误则返回 nil
 */
+ (instancetype _Nullable)createActionInView:(NSString * _Nullable)viewName
                                  actionName:(NSString * _Nonnull)actionName;

/*
 @brief 为用户自定义动作添加说明信息
 
 为通过调用类方法 createActionInView:actionName 创建的动作添加说明信息
 
 @param valueName 说明信息的名称
 
 @param value int 类型 说明信息的值
 
 @return COneAPMAction_StatusCode 返回操作成功或者失败的状态码
 */
- (COneAPMAction_StatusCode)reportValue:(NSString * _Nonnull)valueName
                               intValue:(int)value;

/*
 @brief 为用户自定义动作添加说明信息
 
 为通过调用类方法 createActionInView:actionName 创建的动作添加说明信息
 
 @param valueName 说明信息的名称
 
 @param value double 类型 说明信息的值
 
 @return COneAPMAction_StatusCode 返回操作成功或者失败的状态码
 */
- (COneAPMAction_StatusCode)reportValue:(NSString * _Nonnull)valueName
                            doubleValue:(double)value;

/*
 @brief 为用户自定义动作添加说明信息
 
 为通过调用类方法 createActionInView:actionName 创建的动作添加说明信息
 
 @param valueName 说明信息的名称
 
 @param value NSString 类型 说明信息的值
 
 @return COneAPMAction_StatusCode 返回操作成功或者失败的状态码
 */
- (COneAPMAction_StatusCode)reportValue:(NSString * _Nonnull)valueName
                            stringValue:(NSString * _Nonnull)value;

/*
 @brief 为用户自定义动作添加错误信息
 
 为通过调用类方法 createActionInView:actionName 或 enterActionInView:actionName: 创建的动作添加错误信息
 
 @param errorName 错误信息的名称
 
 @param value NSString 类型 错误信息
 
 @return COneAPMAction_StatusCode 返回操作成功或者失败的状态码
 */
- (COneAPMAction_StatusCode)reportError:(NSString * _Nonnull)errorName
                           errorMessage:(NSString * _Nonnull)error;

/*
 @brief 上报错误信息
 
上报一个不与用户自定义动作相关联的错误信息
 
 @param errorName 错误信息的名称
 
 @param value NSString 类型 错误信息
 
 @return COneAPMAction_StatusCode 返回操作成功或者失败的状态码
 */
+ (COneAPMAction_StatusCode)reportError:(NSString * _Nonnull)errorName
                           errorMessage:(NSString * _Nonnull)error;

@end
