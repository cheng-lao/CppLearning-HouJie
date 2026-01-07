#include "SingleTon.h"
#include <thread>
#include <chrono>

// ============================================
// 测试函数：演示单例模式的唯一性
// ============================================
void testBasicSingleton() {
    std::cout << "\n========== 测试1: 基础单例模式 ==========" << std::endl;
    
    // 多次获取实例，验证返回的是同一个对象
    A& instance1 = A::getInstance();
    A& instance2 = A::getInstance();
    A& instance3 = A::getInstance();
    
    std::cout << "\n验证单例的唯一性：" << std::endl;
    instance1.showAddress();
    instance2.showAddress();
    instance3.showAddress();
    
    std::cout << "\n所有引用指向同一个对象: " 
              << (&instance1 == &instance2 && &instance2 == &instance3) 
              << std::endl;
    
    instance1.setup();
    instance2.setup();
    instance3.setup();
    
    std::cout << "========================================\n" << std::endl;
}

// ============================================
// 测试函数：配置管理器使用场景
// ============================================
void testConfigManager() {
    std::cout << "\n========== 测试2: 配置管理器单例 ==========" << std::endl;
    
    // 模拟不同模块访问配置管理器
    std::cout << "\n[模块A] 设置数据库配置：" << std::endl;
    ConfigManager::getInstance().setConfig("db_host", "localhost");
    ConfigManager::getInstance().setConfig("db_port", "3306");
    
    std::cout << "\n[模块B] 读取配置：" << std::endl;
    ConfigManager::getInstance().getConfig("app_name");
    ConfigManager::getInstance().getConfig("db_host");
    
    std::cout << "\n[模块C] 修改配置：" << std::endl;
    ConfigManager::getInstance().setConfig("debug_mode", "true");
    ConfigManager::getInstance().getConfig("debug_mode");
    
    std::cout << "\n[系统] 显示所有配置：" << std::endl;
    ConfigManager::getInstance().showAllConfigs();
    
    // 验证是同一个实例
    std::cout << "验证：不同模块访问的是同一个配置管理器实例" << std::endl;
    ConfigManager& config1 = ConfigManager::getInstance();
    ConfigManager& config2 = ConfigManager::getInstance();
    std::cout << "config1 地址: " << &config1 << std::endl;
    std::cout << "config2 地址: " << &config2 << std::endl;
    std::cout << "是同一个实例: " << (&config1 == &config2) << std::endl;
    
    std::cout << "========================================\n" << std::endl;
}

// ============================================
// 测试函数：日志管理器使用场景
// ============================================
void testLogger() {
    std::cout << "\n========== 测试3: 日志管理器单例 ==========" << std::endl;
    
    // 模拟不同模块使用日志系统
    std::cout << "\n[用户模块] 记录用户操作：" << std::endl;
    Logger::getInstance().log("用户模块", "用户登录成功");
    Logger::getInstance().log("用户模块", "用户修改密码");
    
    std::cout << "\n[订单模块] 记录订单操作：" << std::endl;
    Logger::getInstance().log("订单模块", "创建新订单 #1001");
    Logger::getInstance().log("订单模块", "订单支付成功");
    
    std::cout << "\n[支付模块] 记录支付操作：" << std::endl;
    Logger::getInstance().log("支付模块", "处理支付请求");
    Logger::getInstance().log("支付模块", "支付完成");
    
    std::cout << "\n[系统] 查看所有日志：" << std::endl;
    Logger::getInstance().showAllLogs();
    
    // 验证是同一个实例
    std::cout << "验证：不同模块使用的是同一个日志管理器实例" << std::endl;
    Logger& logger1 = Logger::getInstance();
    Logger& logger2 = Logger::getInstance();
    std::cout << "logger1 地址: " << &logger1 << std::endl;
    std::cout << "logger2 地址: " << &logger2 << std::endl;
    std::cout << "是同一个实例: " << (&logger1 == &logger2) << std::endl;
    
    std::cout << "========================================\n" << std::endl;
}

// ============================================
// 测试函数：模拟多线程场景（简单演示）
// ============================================
void testMultiThreadScenario() {
    std::cout << "\n========== 测试4: 多模块并发访问场景 ==========" << std::endl;
    
    std::cout << "\n模拟场景：多个模块同时访问配置管理器" << std::endl;
    
    // 模拟模块1
    std::cout << "\n[线程1-网络模块] 访问配置：" << std::endl;
    ConfigManager::getInstance().setConfig("server_port", "8080");
    ConfigManager::getInstance().getConfig("server_port");
    
    // 模拟模块2
    std::cout << "\n[线程2-数据库模块] 访问配置：" << std::endl;
    ConfigManager::getInstance().setConfig("db_name", "mydb");
    ConfigManager::getInstance().getConfig("db_name");
    
    // 模拟模块3
    std::cout << "\n[线程3-缓存模块] 访问配置：" << std::endl;
    ConfigManager::getInstance().setConfig("cache_size", "1024");
    ConfigManager::getInstance().getConfig("cache_size");
    
    std::cout << "\n所有模块共享同一个配置管理器实例" << std::endl;
    ConfigManager::getInstance().showAllConfigs();
    
    std::cout << "========================================\n" << std::endl;
}

// ============================================
// 测试函数：演示单例的生命周期
// ============================================
void testSingletonLifecycle() {
    std::cout << "\n========== 测试5: 单例生命周期 ==========" << std::endl;
    
    std::cout << "\n第一次获取单例实例：" << std::endl;
    A& a1 = A::getInstance();
    a1.showAddress();
    
    std::cout << "\n第二次获取单例实例（应该返回同一个对象）：" << std::endl;
    A& a2 = A::getInstance();
    a2.showAddress();
    
    std::cout << "\n单例对象在程序结束时自动销毁（析构函数会被调用）" << std::endl;
    std::cout << "========================================\n" << std::endl;
}

// ============================================
// 主函数：运行所有测试
// ============================================
int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "    单例模式 (Singleton Pattern) 测试" << std::endl;
    std::cout << "========================================" << std::endl;
    
    // 运行所有测试
    testBasicSingleton();
    testConfigManager();
    testLogger();
    testMultiThreadScenario();
    testSingletonLifecycle();
    
    std::cout << "\n========================================" << std::endl;
    std::cout << "    所有测试完成！" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "\n注意：单例对象会在程序结束时自动销毁" << std::endl;
    std::cout << "（析构函数会在 main 函数返回后调用）" << std::endl;
    
    return 0;
}