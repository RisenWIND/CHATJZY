#include "GroupInfoJZY.h"
#include <iostream>
#include <vector>

GroupInfoJZY::GroupInfoJZY() : groupID(""), groupName(""), platform(""), ownerID("") {}
GroupInfoJZY::~GroupInfoJZY() {}

void GroupInfoJZY::setGroupID(const std::string& id) { groupID = id; }
std::string GroupInfoJZY::getGroupID() const { return groupID; }

void GroupInfoJZY::setGroupName(const std::string& name) { groupName = name; }
std::string GroupInfoJZY::getGroupName() const { return groupName; }

void GroupInfoJZY::setPlatform(const std::string& platformName) { platform = platformName; }
std::string GroupInfoJZY::getPlatform() const { return platform; }

void GroupInfoJZY::setOwnerID(const std::string& id) { ownerID = id; }
std::string GroupInfoJZY::getOwnerID() const { return ownerID; }

void GroupInfoJZY::addMember(const std::string& userID) {
    if (std::find(members.begin(), members.end(), userID) == members.end()) {
        members.push_back(userID);
    }
}

void GroupInfoJZY::removeMember(const std::string& userID) {
    members.erase(std::remove(members.begin(), members.end(), userID), members.end());
}

std::vector<std::string> GroupInfoJZY::getMembers() const { return members; }

void GroupInfoJZY::showInfo() const {
    std::cout << "Group ID: " << groupID << "\n";
    std::cout << "Group name: " << groupName << "\n";
    std::cout << "Platform: " << platform << "\n";
    std::cout << "Owner ID: " << ownerID << "\n";
    std::cout << "Member count: " << members.size() << "\n";
}
