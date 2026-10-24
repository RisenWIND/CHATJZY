#include "AccountManagerJZY.h"
#include <algorithm>

AccountManagerJZY::AccountManagerJZY() {}
AccountManagerJZY::~AccountManagerJZY() {}

bool AccountManagerJZY::userExists(const std::vector<UserInfoJZY>& users, const std::string& id) const {
    for (const auto& user : users) {
        if (user.getUserID() == id) {
            return true;
        }
    }
    return false;
}

bool AccountManagerJZY::registerUser(std::vector<UserInfoJZY>& users, const UserInfoJZY& user) {
    if (userExists(users, user.getUserID())) {
        return false;
    }
    users.push_back(user);
    return true;
}

bool AccountManagerJZY::loginUser(const std::vector<UserInfoJZY>& users, const std::string& id, const std::string& password, UserInfoJZY& outUser) const {
    for (const auto& user : users) {
        if (user.getUserID() == id && user.getPassword() == password) {
            outUser = user;
            return true;
        }
    }
    return false;
}
