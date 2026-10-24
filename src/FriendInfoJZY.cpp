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
    std::cout << "好友ID: " << friendID << "\n";
    std::cout << "昵称: " << nickName << "\n";
    std::cout << "备注: " << remark << "\n";
    std::cout << "分组: " << group << "\n";
    std::cout << "平台: " << platform << "\n";
}
