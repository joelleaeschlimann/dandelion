//
//  cloud.hpp
//  AssetsDandelion
//
//  Created by Joelle Aeschlimann on 01.02.17.
//
//

#ifndef cloud_hpp
#define cloud_hpp

#include "ofMain.h"

class cloud {
    public :
    void setup();
    void draw();
    void update();
    
    void loadImageClouds(int idCloud);
    void setTimerValue(int value);
    
    vector<ofImage> clouds;
    ofVec2f positionCloud;
    float imageAnimation = 0;
    float changePosition= 0;
    
    float startPosX;
    float endPosX;
    
    float movementPosY;
    float increaseMovement ;
    bool isAlive = false;
    float startTimer = 0;
    int startTimerValue = 0;
    
    
    
};

#endif /* cloud_hpp */
