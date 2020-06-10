//
//  Graphics.cpp
//  mySketch
//
//  Created by Michael Nuzzo on 5/13/20.
//

#include "Graphics.h"

// YOU MUST CALL THIS PROPERTY BEFORE USING THE WALL.
// Start the wall and specify the strip widths.
void Wall::initialize(int w)
{
    strips.clear();
    forbiddenColors.clear();
    
    // width of each strip
    stripWidth = w;

    strips.rectangle(0,0,stripWidth,ofGetHeight());
    strips.setColor(pickUniqueColor());
    stripCenters = 0;
}

// Draw the current strip
void Wall::draw()
{
    ofPushMatrix();
    ofTranslate(stripCenters,0);
    strips.draw();
    ofPopMatrix();
}

// Generate a new strip
void Wall::move()
{
    stripCenters += stripWidth;
    strips.setColor(pickUniqueColor());
}

// Sol Lewitt's 1136 seems to have a pattern about when to
// repeat colors. It looks to me like no colors can be
// adjacent and none can be two away either. This function
// selects a "random" color based on that criteria.
ofColor Wall::pickUniqueColor()
{
    const int MIN_DISTANCE = 3;
    int color;
    bool match;
    do
    {
        // pick a color from the palette
        color = UNIQUE_CLRS[int(ofRandom(UNIQUE_CLRS.size()))];
        // see if it's been picked recently
        match = std::find(forbiddenColors.begin(), forbiddenColors.end(), color) != forbiddenColors.end();
        // continue til you find a color that hasnt been used recently
    }
    while(match);
    // remember the picked color as a recently picked color
    forbiddenColors.push_back(color);
    // trim the "recently picked" list
    if(forbiddenColors.size() > MIN_DISTANCE-1)
        forbiddenColors.pop_front();

    return ofColor::fromHex(color);
}

/* ----------------------------------------------------------------- */

// YOU MUST CALL THIS PROPERTY BEFORE USING THE BRUSH.
// Start the brush and specify the number of strips and the brush width.
void Brush::initialize(int numStrips, int w)
{
    center = glm::vec2(0,0);
    angle = -90;
    rotation = 0;
    rotationSpeed = 1;
    velocity = 1;
    strips.clear();

    // total brush width
    brushWidth = w;
    // total strip width
    stripWidth = brushWidth/numStrips;
    stripLength = stripWidth/5.f;

    // add all the strips to the brush
    for(int i = 0; i < numStrips; i++)
    {
        ofPath rect;
        rect.rectangle(0,0,stripWidth,stripLength);
        if(numStrips == 9)
            rect.setColor(ofColor::fromHex(BRUSH_SEQ[numStrips-1-i]));
        else
            rect.setColor(pickUniqueColor());

        strips.push_back(rect);
    }
}

ofColor Brush::pickUniqueColor()
{
    const int MIN_DISTANCE = 3;
    int color;
    bool match;
    do
    {
        // pick a color from the palette
        color = UNIQUE_CLRS[int(ofRandom(UNIQUE_CLRS.size()))];
        // see if it's been picked recently
        match = std::find(forbiddenColors.begin(), forbiddenColors.end(), color) != forbiddenColors.end();
        // continue til you find a color that hasnt been used recently
    }
    while(match);
    // remember the picked color as a recently picked color
    forbiddenColors.push_back(color);
    // trim the "recently picked" list
    if(forbiddenColors.size() > MIN_DISTANCE-1)
        forbiddenColors.pop_front();

    return ofColor::fromHex(color);
}

// turn the brush
void Brush::turn(float rotation_)
{
    // depends on the current brush speed
    angle = angle + (rotation_ * rotationSpeed);
    rotation = rotation_;
}

// accelerate the turning
void Brush::accelerateRotation(float speed)
{
    // cap max speed at 1, and min speed at 0
    rotationSpeed = ofClamp(rotationSpeed+speed,0,1);
}

// Draw the current brush.
void Brush::draw()
{
    ofPushMatrix();
    ofTranslate(center);
    ofRotateZDeg(angle);

    for(int i = 0; i < strips.size(); i++)
    {
        ofPushMatrix();
        ofTranslate(-brushWidth/2.f,-stripLength/2.f);
        ofTranslate(stripWidth*i,0);
        strips[i].draw();
        ofPopMatrix();
    }
    ofPopMatrix();
}

// Move the brush coordinates according to speed & location
void Brush::move()
{
    // move the brush according to velocity and angle
    glm::vec2 move = glm::vec2(velocity,0);
    move = glm::rotate(move,glm::radians(angle+90));
    setCenter(center+move);
}
