//
//  Graphics.h

//  mySketch
//
//  Created by Michael Nuzzo on 5/13/20.
//

#ifndef Graphics_h
#define Graphics_h

#include "ofMain.h"

const int RED = 0xc11a2e;
const int ORANGE = 0xe24f2d;
const int YELLOW = 0xebd438;
const int GREEN = 0x5ea61c;
const int BLUE = 0x0c6dce;
const int INDIGO = 0xabafb0;
const int VIOLET = 0x5847a5;


const std::array<int,7> UNIQUE_CLRS
{
    RED,
    ORANGE,
    YELLOW,
    GREEN,
    BLUE,
    VIOLET,
    INDIGO
};

const std::array<int,9> BRUSH_SEQ
{
    VIOLET,
    ORANGE,
    GREEN,
    YELLOW,
    RED,
    INDIGO,
    BLUE,
    GREEN,
    RED
};

class Wall
{
public:
    void initialize(int w);
    void draw();
    void move();
    inline ofPath getStrips() {return strips;}
    inline float getCenters() {return stripCenters;}
    inline float getStripWidth() {return stripWidth;}
    ofColor pickUniqueColor();

private:
    ofPath strips; // the bands of color
    float stripCenters; // the locations of each color strip
    float stripWidth = 0; // the width of each color strip
    std::deque<int> forbiddenColors; // stores color info to select the next color
};

/* ----------------------------------------------------------------- */

class Brush
{
public:
    void initialize(int numRays, int w);
    void turn(float rotation_);
    void accelerateRotation(float speed);
    void draw();
    void move();
    inline void setCenter(glm::vec2 ctr) {center = ctr;}
    inline void setVelocity(float v) {velocity = v;}
    inline void setAngle(float a) {angle = a;}
    inline glm::vec2 getCenter() {return center;}
    inline float getVelocity() {return velocity;}
    inline float getAngle() {return angle;}
    inline float getRotation() {return rotation;}
    inline float getWidth() {return brushWidth;}
    inline float getStripWidth() {return stripWidth;}
    ofColor pickUniqueColor();


private:
    glm::vec2 center = glm::vec2(0,0); // where the brush's center is being drawn
    float angle = -90; // the current angle of the brush
    float rotation = 0; // used to remember the last rotation speed
    float rotationSpeed = 1; // multiplier to speed and slow the brush (0 < x < 1)
    float velocity = 1; // the forward velocity of the brush
    float brushWidth = 0; // the full width of the brush
    float stripWidth = 0; // the width of each color of the brush
    float stripLength = 0; // the length of each color of the brush
    std::vector<ofPath> strips; // the elements that make up the brush
    std::deque<int> forbiddenColors; // stores color info to select the next color

};

#endif /* Graphics_h */
