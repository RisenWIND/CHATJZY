#include "SystemUIJZY.h"
#include <iostream>

SystemUIJZY::SystemUIJZY() {}
SystemUIJZY::~SystemUIJZY() {}

void SystemUIJZY::run() {
    while (true) {
        showMainMenu();
        int choice = 0;
        std::cin >> choice;

        switch (choice) {
            case 1:
                showRegisterMenu();
                break;
            case 2:
                showLoginMenu();
                break;
            case 3:
                std::cout << "退出系统\n";
                return;
            default:
                std::cout << "输入有误，请重新选择\n";
                break;
        }
    }
}

void SystemUIJZY::showMainMenu() {
    std::cout << "\n=== 即时通信平台 ===\n";
    std::cout << "1. 注册\n";
    std::cout << "2. 登录\n";
    std::cout << "3. 退出\n";
    std::cout << "请选择：";
}

void SystemUIJZY::showRegisterMenu() {
    std::cout << "进入注册界面\n";
}

void SystemUIJZY::showLoginMenu() {
    std::cout << "进入登录界面\n";
}

void SystemUIJZY::showPlatformMenu() {
    std::cout << "进入平台选择界面\n";
}
