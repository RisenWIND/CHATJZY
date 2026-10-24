#ifndef FILEMANAGERJZY_H
#define FILEMANAGERJZY_H

#include <string>

class FileManagerJZY {
public:
    FileManagerJZY();
    ~FileManagerJZY();

    void loadAll();
    void saveAll();

    void loadUsers();
    void saveUsers();

    void loadFriends();
    void saveFriends();

    void loadGroups();
    void saveGroups();
};

#endif
