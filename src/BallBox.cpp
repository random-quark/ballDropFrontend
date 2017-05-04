#include "BallBox.h"
#include "ofUtils.h"

#define DEBUG false

using std::min;

BallBox::BallBox(string _name, string _color) {
    name = _name;
    color = _color;
}

void BallBox::setup(){
    ofLog() << "box is called " << name << endl;
    
    wall.load("wall.jpg");
    
	allocate(960, 637);
    
    box2d.init();
    box2d.setGravity(0, 10);
    box2d.createBounds(0,0,960,637);
    box2d.setFPS(60.0);
    box2d.registerGrabbing();
    
    std::vector<float> pts { 149,314,155,587,353,588,354,314,149,314 };
    float b = 481.0;
    std::vector<float> pts2 { 149+b,310,155+b,587,353+b,588,354+b,310,149+b,310 };

    createEdge(pts);
    createEdge(pts2);
}

void BallBox::createEdge(std::vector<float> pts) {
    ofPolyline debugLine;
    shared_ptr <ofxBox2dEdge> edge = shared_ptr<ofxBox2dEdge>(new ofxBox2dEdge);
    for (int j=0; j<pts.size(); j+=2) {
        float x = pts[j];
        float y = pts[j+1];
        edge.get()->addVertex(x, y);
        
        debugLine.addVertex(x, y);
    }
    edge.get()->create(box2d.getWorld());
    edges.push_back(edge);
    debugLines.push_back(debugLine);
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
    int x = ofRandom(960);
    circles.back().get()->setup(box2d.getWorld(), x, 0, r);
}

void BallBox::update(){
    box2d.update();
}

void BallBox::draw(){
    ofBackground(255);
    wall.draw(0,0);
    
    if (DEBUG) {
        for (int i=0; i<debugLines.size(); i++) {
            debugLines[i].draw();
        }
    }
        
    for(int i=0; i<circles.size(); i++) {
        ofSetColor(circle_colors[i]);
        ofFill();
        circles[i].get()->draw();
    }
}
