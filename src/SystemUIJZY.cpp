#include "SystemUIJZY.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <sstream>

SystemUIJZY::SystemUIJZY() : loggedIn(false) {
    loadData();
    std::cout << "欢迎使用即时通信模拟平台（JZY版）\n";
}

SystemUIJZY::~SystemUIJZY() {
    saveData();
}

std::string SystemUIJZY::getCurrentTimeString() const {
    time_t now = time(nullptr);
    tm* local = localtime(&now);
    std::ostringstream oss;
    oss << (local->tm_year + 1900) << "-" << std::setw(2) << std::setfill('0') << (local->tm_mon + 1)
        << "-" << std::setw(2) << std::setfill('0') << local->tm_mday;
    return oss.str();
}

void SystemUIJZY::loadData() {
    fileManager.loadAll(users, friends, groups);
}

void SystemUIJZY::saveData() {
    fileManager.saveAll(users, friends, groups);
}

void SystemUIJZY::run() {
    while (true) {
        if (!loggedIn) {
            showMainMenu();
            int choice = 0;
            std::cin >> choice;
            switch (choice) {
                case 1: registerUser(); break;
                case 2: loginUser(); break;
                case 3: std::cout << "系统已退出\n"; return;
                default: std::cout << "输入有误，请重新选择\n"; break;
            }
        } else {
            showPlatformMenu();
            int platformChoice = 0;
            std::cin >> platformChoice;
            if (platformChoice == 0) {
                loggedIn = false;
                currentUser = UserInfoJZY();
                continue;
            }
            std::string platform = getPlatformNameFromChoice(platformChoice);
            if (platform.empty()) {
                std::cout << "无效选择\n";
                continue;
            }
            handlePlatformAction(platform);
        }
    }
}

std::string SystemUIJZY::getPlatformNameFromChoice(int choice) const {
    switch (choice) {
        case 1: return "QQ";
        case 2: return "微信";
        case 3: return "微博";
        case 4: return "绑定管理";
        case 5: return "退出登录";
        default: return "";
    }
}

bool SystemUIJZY::userHasPlatform(const std::string& platformName) const {
    if (platformName == "QQ") return currentUser.isQQOpened();
    if (platformName == "微信") return currentUser.isWeChatOpened();
    if (platformName == "微博") return currentUser.isWeiboOpened();
    return false;
}

void SystemUIJZY::openPlatform(const std::string& platformName) {
    if (platformName == "QQ") currentUser.setQQOpened(true);
    else if (platformName == "微信") currentUser.setWeChatOpened(true);
    else if (platformName == "微博") currentUser.setWeiboOpened(true);
    std::cout << platformName << " 已开通\n";
}

void SystemUIJZY::showMainMenu() {
    std::cout << "\n=== 欢迎使用即时通信模拟平台 ===\n";
    std::cout << "1. 注册\n";
    std::cout << "2. 登录\n";
    std::cout << "3. 退出\n";
    std::cout << "请选择：";
}

void SystemUIJZY::showPlatformMenu() {
    std::cout << "\n=== 平台选择 ===\n";
    std::cout << "1. QQ\n";
    std::cout << "2. 微信\n";
    std::cout << "3. 微博\n";
    std::cout << "4. 绑定管理\n";
    std::cout << "5. 退出登录\n";
    std::cout << "请选择：";
}

void SystemUIJZY::registerUser() {
    UserInfoJZY user;
    std::string id, nick, pw, birthday, location;
    std::cout << "请输入ID：";
    std::cin >> id;
    if (accountManager.userExists(users, id)) {
        std::cout << "ID已被占用，请重新注册\n";
        return;
    }

    std::cout << "请输入昵称：";
    std::cin >> nick;
    std::cout << "请输入密码：";
    std::cin >> pw;
    std::cout << "请输入生日：";
    std::cin >> birthday;
    std::cout << "请输入所在地：";
    std::cin >> location;

    user.setUserID(id);
    user.setNickName(nick);
    user.setPassword(pw);
    user.setBirthday(birthday);
    user.setLocation(location);
    user.setRegistrationTime(getCurrentTimeString());

    std::cout << "请选择开通平台（1.QQ 2.微信 3.微博，输入0跳过）：";
    int platformChoice = 0;
    std::cin >> platformChoice;
    while (platformChoice != 0) {
        std::string platformName;
        if (platformChoice == 1) platformName = "QQ";
        else if (platformChoice == 2) platformName = "微信";
        else if (platformChoice == 3) platformName = "微博";
        else {
            std::cout << "输入有误\n";
            break;
        }
        bindingManager.bindPlatform(user, platformName, false);
        std::cout << "继续开通平台（1.QQ 2.微信 3.微博，输入0结束）：";
        std::cin >> platformChoice;
    }

    if (accountManager.registerUser(users, user)) {
        std::cout << "注册成功\n";
    } else {
        std::cout << "注册失败\n";
    }
}

