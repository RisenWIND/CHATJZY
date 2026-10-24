#include "GroupManagerJZY.h"
#include <algorithm>
#include <iostream>

GroupManagerJZY::GroupManagerJZY() {}
GroupManagerJZY::~GroupManagerJZY() {}

bool GroupManagerJZY::addGroup(std::vector<GroupInfoJZY>& groups, const GroupInfoJZY& group) {
    for (const auto& item : groups) {
        if (item.getGroupID() == group.getGroupID()) {
            return false;
        }
    }
    groups.push_back(group);
    return true;
}

bool GroupManagerJZY::joinGroup(std::vector<GroupInfoJZY>& groups, const std::string& groupID, const std::string& userID) {
    auto it = std::find_if(groups.begin(), groups.end(), [&](const GroupInfoJZY& group) {
        return group.getGroupID() == groupID;
    });
    if (it == groups.end()) {
        return false;
    }
    it->addMember(userID);
    return true;
}

bool GroupManagerJZY::exitGroup(std::vector<GroupInfoJZY>& groups, const std::string& groupID, const std::string& userID) {
    auto it = std::find_if(groups.begin(), groups.end(), [&](const GroupInfoJZY& group) {
        return group.getGroupID() == groupID;
    });
    if (it == groups.end()) {
        return false;
    }
    it->removeMember(userID);
    return true;
}

GroupInfoJZY GroupManagerJZY::findGroupByID(const std::vector<GroupInfoJZY>& groups, const std::string& groupID) const {
    for (const auto& group : groups) {
        if (group.getGroupID() == groupID) {
            return group;
        }
    }
    return GroupInfoJZY();
}

std::vector<GroupInfoJZY> GroupManagerJZY::findGroupsByPlatform(const std::vector<GroupInfoJZY>& groups, const std::string& platform) const {
    std::vector<GroupInfoJZY> result;
    for (const auto& group : groups) {
        if (group.getPlatform() == platform) {
            result.push_back(group);
        }
    }
    return result;
}

void GroupManagerJZY::printGroups(const std::vector<GroupInfoJZY>& groups) const {
    if (groups.empty()) {
        std::cout << "No groups currently\n";
        return;
    }
    int index = 1;
    for (const auto& group : groups) {
        std::cout << index++ << ". " << group.getGroupName() << " (" << group.getGroupID() << ")" << " Platform:" << group.getPlatform() << "\n";
    }
}

void GroupManagerJZY::printMembers(const GroupInfoJZY& group) const {
    const auto members = group.getMembers();
    if (members.empty()) {
        std::cout << "No members in the group\n";
        return;
    }
    int index = 1;
    for (const auto& member : members) {
        std::cout << index++ << ". " << member << "\n";
    }
}


