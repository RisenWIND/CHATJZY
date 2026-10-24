#ifndef USERINFOJZY_H
#define USERINFOJZY_H

#include <string>
#include <vector>

class UserInfoJZY {
public:
    UserInfoJZY();
    ~UserInfoJZY();

    void setUserID(const std::string& id);
    std::string getUserID() const;

    void setNickName(const std::string& name);
    std::string getNickName() const;

    void setPassword(const std::string& pw);
    std::string getPassword() const;

    void setBirthday(const std::string& date);
    std::string getBirthday() const;

    void setLocation(const std::string& loc);
    std::string getLocation() const;

    void setRegistrationTime(const std::string& time);
    std::string getRegistrationTime() const;

    void setQQOpened(bool flag);
    bool isQQOpened() const;

    void setWeChatOpened(bool flag);
    bool isWeChatOpened() const;

    void setWeiboOpened(bool flag);
    bool isWeiboOpened() const;

    void showInfo() const;

private:
    std::string userID;
    std::string nickName;
    std::string password;
    std::string birthday;
    std::string location;
    std::string registrationTime;

    bool qqOpened;
    bool weChatOpened;
    bool weiboOpened;
};

#endif
