//
//  bird.cpp
//  AssetsDandelion
//
//  Created by Joelle Aeschlimann on 01.02.17.
//
//

#include "bird.hpp"

void bird::setup(){
    //endPosX = 2560+125;
    endPosX = 2560+125;
    
    loadImageBirds();
    

    
}

void bird::loadImageBirds(){
    
    float numberOfBirds = 5;
    
    ofImage imageBird1;
    imageBird1.load("bird/bird-01.png");
    birds.push_back(imageBird1);
    
    ofImage imageBird2;
    imageBird2.load("bird/bird-02.png");
    birds.push_back(imageBird2);
    
    ofImage imageBird3;
    imageBird3.load("bird/bird-03.png");
    birds.push_back(imageBird3);
    
    ofImage imageBird4;
    imageBird4.load("bird/bird-04.png");
    birds.push_back(imageBird4);
    
    ofImage imageBird5;
    imageBird5.load("bird/bird-05.png");
    birds.push_back(imageBird5);
    
    ofImage imageBird6;
    imageBird6.load("bird/bird-06.png");
    birds.push_back(imageBird6);
    
}

void bird::setStartSize(){
    
    float randomNumber = ofRandom(0.6,1.3);
    sizeW = 125*randomNumber;
    sizeH = 160*randomNumber;
  
}
void bird::setStartPosition(){
    startPosY = sizeH;
    startPosX = 0;
    positionBird.set(startPosX, startPosY);
    cout<<positionBird<<endl;
}

void bird::draw(){
    
    
    if(isAlive) {
        //positionBird.set(changePosition,movementPosX);
        
        int anim = int(imageAnimation);
        //150 // 192
        
        birds[anim].draw(positionBird.x,positionBird.y,sizeW,sizeH);
    
    
    }
    
}

void bird::update(){
    
    
    /*switch(){
    case 1 :
        startPosx = 0;
        endPosX = 1920;
        if(positionBird.x < endPosX){
            if(isAlive) positionBird.x += 20;
        }
        break;
        
    case 2 :
        startPosx = 1920;
        endPosX = 0;
        if(positionBird.x < endPosX){
            if(isAlive) positionBird.x -= 20;
        }
        break;
    
    }*/
    
    float time = ofGetElapsedTimef();
    
    increaseMovement = ofNoise(time);
    
    increaseMovement = ofMap(increaseMovement,0,1,-1,1);
    positionBird.y = positionBird.y +increaseMovement;
    
    if(positionBird.x < endPosX){
       if(isAlive) positionBird.x += 10;
    }else{
        isAlive = false;
        restartTimerValue = ofRandom(10,1000);
    }
    if(isAlive == false){
        if(restartTimer<restartTimerValue){
            restartTimer++;
        }else{
            restartTimer= 0;
            isAlive=true;
            setStartSize();
            setStartPosition();
        }
        
    }
    if(imageAnimation<birds.size()-1){
        imageAnimation+=0.2;
    }else{
        imageAnimation = 0;
    }

}