void SystemUIJZY::loginUser() {
    std::string id, password;
    std::cout << "请输入ID：";
    std::cin >> id;
    std::cout << "请输入密码：";
    std::cin >> password;

    UserInfoJZY tempUser;
    if (accountManager.loginUser(users, id, password, tempUser)) {
        currentUser = tempUser;
        loggedIn = true;
        std::cout << "登录成功，欢迎 " << currentUser.getNickName() << "\n";
        std::cout << "若未绑定其他平台，可在绑定管理中选择绑定\n";
    } else {
        std::cout << "登录失败，ID或密码错误\n";
    }
}

void SystemUIJZY::handlePlatformAction(const std::string& platformName) {
    if (platformName == "退出登录") {
        loggedIn = false;
        currentUser = UserInfoJZY();
        return;
    }

    if (platformName == "绑定管理") {
        showBindingMenu();
        return;
    }

    if (!userHasPlatform(platformName)) {
        std::cout << "当前用户未开通该平台，是否开通？（1.是 2.否）";
        int choose = 0;
        std::cin >> choose;
        if (choose == 1) {
            openPlatform(platformName);
            for (auto& user : users) {
                if (user.getUserID() == currentUser.getUserID()) {
                    user.setCurrentPlatform(platformName);
                    if (platformName == "QQ") user.setQQOpened(true);
                    if (platformName == "微信") user.setWeChatOpened(true);
                    if (platformName == "微博") user.setWeiboOpened(true);
                    break;
                }
            }
        } else {
            return;
        }
    }

    currentUser.setCurrentPlatform(platformName);
    std::cout << "进入 " << platformName << " 平台\n";
    while (true) {
        std::cout << "\n=== " << platformName << " 平台菜单 ===\n";
        std::cout << "1. 个人信息\n";
        std::cout << "2. 好友管理\n";
        std::cout << "3. 群管理\n";
        std::cout << "4. 返回上一级\n";
        std::cout << "请选择：";
        int choice = 0;
        std::cin >> choice;

        switch (choice) {
            case 1: showUserProfileMenu(); break;
            case 2: showFriendMenu(); break;
            case 3: showGroupMenu(); break;
            case 4: return;
            default: std::cout << "输入有误\n"; break;
        }
    }
}

void SystemUIJZY::showUserProfileMenu() {
    std::cout << "\n=== 个人信息 ===\n";
    showCurrentUserInfo();
    std::cout << "1. 编辑个人信息\n";
    std::cout << "2. 返回\n";
    int choice = 0;
    std::cin >> choice;
    if (choice == 1) {
        editCurrentUserInfo();
    }
}

void SystemUIJZY::showCurrentUserInfo() {
    for (auto& user : users) {
        if (user.getUserID() == currentUser.getUserID()) {
            user.showInfo();
            return;
        }
    }
    currentUser.showInfo();
}

void SystemUIJZY::editCurrentUserInfo() {
    for (auto& user : users) {
        if (user.getUserID() == currentUser.getUserID()) {
            std::string newNick, newLocation, newBirthday;
            std::cout << "请输入新昵称（回车保持不变）: ";
            std::cin >> newNick;
            if (!newNick.empty()) user.setNickName(newNick);

            std::cout << "请输入新所在地（回车保持不变）: ";
            std::cin >> newLocation;
            if (!newLocation.empty()) user.setLocation(newLocation);

            std::cout << "请输入新生日（回车保持不变）: ";
            std::cin >> newBirthday;
            if (!newBirthday.empty()) user.setBirthday(newBirthday);

            currentUser = user;
            std::cout << "个人信息已更新\n";
            return;
        }
    }
}

void SystemUIJZY::showFriendMenu() {
    std::cout << "\n=== 好友管理 ===\n";
    std::cout << "1. 好友列表\n";
    std::cout << "2. 添加好友\n";
    std::cout << "3. 查询好友\n";
    std::cout << "4. 返回\n";
    int choice = 0;
    std::cin >> choice;
    switch (choice) {
        case 1: showFriendList(); break;
        case 2: addFriendByID(); break;
        case 3: queryFriend(); break;
        case 4: break;
        default: std::cout << "输入有误\n"; break;
    }
}

