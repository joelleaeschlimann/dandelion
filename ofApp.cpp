#include "ofApp.h"

//--------------------------------------------------------------
static bool removeShapeOffScreen(shared_ptr<ofxBox2dBaseShape> shape) {
    if (!ofRectangle(0, -400, ofGetWidth(), ofGetHeight()+400).inside(shape.get()->getPosition())) {

        return true;
    }
    return false;
}

//--------------------------------------------------------------


void ofApp::setup(){
    isAnimation = true;
    
    
    ofSetVerticalSync(true);
    ofBackgroundHex(0);
    ofSetLogLevel(OF_LOG_NOTICE);
    ofDisableAntiAliasing();
    ofSetFrameRate(60);
    
    //---initialisation du monde box2d
    box2d.init();
    box2d.setFPS(60.0);
    
    //--- initialisation du serial
    bSendSerialMessage = false;
    serial.listDevices();
    
    //--- mettre entrée port du serial
    serial.setup("/dev/tty.usbmodem1421", 9600);
   // serial.setup("/dev/tty.usbserial-A6026LBJ", 9600);
    
    attractPoint2.set(ofGetWidth()/2, ofGetHeight()/2-200);
    attractPoint.set(1225, 480);
    
    
    if(isAnimation){
        bird.setup();
    }
 
    initialisationSeeds();
    createAttractors();
}

//--------------------------------------------------------------
void ofApp::update(){
    
    if(debug){
    
        ofShowCursor();
    }else{
        ofHideCursor();
    }
    readDataFromSensor();
    box2d.update();
    if(isAnimation){
        bird.update();
    }
    
    
    // attractPoint.set(ofGetWidth()/2, ofGetHeight()/2);
    attractors[0].get()->setPosition(attractPoint.x,attractPoint.y);
    
    //les éléments sont effacer dès qu'ils sortent de la fenêtre
    ofRemove(circles, removeShapeOffScreen);
    ofRemove(m_circles, removeShapeOffScreen);
    ofRemove(s_circles, removeShapeOffScreen);
    
    if((circles.size()==0) && (m_circles.size()==0) && (s_circles.size()==0)){
        isAlive = false;

    }
    if(isAlive == false && isImagesClear == false){
        images.erase( images.begin(), images.begin()+images.size() );
        m_images.erase( m_images.begin(), m_images.begin()+m_images.size() );
        s_images.erase( s_images.begin(), s_images.begin()+s_images.size() );


        isImagesClear = true;
        /*cout<<"IMAGES SIZE: "<<images.size()<<" "<<m_images.size()<<" "<<s_images.size()<<endl;
        cout<<"CIRCLES SIZE: "<<circles.size()<<" "<<m_circles.size()<<" "<<s_circles.size()<<endl;*/
    }
    
    if(isAlive == false){
        if(restartTimer < 40){
                    restartTimer++;
        }else{
            isAlive = true;
            isImagesClear = false;
            restartTimer = 0;
            initialisationSeeds();
        }
    }
    
    //detecte la force du micro et lui assigne une puissance
    float puissance;
    
    if(isAlive){
        if(dataSensor == 0){
            
            selectAnimForce(0);
        
        }else if (dataSensor > 1){
            //cout<<int(dataSensor)<<endl;
            if(dataSensor >0 && dataSensor <=2){
                selectAnimForce(2);
            }else if(dataSensor >2 && dataSensor <=4){
                selectAnimForce(3);
                
            }else if(dataSensor > 8){
                selectAnimForce(4);
            }

        }
    
    }
    
    

}

//--------------------------------------------------------------
void ofApp::draw(){
 
    if(debug){
        ofBackground(222);
    }else{
        ofBackgroundHex(0);
    }

    if(isAnimation){
        bird.draw();
    }
    
    
    for(int i=0; i<attractors.size(); i++) {
        ofFill();
        ofPushStyle();
        if(debug){
            ofSetColor(255,170);
        }else{
            ofSetColor(255,0);
        }
        attractors[i].get()->draw();
        ofPopStyle();
    }
    
    if(isAlive) {
        drawSeeds(circles,images);
        drawSeeds(m_circles,m_images);
        drawSeeds(s_circles,s_images);
    }
 }

//-----------------------------------------------------------------

