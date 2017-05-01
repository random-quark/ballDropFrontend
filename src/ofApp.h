#pragma once

#include "ofMain.h"
#include "Settings.h"
#include "ofxPiMapper.h"
#include "BallBox.h"
#include "VideoSource.h"
#include "ofxOsc.h"
#include "ofxBox2d.h"

#define PORT 12345


class ofApp : public ofBaseApp {
	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);

		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseDragged(int x, int y, int button);
            
		ofxPiMapper piMapper;

		// By using a custom source that is derived from FboSource
		// you will be able to see the source listed in sources editor
		BallBox * ballBox1;
        BallBox * ballBox2;
    private:
        ofxOscReceiver receiver;
        void getNewMessages();
        void dropBall(int type);
};
