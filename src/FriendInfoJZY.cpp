#include "FriendInfoJZY.h"
#include <iostream>

FriendInfoJZY::FriendInfoJZY() {}
FriendInfoJZY::~FriendInfoJZY() {}

void FriendInfoJZY::setFriendID(const std::string& id) { friendID = id; }
std::string FriendInfoJZY::getFriendID() const { return friendID; }

void FriendInfoJZY::setNickName(const std::string& name) { nickName = name; }
std::string FriendInfoJZY::getNickName() const { return nickName; }

void FriendInfoJZY::setRemark(const std::string& remarkVal) { remark = remarkVal; }
std::string FriendInfoJZY::getRemark() const { return remark; }

void FriendInfoJZY::setGroup(const std::string& groupVal) { group = groupVal; }
std::string FriendInfoJZY::getGroup() const { return group; }

void FriendInfoJZY::setPlatform(const std::string& platformName) { platform = platformName; }
std::string FriendInfoJZY::getPlatform() const { return platform; }

void FriendInfoJZY::showInfo() const {
    std::cout << "Friend ID: " << friendID << "\n";
    std::cout << "Nickname: " << nickName << "\n";
    std::cout << "Remark: " << remark << "\n";
    std::cout << "Group: " << group << "\n";
    std::cout << "Platform: " << platform << "\n";
}
