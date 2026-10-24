#include "FriendManagerJZY.h"
#include <algorithm>
#include <iostream>

FriendManagerJZY::FriendManagerJZY() {}
FriendManagerJZY::~FriendManagerJZY() {}

bool FriendManagerJZY::addFriend(std::vector<FriendInfoJZY>& friends, const FriendInfoJZY& friendInfo) {
    for (const auto& item : friends) {
        if (item.getFriendID() == friendInfo.getFriendID()) {
            return false;
        }
    }
    friends.push_back(friendInfo);
    return true;
}

bool FriendManagerJZY::deleteFriend(std::vector<FriendInfoJZY>& friends, const std::string& friendID) {
    auto it = std::find_if(friends.begin(), friends.end(), [&](const FriendInfoJZY& item) {
        return item.getFriendID() == friendID;
    });
    if (it == friends.end()) {
        return false;
    }
    friends.erase(it);
    return true;
}

bool FriendManagerJZY::updateFriend(std::vector<FriendInfoJZY>& friends, const std::string& friendID, const std::string& remark, const std::string& groupName) {
    auto it = std::find_if(friends.begin(), friends.end(), [&](const FriendInfoJZY& item) {
        return item.getFriendID() == friendID;
    });
    if (it == friends.end()) {
        return false;
    }
    it->setRemark(remark);
    it->setGroup(groupName);
    return true;
}

FriendInfoJZY FriendManagerJZY::findFriendByID(const std::vector<FriendInfoJZY>& friends, const std::string& friendID) const {
    for (const auto& item : friends) {
        if (item.getFriendID() == friendID) {
            return item;
        }
    }
    return FriendInfoJZY();
}

std::vector<FriendInfoJZY> FriendManagerJZY::findFriendsByNickname(const std::vector<FriendInfoJZY>& friends, const std::string& nickName) const {
    std::vector<FriendInfoJZY> result;
    for (const auto& item : friends) {
        if (item.getNickName() == nickName) {
            result.push_back(item);
        }
    }
    return result;
}

std::vector<FriendInfoJZY> FriendManagerJZY::getFriendsByPlatform(const std::vector<FriendInfoJZY>& friends, const std::string& platform) const {
    std::vector<FriendInfoJZY> result;
    for (const auto& item : friends) {
        if (item.getPlatform() == platform) {
            result.push_back(item);
        }
    }
    return result;
}

std::vector<FriendInfoJZY> FriendManagerJZY::findRecommendedFriends(const std::vector<FriendInfoJZY>& friends, const std::string& currentUserID, const std::string& platform) const {
    std::vector<FriendInfoJZY> result;
    for (const auto& item : friends) {
        if (item.getPlatform() == platform && item.getFriendID() != currentUserID) {
            result.push_back(item);
        }
    }
    return result;
}

void FriendManagerJZY::printFriends(const std::vector<FriendInfoJZY>& friends) const {
    if (friends.empty()) {
        std::cout << "No friends currently\n";
        return;
    }
    int index = 1;
    for (const auto& friendInfo : friends) {
        std::cout << index++ << ". " << friendInfo.getNickName() << " (" << friendInfo.getFriendID() << ")" << " Group:" << friendInfo.getGroup() << "\n";
    }
}
