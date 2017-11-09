（1）在项目文件 [app_name]-Prefix.pch（通常在文件夹「Support Files」中）或者main.m 文件中，引入 OneAPM 头文件：

import <OneAPM/OneAPM.h>

（2）在 main.m 文件的 main 函数中添加如下代码:

int main(int argc, char * argv[]) {
    @autoreleasepool {
    
       [OneAPM setPrintLog:YES];
       [OneAPM startWithApplicationToken:@" <use app token>"];
         
        return UIApplicationMain(argc, argv, nil, NSStringFromClass([AppDelegate class]));
    }
}

为了更好的展示用户访问信息，开发者可以在 SDK 启动代码前通过 setUserName 来自定义设置用户的信息，代码示例：
int main(int argc, char * argv[]) {
    @autoreleasepool {
    
        [OneAPM setPrintLog:YES];
        [OneAPM setUserName:@"phonenum"];
        [OneAPM startWithApplicationToken:@" <use app token>"];
         
        return UIApplicationMain(argc, argv, nil, NSStringFromClass([AppDelegate class]));
    }
}
注意：
 1. setUserName 信息用户可自定义，常见配置邮箱、电话等
 2.如未设置该项，用户信息默认展示 DeviceID
>

