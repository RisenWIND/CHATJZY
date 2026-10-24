#ifndef GROUPINFOJZY_H
#define GROUPINFOJZY_H

#include <string>
#include <vector>

class GroupInfoJZY {
public:
    GroupInfoJZY();
    ~GroupInfoJZY();

    void setGroupID(const std::string& id);
    std::string getGroupID() const;

    void setGroupName(const std::string& name);
    std::string getGroupName() const;

    void setPlatform(const std::string& platform);
    std::string getPlatform() const;

    void setOwnerID(const std::string& id);
    std::string getOwnerID() const;

    void addMember(const std::string& memberID);
    void removeMember(const std::string& memberID);
    std::vector<std::string> getMembers() const;

    void showInfo() const;

private:
    std::string groupID;
    std::string groupName;
    std::string platform;
    std::string ownerID;
    std::vector<std::string> members;
};

#endif
