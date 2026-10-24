#ifndef WEIBOPLATFORMJZY_H
#define WEIBOPLATFORMJZY_H

#include "PlatformBaseJZY.h"

class WeiboPlatformJZY : public PlatformBaseJZY {
public:
    WeiboPlatformJZY();
    ~WeiboPlatformJZY() override;

    void registerAccount() override;
    void loginAccount() override;
    void bindAccount() override;
    void showInfo() override;
};

#endif
