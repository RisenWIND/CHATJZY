#ifndef FRIENDMANAGERJZY_H
#define FRIENDMANAGERJZY_H

#include <string>
#include <vector>
#include "FriendInfoJZY.h"
#include "UserInfoJZY.h"

class FriendManagerJZY {
public:
    FriendManagerJZY();
    ~FriendManagerJZY();

    bool addFriend(std::vector<FriendInfoJZY>& friends, const FriendInfoJZY& friendInfo);
    bool deleteFriend(std::vector<FriendInfoJZY>& friends, const std::string& friendID);
    bool updateFriend(std::vector<FriendInfoJZY>& friends, const std::string& friendID, const std::string& remark, const std::string& groupName);
    FriendInfoJZY findFriendByID(const std::vector<FriendInfoJZY>& friends, const std::string& friendID) const;
    std::vector<FriendInfoJZY> findFriendsByNickname(const std::vector<FriendInfoJZY>& friends, const std::string& nickName) const;
    std::vector<FriendInfoJZY> getFriendsByPlatform(const std::vector<FriendInfoJZY>& friends, const std::string& platform) const;
    std::vector<FriendInfoJZY> findRecommendedFriends(const std::vector<FriendInfoJZY>& friends, const std::string& currentUserID, const std::string& platform) const;
    void printFriends(const std::vector<FriendInfoJZY>& friends) const;
};

#endif
