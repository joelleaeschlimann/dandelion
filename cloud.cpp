//
//  cloud.cpp
//  AssetsDandelion
//
//  Created by Joelle Aeschlimann on 01.02.17.
//
//

#include "cloud.hpp"

void cloud::setup(){

    startPosX = -400;
    endPosX = 3000+125;
    int randyCloud = ofRandom(1,3);
    loadImageClouds(1);
    movementPosY = ofRandom(100,400);
    positionCloud.set(startPosX,movementPosY);
    changePosition = startPosX;
    //startTimerValue = ofRandom(10,5000);
    
    isAlive = false;
}

void cloud::setTimerValue(int value){
    startTimerValue = value;
}

void cloud::loadImageClouds(int idCloud){
    
    ofImage cloud1;
    int randy = ofRandom(1,3);
    string urlimage ="nuages/nuage-0"+ofToString(randy)+".png";
    cloud1.load(urlimage);
    clouds.push_back(cloud1);  
}

void cloud::draw(){
    
    
    if(isAlive)positionCloud.set(changePosition,movementPosY);
    
    ofPushStyle();
    ofSetColor(255,100);
    clouds[0].draw(positionCloud.x,positionCloud.y);
    ofPopStyle();
    
    
}

void cloud::update(){
    
    
    if(positionCloud.x < endPosX){
        if(isAlive==true){
            
            changePosition+=0.1;
        }
    }else{
        isAlive = false;
        movementPosY = ofRandom(0,150);
        changePosition = startPosX;
        
    }
    
    if(isAlive == false){
        
        if(startTimer<startTimerValue){
            startTimer++;

        }else{
            startTimer= 0;
            isAlive=true;
        }
        
    }
   
    
}
