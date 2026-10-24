#ifndef QQPLATFORMJZY_H
#define QQPLATFORMJZY_H

#include "PlatformBaseJZY.h"

class QQPlatformJZY : public PlatformBaseJZY {
public:
    QQPlatformJZY();
    ~QQPlatformJZY() override;

    void registerAccount() override;
    void loginAccount() override;
    void bindAccount() override;
    void showInfo() override;
};

#endif
