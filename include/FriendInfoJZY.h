#ifndef FRIENDINFOJZY_H
#define FRIENDINFOJZY_H

#include <string>

class FriendInfoJZY {
public:
    FriendInfoJZY();
    ~FriendInfoJZY();

    void setFriendID(const std::string& id);
    std::string getFriendID() const;

    void setNickName(const std::string& name);
    std::string getNickName() const;

    void setRemark(const std::string& remark);
    std::string getRemark() const;

    void setGroup(const std::string& group);
    std::string getGroup() const;

    void setPlatform(const std::string& platform);
    std::string getPlatform() const;

    void showInfo() const;

private:
    std::string friendID;
    std::string nickName;
    std::string remark;
    std::string group;
    std::string platform;
};

#endif
