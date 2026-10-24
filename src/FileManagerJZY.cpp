#include "FileManagerJZY.h"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <iostream>

FileManagerJZY::FileManagerJZY() {}
FileManagerJZY::~FileManagerJZY() {}

void FileManagerJZY::loadAll(std::vector<UserInfoJZY>& users, std::vector<FriendInfoJZY>& friends, std::vector<GroupInfoJZY>& groups) {
    std::filesystem::create_directories("data");
    loadUsers(users);
    loadFriends(friends);
    loadGroups(groups);
}

void FileManagerJZY::saveAll(const std::vector<UserInfoJZY>& users, const std::vector<FriendInfoJZY>& friends, const std::vector<GroupInfoJZY>& groups) {
    std::filesystem::create_directories("data");
    saveUsers(users);
    saveFriends(friends);
    saveGroups(groups);
}

void FileManagerJZY::loadUsers(std::vector<UserInfoJZY>& users) {
    std::ifstream in("data/users.txt");
    if (!in.is_open()) {
        return;
    }
    users.clear();
    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string id, nick, pw, birthday, location, reg, qq, wechat, weibo;
        std::getline(ss, id, '|');
        std::getline(ss, nick, '|');
        std::getline(ss, pw, '|');
        std::getline(ss, birthday, '|');
        std::getline(ss, location, '|');
        std::getline(ss, reg, '|');
        std::getline(ss, qq, '|');
        std::getline(ss, wechat, '|');
        std::getline(ss, weibo, '|');

        UserInfoJZY user;
        user.setUserID(id);
        user.setNickName(nick);
        user.setPassword(pw);
        user.setBirthday(birthday);
        user.setLocation(location);
        user.setRegistrationTime(reg);
        user.setQQOpened(qq == "1");
        user.setWeChatOpened(wechat == "1");
        user.setWeiboOpened(weibo == "1");
        users.push_back(user);
    }
    in.close();
}

void FileManagerJZY::saveUsers(const std::vector<UserInfoJZY>& users) {
    std::ofstream out("data/users.txt", std::ios::trunc);
    if (!out.is_open()) {
        return;
    }
    for (const auto& user : users) {
        out << user.getUserID() << "|" << user.getNickName() << "|" << user.getPassword() << "|"
            << user.getBirthday() << "|" << user.getLocation() << "|" << user.getRegistrationTime() << "|"
            << (user.isQQOpened() ? "1" : "0") << "|" << (user.isWeChatOpened() ? "1" : "0") << "|"
            << (user.isWeiboOpened() ? "1" : "0") << "\n";
    }
    out.close();
}

void FileManagerJZY::loadFriends(std::vector<FriendInfoJZY>& friends) {
    std::ifstream in("data/friends.txt");
    if (!in.is_open()) {
        return;
    }
    friends.clear();
    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string friendID, nick, remark, group, platform;
        std::getline(ss, friendID, '|');
        std::getline(ss, nick, '|');
        std::getline(ss, remark, '|');
        std::getline(ss, group, '|');
        std::getline(ss, platform, '|');

        FriendInfoJZY friendInfo;
        friendInfo.setFriendID(friendID);
        friendInfo.setNickName(nick);
        friendInfo.setRemark(remark);
        friendInfo.setGroup(group);
        friendInfo.setPlatform(platform);
        friends.push_back(friendInfo);
    }
    in.close();
}

void FileManagerJZY::saveFriends(const std::vector<FriendInfoJZY>& friends) {
    std::ofstream out("data/friends.txt", std::ios::trunc);
    if (!out.is_open()) {
        return;
    }
    for (const auto& friendInfo : friends) {
        out << friendInfo.getFriendID() << "|" << friendInfo.getNickName() << "|" << friendInfo.getRemark() << "|"
            << friendInfo.getGroup() << "|" << friendInfo.getPlatform() << "\n";
    }
    out.close();
}

void FileManagerJZY::loadGroups(std::vector<GroupInfoJZY>& groups) {
    std::ifstream in("data/groups.txt");
    if (!in.is_open()) {
        return;
    }
    groups.clear();
    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string groupID, groupName, platform, ownerID, membersLine;
        std::getline(ss, groupID, '|');
        std::getline(ss, groupName, '|');
        std::getline(ss, platform, '|');
        std::getline(ss, ownerID, '|');
        std::getline(ss, membersLine, '|');

        GroupInfoJZY group;
        group.setGroupID(groupID);
        group.setGroupName(groupName);
        group.setPlatform(platform);
        group.setOwnerID(ownerID);

        std::stringstream memberSS(membersLine);
        std::string member;
        while (std::getline(memberSS, member, ',')) {
            if (!member.empty()) {
                group.addMember(member);
            }
        }
        groups.push_back(group);
    }
    in.close();
}

void FileManagerJZY::saveGroups(const std::vector<GroupInfoJZY>& groups) {
    std::ofstream out("data/groups.txt", std::ios::trunc);
    if (!out.is_open()) {
        return;
    }
    for (const auto& group : groups) {
        out << group.getGroupID() << "|" << group.getGroupName() << "|" << group.getPlatform() << "|" << group.getOwnerID() << "|";
        const auto members = group.getMembers();
        for (size_t i = 0; i < members.size(); ++i) {
            out << members[i];
            if (i + 1 < members.size()) out << ",";
        }
        out << "\n";
    }
    out.close();
}