void SystemUIJZY::showFriendList() {
    std::vector<FriendInfoJZY> platformFriends;
    for (const auto& friendInfo : friends) {
        if (friendInfo.getPlatform() == currentUser.getCurrentPlatform()) {
            platformFriends.push_back(friendInfo);
        }
    }

    if (platformFriends.empty()) {
        std::cout << "当前平台暂无好友\n";
        return;
    }

    std::cout << "\n=== 好友列表（" << currentUser.getCurrentPlatform() << "）===\n";
    friendManager.printFriends(platformFriends);
    std::cout << "输入好友列表前的序号可编辑：";
    int index = 0;
    std::cin >> index;
    if (index > 0 && index <= static_cast<int>(platformFriends.size())) {
        std::string selectedID = platformFriends[index - 1].getFriendID();
        for (auto& friendInfo : friends) {
            if (friendInfo.getFriendID() == selectedID) {
                friendInfo.showInfo();
                std::cout << "是否删除好友？1是 0否：";
                int del = 0;
                std::cin >> del;
                if (del == 1) {
                    friendManager.deleteFriend(friends, selectedID);
                    std::cout << "删除成功\n";
                }
                break;
            }
        }
    }
}

void SystemUIJZY::addFriendByID() {
    std::string friendID, remark, groupName;
    std::cout << "请输入要添加好友的ID：";
    std::cin >> friendID;
    std::cout << "请输入备注：";
    std::cin >> remark;
    std::cout << "请输入分组：";
    std::cin >> groupName;

    bool exists = false;
    for (const auto& user : users) {
        if (user.getUserID() == friendID) {
            exists = true;
            break;
        }
    }

    if (!exists) {
        std::cout << "该用户不存在\n";
        return;
    }

    FriendInfoJZY friendInfo;
    friendInfo.setFriendID(friendID);
    friendInfo.setNickName(friendID);
    friendInfo.setRemark(remark);
    friendInfo.setGroup(groupName);
    friendInfo.setPlatform(currentUser.getCurrentPlatform());

    if (friendManager.addFriend(friends, friendInfo)) {
        std::cout << "添加好友成功\n";
    } else {
        std::cout << "好友已存在\n";
    }
}

void SystemUIJZY::addFriendByRecommend() {
    std::cout << "推荐好友功能\n";
    showRecommendedFriends(currentUser.getCurrentPlatform());
}

void SystemUIJZY::queryFriend() {
    std::cout << "1. 按ID查询\n2. 按昵称查询\n请选择：";
    int choice = 0;
    std::cin >> choice;
    std::string key;
    if (choice == 1) {
        std::cout << "请输入好友ID：";
        std::cin >> key;
    } else if (choice == 2) {
        std::cout << "请输入好友昵称：";
        std::cin >> key;
    } else {
        std::cout << "输入有误\n";
        return;
    }

    std::vector<FriendInfoJZY> result;
    for (const auto& friendInfo : friends) {
        if (friendInfo.getPlatform() == currentUser.getCurrentPlatform()) {
            if (choice == 1 && friendInfo.getFriendID() == key) result.push_back(friendInfo);
            if (choice == 2 && friendInfo.getNickName() == key) result.push_back(friendInfo);
        }
    }

    if (result.empty()) {
        std::cout << "未找到相关好友\n";
        return;
    }

    std::cout << "查询结果：\n";
    for (size_t i = 0; i < result.size(); ++i) {
        std::cout << i + 1 << ". " << result[i].getFriendID() << " " << result[i].getNickName() << "\n";
    }
}

void SystemUIJZY::editFriend() {
    std::cout << "编辑好友功能占位\n";
}

void SystemUIJZY::showGroupMenu() {
    std::cout << "\n=== 群管理 ===\n";
    std::cout << "1. 群列表\n";
    std::cout << "2. 加入群\n";
    std::cout << "3. 退出群\n";
    std::cout << "4. 查询群成员\n";
    std::cout << "5. 动态切换群管理模式\n";
    std::cout << "6. 返回\n";
    int choice = 0;
    std::cin >> choice;
    switch (choice) {
        case 1: showGroupList(); break;
        case 2: joinGroupByID(); break;
        case 3: quitGroup(); break;
        case 4: showGroupMembers(); break;
        case 5: showGroupDynamicMode(); break;
        case 6: break;
        default: std::cout << "输入有误\n"; break;
    }
}

