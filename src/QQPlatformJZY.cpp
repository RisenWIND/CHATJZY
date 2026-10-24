#include "QQPlatformJZY.h"
#include <iostream>

QQPlatformJZY::QQPlatformJZY() {
    setPlatformName("QQ");
}

QQPlatformJZY::~QQPlatformJZY() {}

void QQPlatformJZY::registerAccount() {
    std::cout << "QQ注册成功\n";
}

void QQPlatformJZY::loginAccount() {
    std::cout << "QQ登录成功\n";
    setLogin(true);
}

void QQPlatformJZY::bindAccount() {
    std::cout << "QQ绑定账号\n";
}

void QQPlatformJZY::showInfo() {
    std::cout << "当前平台：QQ\n";
}
