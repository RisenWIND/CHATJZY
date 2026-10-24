#ifndef GROUPMANAGERJZY_H
#define GROUPMANAGERJZY_H

#include <string>
#include <vector>
#include "GroupInfoJZY.h"

class GroupManagerJZY {
public:
    GroupManagerJZY();
    ~GroupManagerJZY();

    bool addGroup(std::vector<GroupInfoJZY>& groups, const GroupInfoJZY& group);
    bool joinGroup(std::vector<GroupInfoJZY>& groups, const std::string& groupID, const std::string& userID);
    bool exitGroup(std::vector<GroupInfoJZY>& groups, const std::string& groupID, const std::string& userID);
    GroupInfoJZY findGroupByID(const std::vector<GroupInfoJZY>& groups, const std::string& groupID) const;
    std::vector<GroupInfoJZY> findGroupsByPlatform(const std::vector<GroupInfoJZY>& groups, const std::string& platform) const;
    void printGroups(const std::vector<GroupInfoJZY>& groups) const;
    void printMembers(const GroupInfoJZY& group) const;
};

#endif
