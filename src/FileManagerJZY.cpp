#include "FileManagerJZY.h"
#include <iostream>

FileManagerJZY::FileManagerJZY() {}
FileManagerJZY::~FileManagerJZY() {}

void FileManagerJZY::loadAll() {
    std::cout << "加载所有数据...\n";
}

void FileManagerJZY::saveAll() {
    std::cout << "保存所有数据...\n";
}

void FileManagerJZY::loadUsers() {
    std::cout << "加载用户文件...\n";
}

void FileManagerJZY::saveUsers() {
    std::cout << "保存用户文件...\n";
}

void FileManagerJZY::loadFriends() {
    std::cout << "加载好友文件...\n";
}

void FileManagerJZY::saveFriends() {
    std::cout << "保存好友文件...\n";
}

void FileManagerJZY::loadGroups() {
    std::cout << "加载群文件...\n";
}

void FileManagerJZY::saveGroups() {
    std::cout << "保存群文件...\n";
}
