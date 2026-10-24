#ifndef WECHATPLATFORMJZY_H
#define WECHATPLATFORMJZY_H

#include "PlatformBaseJZY.h"

class WeChatPlatformJZY : public PlatformBaseJZY {
public:
    WeChatPlatformJZY();
    ~WeChatPlatformJZY() override;

    void registerAccount() override;
    void loginAccount() override;
    void bindAccount() override;
    void showInfo() override;
};

#endif
