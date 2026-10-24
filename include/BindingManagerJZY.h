#ifndef BINDINGMANAGERJZY_H
#define BINDINGMANAGERJZY_H

#include <string>
#include <vector>
#include "UserInfoJZY.h"

class BindingManagerJZY {
public:
    BindingManagerJZY();
    ~BindingManagerJZY();

    bool bindPlatform(UserInfoJZY& user, const std::string& platformName, bool createIfNotExists = false);
    bool canBindToPlatform(const UserInfoJZY& user, const std::string& platformName) const;
    bool isPlatformOpened(const UserInfoJZY& user, const std::string& platformName) const;
};

#endif
