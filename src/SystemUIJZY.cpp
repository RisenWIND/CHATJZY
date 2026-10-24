#include "SystemUIJZY.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <sstream>

SystemUIJZY::SystemUIJZY() : loggedIn(false) {
    loadData();
    std::cout << "Welcome to the Instant Messaging Platform (JZY Version)\n";
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
                case 3: std::cout << "System exit.\n"; return;
                default: std::cout << "Invalid input, please try again.\n"; break;
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
                std::cout << "Invalid choice\n";
                continue;
            }
            handlePlatformAction(platform);
        }
    }
}

std::string SystemUIJZY::getPlatformNameFromChoice(int choice) const {
    switch (choice) {
        case 1: return "QQ";
        case 2: return "WeChat";
        case 3: return "Weibo";
        case 4: return "Bind";
        case 5: return "Logout";
        default: return "";
    }
}

bool SystemUIJZY::userHasPlatform(const std::string& platformName) const {
    if (platformName == "QQ") return currentUser.isQQOpened();
    if (platformName == "WeChat") return currentUser.isWeChatOpened();
    if (platformName == "Weibo") return currentUser.isWeiboOpened();
    return false;
}

void SystemUIJZY::openPlatform(const std::string& platformName) {
    if (platformName == "QQ") currentUser.setQQOpened(true);
    else if (platformName == "WeChat") currentUser.setWeChatOpened(true);
    else if (platformName == "Weibo") currentUser.setWeiboOpened(true);
    std::cout << platformName << " is enabled.\n";
}

void SystemUIJZY::showMainMenu() {
    std::cout << "\n=== Instant Messaging Platform ===\n";
    std::cout << "1. Register\n";
    std::cout << "2. Login\n";
    std::cout << "3. Exit\n";
    std::cout << "Choose: ";
}

void SystemUIJZY::showPlatformMenu() {
    std::cout << "\n=== Platform Selection ===\n";
    std::cout << "1. QQ\n";
    std::cout << "2. WeChat\n";
    std::cout << "3. Weibo\n";
    std::cout << "4. Bind Management\n";
    std::cout << "5. Logout\n";
    std::cout << "Choose: ";
}

void SystemUIJZY::registerUser() {
    UserInfoJZY user;
    std::string id, nick, pw, birthday, location;
    std::cout << "Enter ID: ";
    std::cin >> id;
    if (accountManager.userExists(users, id)) {
        std::cout << "ID already exists. Please register again.\n";
        return;
    }

    std::cout << "Enter nickname: ";
    std::cin >> nick;
    std::cout << "Enter password: ";
    std::cin >> pw;
    std::cout << "Enter birthday: ";
    std::cin >> birthday;
    std::cout << "Enter location: ";
    std::cin >> location;

    user.setUserID(id);
    user.setNickName(nick);
    user.setPassword(pw);
    user.setBirthday(birthday);
    user.setLocation(location);
    user.setRegistrationTime(getCurrentTimeString());

    std::cout << "Choose platforms to enable (1.QQ 2.WeChat 3.Weibo, 0 to skip): ";
    int platformChoice = 0;
    std::cin >> platformChoice;
    while (platformChoice != 0) {
        std::string platformName;
        if (platformChoice == 1) platformName = "QQ";
        else if (platformChoice == 2) platformName = "WeChat";
        else if (platformChoice == 3) platformName = "Weibo";
        else {
            std::cout << "Invalid input\n";
            break;
        }
        bindingManager.bindPlatform(user, platformName, false);
        std::cout << "Continue opening platform (1.QQ 2.WeChat 3.Weibo, 0 to finish): ";
        std::cin >> platformChoice;
    }

    if (accountManager.registerUser(users, user)) {
        std::cout << "Registration successful\n";
    } else {
        std::cout << "Registration failed\n";
    }
}

void SystemUIJZY::loginUser() {
    std::string id, password;
    std::cout << "Enter ID: ";
    std::cin >> id;
    std::cout << "Enter password: ";
    std::cin >> password;

    UserInfoJZY tempUser;
    if (accountManager.loginUser(users, id, password, tempUser)) {
        currentUser = tempUser;
        loggedIn = true;
        std::cout << "Login successful, welcome " << currentUser.getNickName() << "\n";
        std::cout << "If other platforms are not bound, you can bind them in the bind menu.\n";
    } else {
        std::cout << "Login failed, invalid ID or password\n";
    }
}