void ofApp::readDataFromSensor(){
    if(bSendSerialMessage){
        serial.writeByte('a');
        unsigned char bytesReturned[NUM_BYTES];
        memset(bytesReturned, 0, NUM_BYTES);
        
        while(serial.readBytes(bytesReturned, NUM_BYTES)>0){
        }
        
        bSendSerialMessage = false;
        dataString = ofToString(bytesReturned);
        dataSensor = ofToFloat(dataString)/100;
        dataSensor = ofMap(dataSensor, 0 , 4.9 , 0, 10);
    }
    
    countCycles ++;
    if(countCycles == 5){
        bSendSerialMessage = true;
        countCycles = 0;
    }
}
//-----------------------------------------------------------------

void ofApp::selectAnimForce(int puissance){
    switch(puissance){
        case 0:
            //box2d.setGravity(0, 0);
            setLivingRotationSeed(circles,ofRandom(0.2,0.8));
            setLivingRotationSeed(m_circles,ofRandom(0.2,0.8));
            setLivingRotationSeed(s_circles,ofRandom(0.2,0.6));
            break;
        case 1 :
            //box2d.setGravity(0, 0);
            setLivingRotationSeed(circles,ofRandom(0.5,2));
            setLivingRotationSeed(m_circles,ofRandom(0.5,2));
            setLivingRotationSeed(s_circles,ofRandom(0.5,2));

           

            break;
        case 2:
            //box2d.setGravity(0, 0);
            setLivingRotationSeed(circles,ofRandom(1,4));
            setLivingRotationSeed(m_circles,ofRandom(1,4));
            setLivingRotationSeed(s_circles,ofRandom(1,4));
            
            
            break;
        case 3:
            
            setForceOnLittleBlow(circles,1);
            setForceOnLittleBlow(m_circles,1);
            setForceOnLittleBlow(s_circles,1);
            
          
            break;
        case 4:
            wind = wind-0.4;
            setGravityOnBlow();
            setForceOnBlow(circles);
            setForceOnBlow(m_circles);
            setForceOnBlow(s_circles);
            break;
            
    }
    
}
//-----------------------------------------------------------------

void ofApp::setGravityOnBlow(){
    //cout<<"GRAVITY"<<endl;
    box2d.setGravity(0.1, 5);
}

//-----------------------------------------------------------------

void ofApp::setForceOnLittleBlow(vector <shared_ptr<ofxBox2dRect> > elements, int number){
    
    float time = ofGetElapsedTimef();
    
    
   //box2d.setGravity(0.1, 3);
    if(elements.size() > 0){
        int randomNumber = ofRandom(0,elements.size());
        int numberofSeedBlow = number;
        for(int i=0;i<numberofSeedBlow;i++){
            float noisy = ofNoise(time);
            float forceX = ofMap(noisy,0,1,-2, 2);
            force.set(ofRandom(forceX,0.05),-0.3);
            //force.set(0,1);
           // elements[0].get()->addForce(force,3);
            
            elements[0].get()->addForce(force,1);

        }
    }

}
//-----------------------------------------------------------------

void ofApp::setForceOnBlow(vector <shared_ptr<ofxBox2dRect> > elements){
    
    float time = ofGetElapsedTimef();
    
    for(int i=0;i<elements.size();i++){
        float noisy = ofNoise(time)+0.4;
        float forceX = ofMap(noisy,0,1,-2, 2);
        force.set(ofRandom(forceX,0.05),-0.3);
        elements[i].get()->addForce(force,2);
    }
    
}
//-----------------------------------------------------------------

void ofApp::setLivingRotationSeed(vector <shared_ptr<ofxBox2dRect> > elements, float valRandom){

    float time = ofGetElapsedTimef();
    
    for(int a=0; a<elements.size(); a++){
        
        getRotationSeed = elements[a].get()->getRotation();
        rotation = ofNoise(time);
        float randy1 = ofRandom(0,valRandom);
        float randy2 = ofRandom(0,valRandom);
        rotation = ofMap(rotation,0,1,getRotationSeed-randy1,getRotationSeed+randy2);
        
        elements[a].get()->setRotation(rotation);
    }
}

//-----------------------------------------------------------------

void ofApp::initialisationSeeds(){
    imagePos = 0;
    imagesize =0;
   
    box2d.setGravity(0, 0);
    force.set(0,0);
    createSeeds(20,1, attractorSize+14 );
    createSeeds(14,2, attractorSize+5 );
    createSeeds(14,3,attractorSize);
    
}

