#ifndef ACCOUNTMANAGERJZY_H
#define ACCOUNTMANAGERJZY_H

#include <string>
#include <vector>
#include "UserInfoJZY.h"

class AccountManagerJZY {
public:
    AccountManagerJZY();
    ~AccountManagerJZY();

    bool userExists(const std::vector<UserInfoJZY>& users, const std::string& id) const;
    bool registerUser(std::vector<UserInfoJZY>& users, const UserInfoJZY& user);
    bool loginUser(const std::vector<UserInfoJZY>& users, const std::string& id, const std::string& password, UserInfoJZY& outUser) const;
};

#endif