void SystemUIJZY::showGroupList() {
    std::vector<GroupInfoJZY> platformGroups;
    for (const auto& group : groups) {
        if (group.getPlatform() == currentUser.getCurrentPlatform()) {
            platformGroups.push_back(group);
        }
    }
    if (platformGroups.empty()) {
        std::cout << "当前平台暂无群\n";
        return;
    }
    groupManager.printGroups(platformGroups);
}

void SystemUIJZY::joinGroupByID() {
    std::string groupID;
    std::cout << "请输入要加入的群号：";
    std::cin >> groupID;
    GroupInfoJZY target;
    for (const auto& group : groups) {
        if (group.getGroupID() == groupID) {
            target = group;
            break;
        }
    }

    if (target.getGroupID().empty()) {
        std::cout << "群号不存在\n";
        return;
    }

    if (target.getPlatform() != currentUser.getCurrentPlatform()) {
        std::cout << "当前平台与该群不匹配\n";
        return;
    }

    if (groupManager.joinGroup(groups, groupID, currentUser.getUserID())) {
        std::cout << "加入群成功\n";
    } else {
        std::cout << "加入失败\n";
    }
}

void SystemUIJZY::quitGroup() {
    std::string groupID;
    std::cout << "请输入要退出的群号：";
    std::cin >> groupID;
    if (groupManager.exitGroup(groups, groupID, currentUser.getUserID())) {
        std::cout << "退出群成功\n";
    } else {
        std::cout << "未找到该群或未加入\n";
    }
}

void SystemUIJZY::showGroupMembers() {
    std::string groupID;
    std::cout << "请输入群号：";
    std::cin >> groupID;
    GroupInfoJZY group = groupManager.findGroupByID(groups, groupID);
    if (group.getGroupID().empty()) {
        std::cout << "群不存在\n";
        return;
    }
    std::cout << "群成员：\n";
    groupManager.printMembers(group);
}

void SystemUIJZY::showGroupDynamicMode() {
    std::cout << "\n=== 群管理模式动态切换 ===\n";
    std::cout << "1. QQ群模式\n";
    std::cout << "2. 微信群模式\n";
    std::cout << "3. 微博群模式\n";
    std::cout << "请选择：";
    int choice = 0;
    std::cin >> choice;
    if (choice == 1) std::cout << "QQ群可申请加入、允许临时讨论组、管理员制度\n";
    else if (choice == 2) std::cout << "微信群只能推荐加入、不允许临时讨论组、仅群主特权\n";
    else if (choice == 3) std::cout << "微博群以社交平台为主，采用简化管理模式\n";
    else std::cout << "输入有误\n";
}

void SystemUIJZY::showRecommendedFriends(const std::string& platformName) {
    std::vector<FriendInfoJZY> recs = friendManager.findRecommendedFriends(friends, currentUser.getUserID(), platformName);
    if (recs.empty()) {
        std::cout << "暂无推荐好友\n";
        return;
    }
    for (size_t i = 0; i < recs.size(); ++i) {
        std::cout << i + 1 << ". " << recs[i].getNickName() << "（" << recs[i].getFriendID() << "）\n";
    }
}

void SystemUIJZY::showBindingMenu() {
    std::cout << "\n=== 绑定管理 ===\n";
    std::cout << "1. QQ绑定\n";
    std::cout << "2. 微信绑定\n";
    std::cout << "3. 微博绑定\n";
    std::cout << "4. 返回\n";
    std::cout << "请选择：";
    int choice = 0;
    std::cin >> choice;
    std::string platform = "";
    switch (choice) {
        case 1: platform = "QQ"; break;
        case 2: platform = "微信"; break;
        case 3: platform = "微博"; break;
        case 4: return;
        default: std::cout << "输入有误\n"; return;
    }

    if (bindingManager.isPlatformOpened(currentUser, platform)) {
        std::cout << platform << " 已开通\n";
        return;
    }

    if (bindingManager.bindPlatform(currentUser, platform, false)) {
        std::cout << platform << "绑定成功\n";
        for (auto& user : users) {
            if (user.getUserID() == currentUser.getUserID()) {
                if (platform == "QQ") user.setQQOpened(true);
                if (platform == "微信") user.setWeChatOpened(true);
                if (platform == "微博") user.setWeiboOpened(true);
                break;
            }
        }
    }
}

