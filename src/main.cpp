#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
//	ofSetupOpenGL(1920,1080,OF_FULLSCREEN);			// fullscreen (1080p)
//    ofSetupOpenGL(960,540,OF_WINDOW);            // 1080p / 2
//    ofSetupOpenGL(1280,720,OF_WINDOW);            // 720p
//    ofSetupOpenGL(1584,396,OF_WINDOW);            // linkedin
//    ofSetupOpenGL(1600,900,OF_WINDOW);            // 16:9
    ofSetupOpenGL(1195,500,OF_WINDOW);            // cinematic 






	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());
}