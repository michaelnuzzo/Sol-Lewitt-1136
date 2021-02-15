#pragma once

#include "ofMain.h"
#include "Graphics.h"

class ofApp : public ofBaseApp{

    public:
        void setup();
        void update();
        void draw();

        void keyPressed(int key);
        void keyReleased(int key);
        void mouseMoved(int x, int y );
        void mouseDragged(int x, int y, int button);
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);
        void mouseEntered(int x, int y);
        void mouseExited(int x, int y);
        void windowResized(int w, int h);
        void dragEvent(ofDragInfo dragInfo);
        void gotMessage(ofMessage msg);

    void drawWall();
    void drawBrush();
    void processKeys();


private:
    Brush brush; // where the current paint is being drawn
    Wall wall;
    ofEasyCam cam;
    std::map<int,long> keysPressed; // all the keys currently being pressed
    std::map<int,long> keysReleased; // all the keys within 1 second of having been released
    std::array<ofFbo,2> brushFbos;
    std::array<ofFbo,2> wallFbos;
    int nextPop = 0;
    int nextClear = 0;
    int curBrushFbo = 0;
    int curWallFbo = 0;
    float lastRotation = 0;
    float maxTurnSpeed = 0;
};