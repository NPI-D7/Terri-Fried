#include <vector>

typedef struct {
    double x;
    double y;
} Vector2;

class box2d_Player {
private:
    double x;
    double y;
    int width;
    int height;
    bool onPlatform;
    Vector2 velocity;
    
public:
    box2d_Player(double x, double y, int width, int height);
    double getX();
    double getY();
    void setX(int x);
    void setY(int y);
    int getWidth();
    int getHeight();
    bool isOnGround();
    bool isOnPlatform();
    void setOnPlatform(bool result);
    void setVelocity(double x, double y);
    Vector2 getVelocity();
    void updatePosition();
};
