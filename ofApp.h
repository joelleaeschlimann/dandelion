#pragma once
#define NUM_BYTES 16
#include "ofMain.h"
#include "ofxBox2d.h"
#include "bird.hpp"
#include "cloud.hpp"


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void mouseDragged(int x, int y, int button);
        void keyPressed(int key);
    
    
        void initialisationSeeds();
        void createSeeds(float number, int idSeed,float rPosition);
        void createAttractors();
        void loadImageSeedbyId(int idSeed,shared_ptr<ofxBox2dRect> circle);
        void setLivingRotationSeed(vector <shared_ptr<ofxBox2dRect> > elements, float val);
        void setGravityOnBlow();
        void setForceOnLittleBlow(vector <shared_ptr<ofxBox2dRect> > elements,int number);
        void setForceOnBlow(vector <shared_ptr<ofxBox2dRect> > elements);
        void readDataFromSensor();
        void selectAnimForce(int puissance);
    
        void drawSeeds(vector <shared_ptr<ofxBox2dRect>>shape,vector<ofImage> tabOfImages);
    
        ofSerial serial;
        string dataString;
    
        ofxBox2d box2d;
    
        vector <shared_ptr<ofxBox2dRect> > circles;
        vector <shared_ptr<ofxBox2dRect> > m_circles;
        vector <shared_ptr<ofxBox2dRect> > s_circles;
        vector <shared_ptr<ofxBox2dCircle> > attractors;
        vector <shared_ptr<ofxBox2dCircle> > obstacles;
		
        bool bSendSerialMessage;
        bool debug = false;
        bool isImagesClear = false;
        bool isLandscape = false;
        bool isAnimation = false;
    
        float positionX;
        float positionY;
        float angle = 0;
        float attractorSize = 20;
        float isAlive = true;
        float imagesize = 4;
        float imagePos = 0;
        float wind = 10;
        float seedBlow = 0;
        float getRotationSeed = 0;
        float rotation = 0;
        float t =0;
        float dataSensor;
        int  press = 0;
    
        int countCycles;
        int numberOfElementsLeft = 0;
    int restartTimer = 0;
    
    
    //-15
        ofVec2f attractPoint;
        ofVec2f attractPoint2;
        ofVec2f imagePosition;
        ofVec2f m_imagePosition;
        ofVec2f s_imagePosition;
        ofVec2f force;
    
        vector<ofImage> images;
        vector<ofImage> m_images;
        vector<ofImage> s_images;
    bool isGrowing;
    
    vector<cloud> clouds;
    
    bird bird;
   
};
