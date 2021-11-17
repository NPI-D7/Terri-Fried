#include "platform.hpp"
#include <math.h>

const int screenWidth = 400;
const int screenHeight = 240;

Platform::Platform(int index) {
    width = 100/2;
    height = 32/2;
    
    x = rand()% 660/2 + 20/2;
    y = 0 - height - (index * 100/2);
    
    int coinInt = rand()% 5;
    
    if (coinInt == 0 || index == 0)
        hasCoin = false;
    else
        hasCoin = true;
    
    coinX = x + width/2 - (24/2)/2;
    coinY = y - 24/2 - 3;
}

double Platform::getX() {
    return x;
}

double Platform::getY() {
    return y;
}

int Platform::getWidth() {
    return width;
}

int Platform::getHeight() {
    return height;
}

bool Platform::getHasCoin() {
    return hasCoin;
}

void Platform::setHasCoin(bool value) {
    hasCoin = value;
}

int Platform::getCoinX() {
    return coinX;
}

int Platform::getCoinY() {
    return coinY;
}

void Platform::updatePosition() {
    y+=0.5;
    
    coinX = x + width/2 - (24/2)/2;
    coinY = y - 24/2 - 3;
    
    if (y > screenHeight) {
        x = rand()% 660/2 + 20/2;
        y = 0 - height;
        
        int coinInt = rand()% 5;
        
        if (coinInt == 0)
            hasCoin = false;
        else
            hasCoin = true;
    }
}
