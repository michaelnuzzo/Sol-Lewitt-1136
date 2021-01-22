#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofHideCursor();

    // set the number of brush strokes and the total brush width
    brush.initialize(9,ofGetHeight()/3.f);
    // set the initial position of the brush
    brush.setCenter(glm::vec2(0, 2*ofGetHeight()/3.f));
    brush.setVelocity(ofGetWidth()/600.f);

    maxTurnSpeed = 105*brush.getVelocity()/brush.getWidth();

    // the width of the wall rectangles should be equal to the width of the brush strokes
    wall.initialize(brush.getStripWidth());

    // set up the camera
    cam.removeAllInteractions();
    cam.setupPerspective();
    cam.enableOrtho();
    cam.setVFlip(true);

    // set up the fbos
    for(auto& elem : brushFbos)
        elem.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA, 2);
    for(auto& elem : wallFbos)
        elem.allocate(ofGetWidth()+(2*brush.getStripWidth()), ofGetHeight(), GL_RGBA, 2);

    // initialize which fbos to write into
    curBrushFbo = brush.getCenter().x/ofGetWidth();
    curWallFbo = wall.getCenters()/ofGetWidth();

    // draw the initial wall
    for(int i = 0; i < (ofGetWidth()/wall.getStripWidth())+1; i++)
        drawWall();

    // initialize the tracking for when to add more strips to the wall
    nextPop = cam.getPosition().x;
    nextClear = ofGetWidth()*2/3.f;
}

//--------------------------------------------------------------
void ofApp::update(){

    processKeys();

    float relativeBrushStart = brush.getCenter().x - cam.getPosition().x + ofGetWidth()/2.f;
    float xVelocity = sin(-ofDegToRad(brush.getAngle()))*brush.getVelocity();
    // move camera with brush when at 2/3s of way across canvas
    if(relativeBrushStart > ofGetWidth()*2/3.f && xVelocity > 0)
        cam.move(xVelocity,0,0);
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();
    // if the camera has progressed one rectangle width across the wall from the last addition
    if(cam.getPosition().x > nextPop)
    {
        drawWall();
        nextPop += wall.getStripWidth();
    }
    // clear the other buffer when we hit the 2/3s point of the current buffer
    if(brush.getCenter().x > nextClear )
    {
        brushFbos.at((curBrushFbo+1)%2).begin();
        ofClear(0, 0, 0, 0);
        brushFbos.at((curBrushFbo+1)%2).end();

        nextClear += ofGetWidth();
    }

    drawBrush();

    wallFbos.at(curWallFbo%2).draw(curWallFbo * wallFbos[0].getWidth(),0);
    wallFbos.at((curWallFbo+1)%2).draw((curWallFbo-1) * wallFbos[0].getWidth(),0);
    wallFbos.at((curWallFbo+1)%2).draw((curWallFbo+1) * wallFbos[0].getWidth(),0);

    brushFbos.at(curBrushFbo%2).draw(curBrushFbo * ofGetWidth(),0);
    brushFbos.at((curBrushFbo+1)%2).draw((curBrushFbo-1) * ofGetWidth(),0);
    brushFbos.at((curBrushFbo+1)%2).draw((curBrushFbo+1) * ofGetWidth(),0);

    cam.end();
}

