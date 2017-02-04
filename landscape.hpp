//
//  landscape.hpp
//  AssetsDandelion
//
//  Created by Joelle Aeschlimann on 01.02.17.
//
//

#ifndef landscape_hpp
#define landscape_hpp

#include "ofMain.h"

class landscape {
    public :
    void setup();
    void draw();
    void update();
    void setPosition(ofVec2f position);
    void setSizeImage(float width, float height);
    void loadImageLandscape(int _idImage);
    float sizeW = 1920;
    float sizeH = 1080;
    
    ofImage landscape01;
    ofImage landscape02;
    
    float posx = 0;
    float posy = 0;
    
    int idImage = 0;
    
    
    
    
};


#endif /* landscape_hpp */