void ofApp::createSeeds(float number,int idSeed, float rPosition){
    
    int rectBaseSeedSizeH = 8;
    int rectBaseSeedSizeW = 3;
    float rectBaseRadiusPosition = rPosition;
    float interval = 360/number;
    
    //---set texture
    //shapes.back().get()->setTexture(&textures[(int)ofRandom(textures.size())]);

   //--- create circle
    for(int i=0; i<number; i++) {
        
        if(angle < 360) angle = (interval*i);
        float angleRadians = ofDegToRad(angle);
        
        positionX =    rectBaseRadiusPosition*cos(ofDegToRad(angle));
        positionY =    rectBaseRadiusPosition*sin(ofDegToRad(angle));
        
        int rectBaseSeedPosition_x = positionX+attractPoint.x;
        int rectBaseSeedPosition_y = positionY+attractPoint.y;
        
        
        shared_ptr<ofxBox2dRect> circle = shared_ptr<ofxBox2dRect>(new ofxBox2dRect);
        
        //setPhysics(float density, float bounce, float friction)
        circle.get()->setPhysics(1, 0.2, 0.1);
        //circle.get()->setPhysics(3.0, 0.53, 0.1);
        //circle.get()->setVelocity(ofRandom(-30, 30), ofRandom(-30, 30));
        circle.get()->setup(box2d.getWorld(),rectBaseSeedPosition_x , rectBaseSeedPosition_y, rectBaseSeedSizeH,rectBaseSeedSizeW);
        circle.get()->setAngle(angleRadians);
       
        loadImageSeedbyId(idSeed,circle);
        
        
    }
    /*cout<<"M_IMAGES SIZE : "<<m_images.size()<<endl;
    cout<<"M_CIRCLES SIZES: "<<m_circles.size()<<endl;*/
}

void ofApp::loadImageSeedbyId(int idSeed,shared_ptr<ofxBox2dRect> circle){
    ofImage image;
    switch(idSeed){
        case 1:
            
            image.load("s001.png");
            images.push_back(image);
            circles.push_back(circle);
            
            break;
        case 2:
            
            image.load("s002.png");
            m_images.push_back(image);
            m_circles.push_back(circle);
            
            break;
        case 3:
            image.load("s004.png");
            s_images.push_back(image);
            s_circles.push_back(circle);
            
            break;
    }

}
void ofApp::drawSeeds(vector <shared_ptr<ofxBox2dRect>>shapes, vector<ofImage> tabOfImages){
    if(imagesize < 150 ){
        selectAnimForce(1);
        imagesize += 1*0.4;
        imagePos +=0.13*0.4;
    }
  
    for(int i=0; i<shapes.size(); i++) {
        
      
        
        ofFill();
        ofSetColor(255,0);
        shapes[i].get()->draw();
        
        imagePosition.set(
                          shapes[i].get()->getPosition().x,
                          shapes[i].get()->getPosition().y);
       
        ofPushMatrix();
            ofSetRectMode(OF_RECTMODE_CENTER);
            tabOfImages[i].setAnchorPoint(0, imagePos ) ;
        
            ofTranslate(imagePosition.x,imagePosition.y);
            ofRotate(90);
            ofRotate(shapes[i].get()->getRotation());
            ofSetColor(255);
        
            tabOfImages[i].draw(0,0,imagesize,imagesize);
            ofPopMatrix();
    }
}

void ofApp::createAttractors(){
    
    //--- create attractor
    float numberofAtractor = 1;
    float attractor1Position_x = ofGetWidth()/2;
    float attractor1Position_y = ofGetHeight()/2;
    
    
    for(int a=0; a<numberofAtractor; a++){
        shared_ptr<ofxBox2dCircle> attractor = shared_ptr<ofxBox2dCircle>(new ofxBox2dCircle);
        
        attractor.get()->setPhysics(0,0,0);
        attractor.get()->setup(box2d.getWorld(), attractor1Position_x,attractor1Position_y, attractorSize);
        attractors.push_back(attractor);
        
    }
}


void ofApp::keyPressed(int key) {
    
    switch(key){
        case ' ':
            if (press<1){
                press++;
                debug = true;
                
            }else {
                debug = false;
                press = 0;
                
            }
       
        case 'a':
            cout<<attractPoint<<endl;
            break;
     }
}

void ofApp::mouseDragged(int x, int y, int button){
    attractPoint2.set(ofGetMouseX(), ofGetMouseY());
    attractPoint.set(ofGetMouseX(), ofGetMouseY());
 
    if(debug){
        

    }

}








