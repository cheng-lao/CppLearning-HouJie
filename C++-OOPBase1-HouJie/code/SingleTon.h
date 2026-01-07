
#ifndef SINGLETON_H
#define SINGLETON_H

#include <string>
#include <iostream>
#include <map>
#include <vector>
using namespace std;
// ============================================
// 示例1: 基础单例模式 (Meyers' Singleton)
// ============================================
class A
{
private:
    A() {
        std::cout << "单例对象 A 被创建了！" << std::endl;
    }
    A(const A& rhs) = delete;  // 禁止拷贝构造
    A& operator=(const A& rhs) = delete;  // 禁止赋值操作
    
public:
    static A& getInstance() {
        // 只有有人用过这个类才会生成这个static对象，否则在内存当中就不会出现
        // 使用方法: A::getInstance().setup();
        static A a;  // 线程安全（C++11之后）
        return a;    
    }
    
    void setup() { 
        std::cout << "A::setup() 被调用" << std::endl;
    }
    
    void showAddress() {
        std::cout << "单例对象 A 的内存地址: " << this << std::endl;
    }
    
    ~A() {
        std::cout << "单例对象 A 被销毁了！" << std::endl;
    }
};

// ============================================
// 示例2: 配置管理器单例 (实际应用场景)
// ============================================
class ConfigManager
{
private:
    std::map<std::string, std::string> configs;  // 配置项存储
    int accessCount;  // 访问计数
    
    ConfigManager() : accessCount(0) {
        std::cout << "配置管理器被创建！" << std::endl;
        // 初始化默认配置
        configs["app_name"] = "MyApp";
        configs["version"] = "1.0.0";
        configs["debug_mode"] = "false";
    }
    
    ConfigManager(const ConfigManager&) = delete;  // 禁用拷贝构造函数
    ConfigManager& operator=(const ConfigManager&) = delete;    //禁用赋值构造函数
    
public:
    static ConfigManager& getInstance() {
        static ConfigManager instance;
        return instance;
    }
    
    // 设置配置项
    void setConfig(const std::string& key, const std::string& value) {
        configs[key] = value;
        std::cout << "设置配置: " << key << " = " << value << std::endl;
    }
    
    // 获取配置项
    std::string getConfig(const std::string& key) {
        accessCount++;
        auto it = configs.find(key);
        if (it != configs.end()) {
            std::cout << "获取配置: " << key << " = " << it->second 
                      << " (访问次数: " << accessCount << ")" << std::endl;
            return it->second;
        }
        std::cout << "配置项 " << key << " 不存在！" << std::endl;
        return "";
    }
    
    // 显示所有配置
    void showAllConfigs() {
        std::cout << "\n=== 所有配置项 ===" << std::endl;
        for (const auto& pair : configs) {
            std::cout << "  " << pair.first << " = " << pair.second << std::endl;
        }
        std::cout << "总访问次数: " << accessCount << std::endl;
        std::cout << "==================\n" << std::endl;
    }
    
    // 获取访问计数
    int getAccessCount() const {
        return accessCount;
    }
    
    ~ConfigManager() {
        std::cout << "配置管理器被销毁！" << std::endl;
    }
};

// ============================================
// 示例3: 日志管理器单例 (实际应用场景)
// ============================================
class Logger
{
private:
    std::vector<std::string> logs;  // 日志存储
    bool enabled;  // 是否启用日志
    
    Logger() : enabled(true) {
        std::cout << "日志管理器被创建！" << std::endl;
        log("系统", "日志系统初始化完成");
    }
    
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    
public:
    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }
    
    // 记录日志
    void log(const std::string& module, const std::string& message) {
        if (!enabled) return;
        
        std::string logEntry = "[" + module + "] " + message;
        logs.push_back(logEntry);
        std::cout << logEntry << std::endl;
    }
    
    // 启用/禁用日志
    void setEnabled(bool enable) {
        enabled = enable;
        log("系统", enable ? "日志已启用" : "日志已禁用");
    }
    
    // 显示所有日志
    void showAllLogs() {
        std::cout << "\n=== 日志记录 ===" << std::endl;
        for (size_t i = 0; i < logs.size(); ++i) {
            std::cout << "[" << (i + 1) << "] " << logs[i] << std::endl;
        }
        std::cout << "共 " << logs.size() << " 条日志" << std::endl;
        std::cout << "===============\n" << std::endl;
    }
    
    // 清空日志
    void clearLogs() {
        logs.clear();
        log("系统", "日志已清空");
    }
    
    ~Logger() {
        log("系统", "日志系统关闭");
    }
};

#endif // SINGLETON_H