void SystemUIJZY::handlePlatformAction(const std::string& platformName) {
    if (platformName == "Logout") {
        loggedIn = false;
        currentUser = UserInfoJZY();
        return;
    }

    if (platformName == "Bind") {
        showBindingMenu();
        return;
    }

    if (!userHasPlatform(platformName)) {
        std::cout << "The user has not enabled this platform. Enable it? (1.Yes 2.No)";
        int choose = 0;
        std::cin >> choose;
        if (choose == 1) {
            openPlatform(platformName);
            for (auto& user : users) {
                if (user.getUserID() == currentUser.getUserID()) {
                    user.setCurrentPlatform(platformName);
                    if (platformName == "QQ") user.setQQOpened(true);
                    if (platformName == "WeChat") user.setWeChatOpened(true);
                    if (platformName == "Weibo") user.setWeiboOpened(true);
                    break;
                }
            }
        } else {
            return;
        }
    }

    currentUser.setCurrentPlatform(platformName);
    std::cout << "Entering " << platformName << " platform\n";
    while (true) {
        std::cout << "\n=== " << platformName << " Platform Menu ===\n";
        std::cout << "1. Profile\n";
        std::cout << "2. Friend Management\n";
        std::cout << "3. Group Management\n";
        std::cout << "4. Return\n";
        std::cout << "Choose: ";
        int choice = 0;
        std::cin >> choice;

        switch (choice) {
            case 1: showUserProfileMenu(); break;
            case 2: showFriendMenu(); break;
            case 3: showGroupMenu(); break;
            case 4: return;
            default: std::cout << "Invalid input\n"; break;
        }
    }
}

void SystemUIJZY::showUserProfileMenu() {
    std::cout << "\n=== Profile ===\n";
    showCurrentUserInfo();
    std::cout << "1. Edit profile\n";
    std::cout << "2. Return\n";
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
            std::cout << "Enter new nickname (empty to keep): ";
            std::cin >> newNick;
            if (!newNick.empty()) user.setNickName(newNick);

            std::cout << "Enter new location (empty to keep): ";
            std::cin >> newLocation;
            if (!newLocation.empty()) user.setLocation(newLocation);

            std::cout << "Enter new birthday (empty to keep): ";
            std::cin >> newBirthday;
            if (!newBirthday.empty()) user.setBirthday(newBirthday);

            currentUser = user;
            std::cout << "Profile updated\n";
            return;
        }
    }
}

void SystemUIJZY::showFriendMenu() {
    std::cout << "\n=== Friend Management ===\n";
    std::cout << "1. Friend list\n";
    std::cout << "2. Add friend\n";
    std::cout << "3. Query friend\n";
    std::cout << "4. Return\n";
    int choice = 0;
    std::cin >> choice;
    switch (choice) {
        case 1: showFriendList(); break;
        case 2: addFriendByID(); break;
        case 3: queryFriend(); break;
        case 4: break;
        default: std::cout << "Invalid input\n"; break;
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
        std::cout << "No friends in the current platform\n";
        return;
    }

    std::cout << "\n=== Friend List (" << currentUser.getCurrentPlatform() << ") ===\n";
    friendManager.printFriends(platformFriends);
    std::cout << "Enter the number to edit a friend: ";
    int index = 0;
    std::cin >> index;
    if (index > 0 && index <= static_cast<int>(platformFriends.size())) {
        std::string selectedID = platformFriends[index - 1].getFriendID();
        for (auto& friendInfo : friends) {
            if (friendInfo.getFriendID() == selectedID) {
                friendInfo.showInfo();
                std::cout << "Delete this friend? 1.Yes 0.No: ";
                int del = 0;
                std::cin >> del;
                if (del == 1) {
                    friendManager.deleteFriend(friends, selectedID);
                    std::cout << "Deleted successfully\n";
                }
                break;
            }
        }
    }
}

void SystemUIJZY::addFriendByID() {
    std::string friendID, remark, groupName;
    std::cout << "Enter friend's ID: ";
    std::cin >> friendID;
    std::cout << "Enter remark: ";
    std::cin >> remark;
    std::cout << "Enter group: ";
    std::cin >> groupName;

    bool exists = false;
    for (const auto& user : users) {
        if (user.getUserID() == friendID) {
            exists = true;
            break;
        }
    }

    if (!exists) {
        std::cout << "This user does not exist\n";
        return;
    }

    FriendInfoJZY friendInfo;
    friendInfo.setFriendID(friendID);
    friendInfo.setNickName(friendID);
    friendInfo.setRemark(remark);
    friendInfo.setGroup(groupName);
    friendInfo.setPlatform(currentUser.getCurrentPlatform());

    if (friendManager.addFriend(friends, friendInfo)) {
        std::cout << "Friend added successfully\n";
    } else {
        std::cout << "Friend already exists\n";
    }
}

void SystemUIJZY::addFriendByRecommend() {
    std::cout << "Recommended friends\n";
    showRecommendedFriends(currentUser.getCurrentPlatform());
}

void SystemUIJZY::queryFriend() {
    std::cout << "1. Query by ID\n2. Query by nickname\nChoose: ";
    int choice = 0;
    std::cin >> choice;
    std::string key;
    if (choice == 1) {
        std::cout << "Enter friend ID: ";
        std::cin >> key;
    } else if (choice == 2) {
        std::cout << "Enter friend nickname: ";
        std::cin >> key;
    } else {
        std::cout << "Invalid input\n";
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
        std::cout << "No matching friend found\n";
        return;
    }

    std::cout << "Query results:\n";
    for (size_t i = 0; i < result.size(); ++i) {
        std::cout << i + 1 << ". " << result[i].getFriendID() << " " << result[i].getNickName() << "\n";
    }
}

