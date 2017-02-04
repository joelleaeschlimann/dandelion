//
//  landscape.cpp
//  AssetsDandelion
//
//  Created by Joelle Aeschlimann on 01.02.17.
//
//

#include "landscape.hpp"
void landscape::setup(){
    
    
}

void landscape::loadImageLandscape(int _idImage){
    idImage = _idImage;
    switch(idImage){
        case 1:
            landscape01.load("landscape/landscape-02.png");
            break;
        case 2:
            cout<<"loloaidjoaf"<<endl;
            landscape01.load("landscape/landscape-01.png");

            break;
    
    }
}

void landscape::draw(){
    landscape01.draw(posx,posy,sizeW,sizeH);
}


void landscape::update(){
    
  
}
