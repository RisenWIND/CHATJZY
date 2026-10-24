#include "WeiboPlatformJZY.h"
#include <iostream>

WeiboPlatformJZY::WeiboPlatformJZY() {
    setPlatformName("微博");
}

WeiboPlatformJZY::~WeiboPlatformJZY() {}

void WeiboPlatformJZY::registerAccount() {
    std::cout << "微博注册成功\n";
}

void WeiboPlatformJZY::loginAccount() {
    std::cout << "微博登录成功\n";
    setLogin(true);
}

void WeiboPlatformJZY::bindAccount() {
    std::cout << "微博绑定账号\n";
}

void WeiboPlatformJZY::showInfo() {
    std::cout << "当前平台：微博\n";
}