void SystemUIJZY::editFriend() {
    std::cout << "Edit friend function placeholder\n";
}

void SystemUIJZY::showGroupMenu() {
    std::cout << "\n=== Group Management ===\n";
    std::cout << "1. Group list\n";
    std::cout << "2. Join group\n";
    std::cout << "3. Quit group\n";
    std::cout << "4. Query group members\n";
    std::cout << "5. Dynamic mode switch\n";
    std::cout << "6. Return\n";
    int choice = 0;
    std::cin >> choice;
    switch (choice) {
        case 1: showGroupList(); break;
        case 2: joinGroupByID(); break;
        case 3: quitGroup(); break;
        case 4: showGroupMembers(); break;
        case 5: showGroupDynamicMode(); break;
        case 6: break;
        default: std::cout << "Invalid input\n"; break;
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
        std::cout << "No groups in the current platform\n";
        return;
    }
    groupManager.printGroups(platformGroups);
}

void SystemUIJZY::joinGroupByID() {
    std::string groupID;
    std::cout << "Enter group ID to join: ";
    std::cin >> groupID;
    GroupInfoJZY target;
    for (const auto& group : groups) {
        if (group.getGroupID() == groupID) {
            target = group;
            break;
        }
    }

    if (target.getGroupID().empty()) {
        std::cout << "Group does not exist\n";
        return;
    }

    if (target.getPlatform() != currentUser.getCurrentPlatform()) {
        std::cout << "Current platform does not match the group platform\n";
        return;
    }

    if (groupManager.joinGroup(groups, groupID, currentUser.getUserID())) {
        std::cout << "Joined group successfully\n";
    } else {
        std::cout << "Join failed\n";
    }
}

void SystemUIJZY::quitGroup() {
    std::string groupID;
    std::cout << "Enter group ID to quit: ";
    std::cin >> groupID;
    if (groupManager.exitGroup(groups, groupID, currentUser.getUserID())) {
        std::cout << "Quit group successfully\n";
    } else {
        std::cout << "Group not found or not joined\n";
    }
}

void SystemUIJZY::showGroupMembers() {
    std::string groupID;
    std::cout << "Enter group ID: ";
    std::cin >> groupID;
    GroupInfoJZY group = groupManager.findGroupByID(groups, groupID);
    if (group.getGroupID().empty()) {
        std::cout << "Group does not exist\n";
        return;
    }
    std::cout << "Group members:\n";
    groupManager.printMembers(group);
}

void SystemUIJZY::showGroupDynamicMode() {
    std::cout << "\n=== Dynamic Group Management Mode ===\n";
    std::cout << "1. QQ group mode\n";
    std::cout << "2. WeChat group mode\n";
    std::cout << "3. Weibo group mode\n";
    std::cout << "Choose: ";
    int choice = 0;
    std::cin >> choice;
    if (choice == 1) std::cout << "QQ group mode supports applications, temporary groups, and admin system.\n";
    else if (choice == 2) std::cout << "WeChat group mode only supports invitation and group owner privileges.\n";
    else if (choice == 3) std::cout << "Weibo group uses a simplified social management mode.\n";
    else std::cout << "Invalid input\n";
}

void SystemUIJZY::showRecommendedFriends(const std::string& platformName) {
    std::vector<FriendInfoJZY> recs = friendManager.findRecommendedFriends(friends, currentUser.getUserID(), platformName);
    if (recs.empty()) {
        std::cout << "No recommended friends\n";
        return;
    }
    for (size_t i = 0; i < recs.size(); ++i) {
        std::cout << i + 1 << ". " << recs[i].getNickName() << " (" << recs[i].getFriendID() << ")\n";
    }
}

void SystemUIJZY::showBindingMenu() {
    std::cout << "\n=== Bind Management ===\n";
    std::cout << "1. QQ bind\n";
    std::cout << "2. WeChat bind\n";
    std::cout << "3. Weibo bind\n";
    std::cout << "4. Return\n";
    std::cout << "Choose: ";
    int choice = 0;
    std::cin >> choice;
    std::string platform = "";
    switch (choice) {
        case 1: platform = "QQ"; break;
        case 2: platform = "WeChat"; break;
        case 3: platform = "Weibo"; break;
        case 4: return;
        default: std::cout << "Invalid input\n"; return;
    }

    if (bindingManager.isPlatformOpened(currentUser, platform)) {
        std::cout << platform << " is already enabled\n";
        return;
    }

    if (bindingManager.bindPlatform(currentUser, platform, false)) {
        std::cout << platform << " bind success\n";
        for (auto& user : users) {
            if (user.getUserID() == currentUser.getUserID()) {
                if (platform == "QQ") user.setQQOpened(true);
                if (platform == "WeChat") user.setWeChatOpened(true);
                if (platform == "Weibo") user.setWeiboOpened(true);
                break;
            }
        }
    }
}