void ofApp::processKeys()
{
    bool L = keysPressed.find(OF_KEY_LEFT) != keysPressed.end();
    bool R = keysPressed.find(OF_KEY_RIGHT) != keysPressed.end();
    bool U = keysPressed.find(OF_KEY_UP) != keysPressed.end();
    bool D = keysPressed.find(OF_KEY_DOWN) != keysPressed.end();
    bool xL = keysReleased.find(OF_KEY_LEFT) != keysReleased.end();
    bool xR = keysReleased.find(OF_KEY_RIGHT) != keysReleased.end();

//    // automatic movement override
//    float speed = cos(2*ofDegToRad(ofGetFrameNum()));
//    brush.turn(maxTurnSpeed * ((speed < 0) - (0 < speed)));


    float easingFunction; // this helps transition the rotation from the initial key press

    if (L)
    {
        easingFunction = tanh(2.f*(ofGetElapsedTimef() - keysPressed[OF_KEY_LEFT]));
        brush.turn(-maxTurnSpeed * easingFunction);
    }
    if (R)
    {
        easingFunction = tanh(2.f*(ofGetElapsedTimef() - keysPressed[OF_KEY_RIGHT]));
        brush.turn(maxTurnSpeed * easingFunction);
    }
    if (R && L)
    {
        brush.turn(0);
    }
    if (!R && !L)
    {
        // Used for soft transitions upon key release
        float upTime;
        if(xL)
            upTime = keysReleased[OF_KEY_LEFT];
        else if(xR)
            upTime = keysReleased[OF_KEY_RIGHT];

        easingFunction = 1-tanh(2.f*(ofGetElapsedTimef() - upTime));
        brush.turn(lastRotation*easingFunction);
    }
    if (U)
    {
        brush.accelerateRotation(.01);
    }
    if (D)
    {
        brush.accelerateRotation(-.01);
    }

    // when a key is released, remember which key it was for 1 second
    auto it = keysReleased.begin();
    while (it != keysReleased.end())
    {
      if((ofGetElapsedTimef() - it->second) > 1)
          it = keysReleased.erase(it);
      else
        ++it;
    }

}

void ofApp::drawWall(){
    wallFbos.at(curWallFbo%2).begin();
    ofPushMatrix();
    ofTranslate(-(curWallFbo * wallFbos[0].getWidth()), 0);
    wall.draw();
    ofPopMatrix();
    wallFbos.at(curWallFbo%2).end();

    if(int(wall.getCenters()) % int(wallFbos[0].getWidth()) < wall.getStripWidth())
    {
        wallFbos.at((curWallFbo+1)%2).begin();
        ofPushMatrix();
        ofTranslate(-((curWallFbo-1) * wallFbos[0].getWidth()), 0);
        wall.draw();
        ofPopMatrix();
        wallFbos.at((curWallFbo+1)%2).end();
    }
    else if(int(wall.getCenters()) % int(wallFbos[0].getWidth()) > ofGetWidth() - wall.getStripWidth())
    {
        wallFbos.at((curWallFbo+1)%2).begin();
        ofPushMatrix();
        ofTranslate(-((curWallFbo+1) * wallFbos[0].getWidth()), 0);
        wall.draw();
        ofPopMatrix();
        wallFbos.at((curWallFbo+1)%2).end();
    }
    wall.move();
    curWallFbo = wall.getCenters()/wallFbos[0].getWidth();
}

void ofApp::drawBrush(){
    // draw the brush
    brushFbos.at(curBrushFbo%2).begin();
    ofPushMatrix();
    ofTranslate(-(curBrushFbo * ofGetWidth()), 0);
    brush.draw();
    ofPopMatrix();
    brushFbos.at(curBrushFbo%2).end();

    // if you are within the left boundary, draw into the previous buffer
    if(int(brush.getCenter().x) % ofGetWidth() < brush.getWidth()/2.f)
    {
        brushFbos.at((curBrushFbo+1)%2).begin();
        ofPushMatrix();
        ofTranslate(-((curBrushFbo-1) * ofGetWidth()), 0);
        brush.draw();
        ofPopMatrix();
        brushFbos.at((curBrushFbo+1)%2).end();
    }
    // if you are within the right boundary, draw into the next buffer
    else if(int(brush.getCenter().x) % ofGetWidth() > ofGetWidth() - brush.getWidth()/2.f)
    {
        brushFbos.at((curBrushFbo+1)%2).begin();
        ofPushMatrix();
        ofTranslate(-((curBrushFbo+1) * ofGetWidth()), 0);
        brush.draw();
        ofPopMatrix();
        brushFbos.at((curBrushFbo+1)%2).end();
    }
    brush.move();
    curBrushFbo = brush.getCenter().x/ofGetWidth();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    // Save key & time it was pressed
    if(keysPressed.find(key) == keysPressed.end())
        keysPressed[key] = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
    // Save key that was just released
    keysPressed.erase(key);
    keysReleased[key] = ofGetElapsedTimef();
    lastRotation = brush.getRotation();
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
