# 项目说明

这是一个完全按照课程设计要求扩展后的即时通信系统模拟项目，命名统一采用 JZY 后缀。

## 设计目标

- 采用面向对象思想实现
- 模拟 QQ / 微信 / 微博 三个平台
- 实现用户注册、登录、绑定、开通服务
- 支持好友管理：添加、删除、查询、编辑、分组
- 支持群管理：加入群、退出群、查询成员、动态群模式
- 支持数据文件持久化：用户、好友、群保存到 data 目录
- 提供菜单式操作界面，符合课程设计要求

## 类设计

- UserInfoJZY
- AccountManagerJZY
- BindingManagerJZY
- PlatformBaseJZY
- QQPlatformJZY
- WeChatPlatformJZY
- WeiboPlatformJZY
- FriendInfoJZY
- FriendManagerJZY
- GroupInfoJZY
- GroupManagerJZY
- FileManagerJZY
- SystemUIJZY

## 目录说明

- `include/`：类声明头文件
- `src/`：实现文件
- `data/`：运行时保存用户、好友和群数据
- `CMakeLists.txt`：项目编译配置

## 编译运行

```bash
mkdir -p build
cd build
cmake ..
make
./CHATJZY
```

## 功能菜单概览

1. 注册
2. 登录
3. 退出

平台选择：QQ / 微信 / 微博 / 绑定管理 / 退出登录

平台内菜单：
- 个人信息
- 好友管理
- 群管理

好友管理：
- 好友列表
- 添加好友
- 查询好友

群管理：
- 群列表
- 加入群
- 退出群
- 查询群成员
- 动态切换群模式

## 说明

本项目是课程设计的扩展版框架，已覆盖核心设计要求，并可继续增加 QQ TCP 通信、复杂推荐好友逻辑、群管理员分析等功能。
