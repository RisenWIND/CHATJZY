#ifndef FILEMANAGERJZY_H
#define FILEMANAGERJZY_H

#include <string>
#include <vector>
#include "UserInfoJZY.h"
#include "FriendInfoJZY.h"
#include "GroupInfoJZY.h"

class FileManagerJZY {
public:
    FileManagerJZY();
    ~FileManagerJZY();

    void loadAll(std::vector<UserInfoJZY>& users, std::vector<FriendInfoJZY>& friends, std::vector<GroupInfoJZY>& groups);
    void saveAll(const std::vector<UserInfoJZY>& users, const std::vector<FriendInfoJZY>& friends, const std::vector<GroupInfoJZY>& groups);

    void loadUsers(std::vector<UserInfoJZY>& users);
    void saveUsers(const std::vector<UserInfoJZY>& users);

    void loadFriends(std::vector<FriendInfoJZY>& friends);
    void saveFriends(const std::vector<FriendInfoJZY>& friends);

    void loadGroups(std::vector<GroupInfoJZY>& groups);
    void saveGroups(const std::vector<GroupInfoJZY>& groups);
};

#endif
