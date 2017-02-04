//
//  bird.hpp
//  AssetsDandelion
//
//  Created by Joelle Aeschlimann on 01.02.17.
//
//

#ifndef bird_hpp
#define bird_hpp

#include "ofMain.h"

class bird {
    public :
    void setup();
    void draw();
    void update();
    
    void loadImageBirds();
    void setStartSize();
    void setStartPosition();
    
    vector<ofImage> birds;
    ofVec2f positionBird;
    float imageAnimation = 0;
    float changePosition= 0;
    
    float startPosX;
    float endPosX;
    
    float movementPosY;
    float startPosY;
    float increaseMovement ;
    bool isAlive = false;
    float restartTimer = 0;
    int restartTimerValue = 0;
    
    float sizeW = 0;
    float sizeH = 0;
    
    
    

};

#endif /* bird_hpp */
