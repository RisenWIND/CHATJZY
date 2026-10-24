#ifndef SYSTEMUIJZY_H
#define SYSTEMUIJZY_H

#include <string>
#include <vector>
#include "UserInfoJZY.h"
#include "FriendInfoJZY.h"
#include "GroupInfoJZY.h"
#include "FileManagerJZY.h"
#include "AccountManagerJZY.h"
#include "FriendManagerJZY.h"
#include "GroupManagerJZY.h"
#include "BindingManagerJZY.h"

class SystemUIJZY {
public:
    SystemUIJZY();
    ~SystemUIJZY();

    void run();

private:
    std::vector<UserInfoJZY> users;
    std::vector<FriendInfoJZY> friends;
    std::vector<GroupInfoJZY> groups;
    UserInfoJZY currentUser;
    bool loggedIn;
    FileManagerJZY fileManager;
    AccountManagerJZY accountManager;
    FriendManagerJZY friendManager;
    GroupManagerJZY groupManager;
    BindingManagerJZY bindingManager;

    void loadData();
    void saveData();
    void showMainMenu();
    void showRegisterMenu();
    void showLoginMenu();
    void showPlatformMenu();
    void showUserProfileMenu();
    void showFriendMenu();
    void showGroupMenu();
    void showBindingMenu();
    void registerUser();
    void loginUser();
    void handlePlatformAction(const std::string& platformName);
    void showCurrentUserInfo();
    void editCurrentUserInfo();
    void addFriendByID();
    void addFriendByRecommend();
    void queryFriend();
    void showFriendList();
    void editFriend();
    void joinGroupByID();
    void quitGroup();
    void showGroupMembers();
    void showGroupList();
    void showGroupDynamicMode();
    void showRecommendedFriends(const std::string& platformName);
    std::string getPlatformNameFromChoice(int choice) const;
    bool userHasPlatform(const std::string& platformName) const;
    void openPlatform(const std::string& platformName);
    std::string getCurrentTimeString() const;
};

#endif
