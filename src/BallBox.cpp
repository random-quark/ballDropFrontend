#include "BallBox.h"

using std::min;

BallBox::BallBox(string _name, string _color) {
    name = _name;
    color = _color;
}

void BallBox::setup(){
    ofLog() << "box is called " << name << endl;
    
	allocate(500, 500);
    
    box2d.init();
    box2d.setGravity(0, 10);
    box2d.createBounds();
    box2d.setFPS(60.0);
    box2d.registerGrabbing();

}

void BallBox::dropBalls() {
    circle_colors.clear();
    circles.clear();
}

void BallBox::newBall(){
    int adjust = int(ofRandom(50)) - 25;
    int value = std::min(230 + adjust, 255);
    if (color == "green") {
        circle_colors.push_back(ofColor(0,value,0));
    } else {
        circle_colors.push_back(ofColor(value,0,0));
    }
    
    float r = ofRandom(4, 20);		// a random radius 4px - 20px
    circles.push_back(shared_ptr<ofxBox2dCircle>(new ofxBox2dCircle));
    circles.back().get()->setPhysics(3.0, 0.53, 0.1);
    int x = ofRandom(500);
    circles.back().get()->setup(box2d.getWorld(), x, 0, r);
}

void BallBox::update(){
    box2d.update();
}

void BallBox::draw(){
    ofBackground(255);
    for(int i=0; i<circles.size(); i++) {
        ofSetColor(circle_colors[i]);
        ofFill();
        circles[i].get()->draw();
    }
}
