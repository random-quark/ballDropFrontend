#include "ofApp.h"

void ofApp::setup(){
    receiver.setup( PORT );
        
	ofBackground(0);

	// Enable or disable audio for video sources globally
	// Set this to false to save resources on the Raspberry Pi
	ofx::piMapper::VideoSource::enableAudio = true;
	ofx::piMapper::VideoSource::useHDMIForAudio = false;

	// Add our CustomSource to list of fbo sources of the piMapper
	// FBO sources should be added before piMapper.setup() so the
	// piMapper is able to load the source if it is assigned to
	// a surface in XML settings.
	ballBox1 = new BallBox("Box 1", "green");
    ballBox2 = new BallBox("Box 2", "red");
	piMapper.registerFboSource(ballBox1);
    piMapper.registerFboSource(ballBox2);
	piMapper.setup();

	// The info layer is hidden by default, press <i> to toggle
	// piMapper.showInfo();
	
	ofSetFullscreen(Settings::instance()->getFullscreen());
}

void ofApp::update(){
    getNewMessages();
    
	piMapper.update();
}

void ofApp::dropBall(int type) {
    string color;
    if (type == 0) {
        ballBox1->newBall();
    } else if (type == 1) {
        ballBox2->newBall();
    }
}

void ofApp::getNewMessages() {
    while(receiver.hasWaitingMessages()) {
        ofxOscMessage m;
        receiver.getNextMessage( &m );
        if ( m.getAddress() == "/positive" ) {
            dropBall(0);
        }
        if (m.getAddress() == "/negative") {
            dropBall(1);
        }
        if (m.getAddress() == "/reset") {
            ballBox1->dropBalls();
            ballBox2->dropBalls();
        }
    }
}

void ofApp::draw(){
	piMapper.draw();
}

void ofApp::keyPressed(int key){
	piMapper.keyPressed(key);
}

void ofApp::keyReleased(int key){
	piMapper.keyReleased(key);
    if (key=='b') {
        dropBall(0);
        dropBall(1);
    }
}

void ofApp::mousePressed(int x, int y, int button){
    piMapper.mousePressed(x, y, button);
}

void ofApp::mouseReleased(int x, int y, int button){
    piMapper.mouseReleased(x, y, button);
}

void ofApp::mouseDragged(int x, int y, int button){
    piMapper.mouseDragged(x, y, button);
}
