#pragma once

#include "ofMain.h"
#include "FboSource.h"
#include "ofxBox2d.h"

class BallBox : public ofx::piMapper::FboSource {
	public:
        BallBox(string _name, string _color);
        void setup();
		void update();
		void draw();
        void newBall();
        void dropBalls();
    private:
        string color;
        vector<ofColor> circle_colors;
        vector<shared_ptr<ofxBox2dCircle>> circles;
        ofxBox2d box2d;
};
