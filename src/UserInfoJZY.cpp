#include "UserInfoJZY.h"
#include <iostream>

UserInfoJZY::UserInfoJZY()
    : userID(""), nickName(""), password(""), birthday(""), location(""), registrationTime(""), currentPlatform(""), qqOpened(false), weChatOpened(false), weiboOpened(false) {}

UserInfoJZY::UserInfoJZY(const std::string& id)
    : UserInfoJZY() {
    userID = id;
}

UserInfoJZY::~UserInfoJZY() {}

void UserInfoJZY::setUserID(const std::string& id) { userID = id; }
std::string UserInfoJZY::getUserID() const { return userID; }

void UserInfoJZY::setNickName(const std::string& name) { nickName = name; }
std::string UserInfoJZY::getNickName() const { return nickName; }

void UserInfoJZY::setPassword(const std::string& pw) { password = pw; }
std::string UserInfoJZY::getPassword() const { return password; }

void UserInfoJZY::setBirthday(const std::string& date) { birthday = date; }
std::string UserInfoJZY::getBirthday() const { return birthday; }

void UserInfoJZY::setLocation(const std::string& loc) { location = loc; }
std::string UserInfoJZY::getLocation() const { return location; }

void UserInfoJZY::setRegistrationTime(const std::string& time) { registrationTime = time; }
std::string UserInfoJZY::getRegistrationTime() const { return registrationTime; }

void UserInfoJZY::setQQOpened(bool flag) { qqOpened = flag; }
bool UserInfoJZY::isQQOpened() const { return qqOpened; }

void UserInfoJZY::setWeChatOpened(bool flag) { weChatOpened = flag; }
bool UserInfoJZY::isWeChatOpened() const { return weChatOpened; }

void UserInfoJZY::setWeiboOpened(bool flag) { weiboOpened = flag; }
bool UserInfoJZY::isWeiboOpened() const { return weiboOpened; }

void UserInfoJZY::setCurrentPlatform(const std::string& platform) { currentPlatform = platform; }
std::string UserInfoJZY::getCurrentPlatform() const { return currentPlatform; }

void UserInfoJZY::showInfo() const {
    std::cout << "用户ID: " << userID << "\n";
    std::cout << "昵称: " << nickName << "\n";
    std::cout << "生日: " << birthday << "\n";
    std::cout << "所在地: " << location << "\n";
    std::cout << "注册时间: " << registrationTime << "\n";
    std::cout << "已开通平台: QQ=" << qqOpened << " 微信=" << weChatOpened << " 微博=" << weiboOpened << "\n";
}
