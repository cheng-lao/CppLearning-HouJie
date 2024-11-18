#include<iostream.h>

using namespace std;

enum ImageType{
    LSAT, SPOT
};

class  Image
{
private:
    static Image* _prototype[10];
    static int _nextSlot;
public:
    virtual void draw() = 0;
    static Image* findAndClone(ImageType type);
protected:
    virtual ImageType returnType() = 0;
    virtual Image* clone() = 0;
    static void addPrototype(Image* image){
        Image::_prototype[Image::_nextSlot++] = image;
    }
};
Image* Image::_prototype[];
int Image::_nextSlot;


Image* Image::findAndClone(ImageType type)
{
    for(int i=0; i < Image::_nextSlot; i++)
        if(Image::_prototype[i].returnType == type)
            return Image::_prototype[i]->clone();
    return nullptr;
}

// 以上是父类的实现方式 下面是subClass的实现案例

class LandSatImage: public Image
{
public:
    ImageType returnType(){
        return LSAT;
    }

    void draw(){
        cout<<"LandSatImage::draw"<< _id<< endl;
    }

    Image* clone(){
        retuen new LandSatImage(1);
    }
    
    //有两个构造函数，一个是当初始化的时候需要将类当中的静态变量自己，加入到父类当中
    //还有一个是在父类要Clone自己的时候需要初始化一下，二者都可以是无参构造函数，所以这里
    //添加一个无关参数加以区分
protected:

    static LandSatImage _landSatIamge;
    LandSatImage(int dummy){
        _id = _count++;
    }

private:
    LandSatImage(){
        addPrototype(this);
    }

    int _id;
    static int _count;
};
LandSatImage LandSatImage::_landSatIamge;
int LandSatImaeg::_count = 1;






