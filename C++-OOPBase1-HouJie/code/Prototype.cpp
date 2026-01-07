#include <iostream>
#include <vector>
#include <string>
#include <map> // 使用 map 来代替固定大小的数组，更灵活地注册原型
using namespace std;
// ------------------------------------
// 1. Component (基类 - 抽象图像)
// ------------------------------------
class Image {
protected:
    // 通常原型模式会包含一些状态，这里我们用一个ID来区分
    std::string id; 

public:
    Image(std::string _id = "Unknown") : id(_id) {}
    virtual ~Image() { 
        std::cout << "  - Destructing Image: " << id << std::endl; 
    }

    // 核心：虚拷贝（Virtual Constructor）接口
    // 每个子类都必须实现如何克隆自己
    virtual Image* clone() const = 0; 

    // 用于显示图像类型
    virtual void displayType() const {
        std::cout << "Image Type: " << id << std::endl;
    }

    // ------------------------------------
    // 2. Prototype Manager (原型管理器) - 静态方法和数据
    // ------------------------------------
    // 这里用 map 来存储原型，键是字符串ID，值是原型对象指针
    static std::map<std::string, Image*> prototypes;    //管理器

    // 注册原型：将一个原型实例添加到管理器中
    static void addPrototype(Image* proto) {
        prototypes[proto->id] = proto;
        std::cout << "Registered Prototype: " << proto->id << std::endl;
    }

    // 通过ID查找并克隆原型
    static Image* createById(const std::string& typeId) {
        auto it = prototypes.find(typeId);
        if (it != prototypes.end()) {
            std::cout << "Cloning from prototype: " << typeId << std::endl;
            return it->second->clone(); // 调用找到的原型实例的 clone() 方法
        } else {
            std::cout << "Error: Prototype " << typeId << " not found!" << std::endl;
            return nullptr;
        }
    }
};

// 静态成员变量的定义和初始化
std::map<std::string, Image*> Image::prototypes;

// ------------------------------------
// 3. Concrete Prototype (具体原型类 - 卫星图像)
// ------------------------------------
class LandSatImage : public Image {
private:
//构造函数设置成私有类型
    LandSatImage(): Image("LandSat") {
        // cout << "LandSatImage::Constructor" << endl;
        Image::addPrototype(&prototypeInstance);
    }
    LandSatImage(int): Image("LandSat"){
        count++;
    }
    // 这是实现 clone() 的关键，创建一个新的 LandSatImage 对象
    Image* clone() const override {
        return new LandSatImage();
    }
    static int count;
    static LandSatImage prototypeInstance;
public:
    void displayType() const override {
        std::cout << "LandSat Image (ID: " << id << ") - Specialized satellite data." << std::endl;
    }
};
int LandSatImage::count = 0;
LandSatImage LandSatImage::prototypeInstance;  
//必须要在类外面再定义一下 这个静态成员变量才能正常初始化，执行构造函数

// ------------------------------------
// 4. Concrete Prototype (具体原型类 - 聚光图像)
// ------------------------------------
class SpotImage : public Image {
private:
    SpotImage(): Image("Spot") {
        // 同理，这里注册的是一个静态的 SpotImage 实例
        Image::addPrototype(&SpotImage::prototypeInstance);
    }
    SpotImage(int):Image("Spot"){
        
    }
    Image* clone() const override {
        return new SpotImage();
    }
    static int count;
    static SpotImage prototypeInstance;
public:
    void displayType() const override {
        std::cout << "Spot Image (ID: " << id << ") - High resolution imagery." << std::endl;
    }
};
int SpotImage::count = 0;
SpotImage SpotImage::prototypeInstance;

// ------------------------------------
// Main 函数 - 客户端代码
// ------------------------------------
int main() {
    std::cout << "--- Prototype Pattern Example ---" << std::endl << std::endl;

    // 客户端不需要知道具体的图像类名，只需要知道其ID
    std::cout << "Requesting a LandSat Image..." << std::endl;

    Image* myLandSatImage = Image::createById("LandSat");
    if (myLandSatImage) {
        myLandSatImage->displayType();
    }

    std::cout << "\nRequesting a Spot Image..." << std::endl;
    Image* mySpotImage = Image::createById("Spot");
    if (mySpotImage) {
        mySpotImage->displayType();
    }

    std::cout << "\nRequesting another LandSat Image..." << std::endl;
    Image* anotherLandSatImage = Image::createById("LandSat");
    if (anotherLandSatImage) {
        anotherLandSatImage->displayType();
    }

    std::cout << "\nAttempting to create an unregistered image type..." << std::endl;
    Image* unknownImage = Image::createById("Radar");

    std::cout << "\n--- Cleaning up ---" << std::endl;
    // 记得释放通过 new 创建的对象，防止内存泄漏
    delete myLandSatImage;
    delete mySpotImage;
    delete anotherLandSatImage;
    // delete unknownImage; // 如果创建失败，它会是 nullptr

    // 清理原型管理器中注册的静态原型实例（可选，因为它们是静态的，程序结束时会自动销毁）
    // 如果原型实例不是静态的，这里就需要手动删除
    // for (auto const& [key, val] : Image::prototypes) {
    //     // 这里我们注册的是静态实例的地址，所以不需要手动删除
    //     // delete val; 
    // }
    Image::prototypes.clear();

    return 0;
}