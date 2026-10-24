#include "GroupInfoJZY.h"
#include <iostream>

GroupInfoJZY::GroupInfoJZY() {}
GroupInfoJZY::~GroupInfoJZY() {}

void GroupInfoJZY::setGroupID(const std::string& id) { groupID = id; }
std::string GroupInfoJZY::getGroupID() const { return groupID; }

void GroupInfoJZY::setGroupName(const std::string& name) { groupName = name; }
std::string GroupInfoJZY::getGroupName() const { return groupName; }

void GroupInfoJZY::setPlatform(const std::string& platformName) { platform = platformName; }
std::string GroupInfoJZY::getPlatform() const { return platform; }

void GroupInfoJZY::setOwnerID(const std::string& id) { ownerID = id; }
std::string GroupInfoJZY::getOwnerID() const { return ownerID; }

void GroupInfoJZY::addMember(const std::string& memberID) {
    members.push_back(memberID);
}

void GroupInfoJZY::removeMember(const std::string& memberID) {
    auto it = std::find(members.begin(), members.end(), memberID);
    if (it != members.end()) {
        members.erase(it);
    }
}

std::vector<std::string> GroupInfoJZY::getMembers() const { return members; }

void GroupInfoJZY::showInfo() const {
    std::cout << "群ID: " << groupID << "\n";
    std::cout << "群名: " << groupName << "\n";
    std::cout << "平台: " << platform << "\n";
    std::cout << "群主: " << ownerID << "\n";
    std::cout << "成员数: " << members.size() << "\n";
}
