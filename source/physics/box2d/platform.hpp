#include <box2d/box2d.h>
class box2d_Platform {
private:
    double x;
    double y;
    int width;
    int height;
    bool hasCoin;
    int coinX;
    int coinY;
    
public:
    box2d_Platform(int index);
    double getX();
    double getY();
    int getWidth();
    int getHeight();
    bool getHasCoin();
    void setHasCoin(bool value);
    int getCoinX();
    int getCoinY();
    void updatePosition();
};
