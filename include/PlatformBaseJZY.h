#ifndef PLATFORMBASEJZY_H
#define PLATFORMBASEJZY_H

#include <string>

class PlatformBaseJZY {
public:
    PlatformBaseJZY(const std::string& name = "");
    virtual ~PlatformBaseJZY() = default;

    virtual void registerAccount() = 0;
    virtual void loginAccount() = 0;
    virtual void bindAccount() = 0;
    virtual void showInfo() = 0;

    std::string getPlatformName() const;
    void setPlatformName(const std::string& name);

    bool isOpen() const;
    void setOpen(bool flag);

    bool isLogin() const;
    void setLogin(bool flag);

private:
    std::string platformName;
    bool open;
    bool login;
};

#endif
