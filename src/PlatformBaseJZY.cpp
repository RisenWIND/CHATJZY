#include "PlatformBaseJZY.h"

PlatformBaseJZY::PlatformBaseJZY(const std::string& name)
    : platformName(name), open(false), login(false) {}

std::string PlatformBaseJZY::getPlatformName() const { return platformName; }
void PlatformBaseJZY::setPlatformName(const std::string& name) { platformName = name; }

bool PlatformBaseJZY::isOpen() const { return open; }
void PlatformBaseJZY::setOpen(bool flag) { open = flag; }

bool PlatformBaseJZY::isLogin() const { return login; }
void PlatformBaseJZY::setLogin(bool flag) { login = flag; }
