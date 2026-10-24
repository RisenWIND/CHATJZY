#include "WeChatPlatformJZY.h"
#include <iostream>

WeChatPlatformJZY::WeChatPlatformJZY() {
    setPlatformName("微信");
}

WeChatPlatformJZY::~WeChatPlatformJZY() {}

void WeChatPlatformJZY::registerAccount() {
    std::cout << "微信注册成功\n";
}

void WeChatPlatformJZY::loginAccount() {
    std::cout << "微信登录成功\n";
    setLogin(true);
}

void WeChatPlatformJZY::bindAccount() {
    std::cout << "微信绑定账号\n";
}

void WeChatPlatformJZY::showInfo() {
    std::cout << "当前平台：微信\n";
}
