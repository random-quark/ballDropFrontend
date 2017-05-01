#include "ofMain.h"
#include "ofApp.h"
#include <string>
#include <vector>
#include "Settings.h"

#define WIDTH 500
#define HEIGHT 500

int main(int argc, char * argv[]){
	bool fullscreen = false;

	vector<string> arguments = vector<string>(argv, argv + argc);
	for(int i = 0; i < arguments.size(); ++i){
		if(arguments.at(i) == "-f"){
			fullscreen = true;
			break;
		}
	}
	
	Settings::instance()->setFullscreen(fullscreen);

	ofSetupOpenGL(WIDTH, HEIGHT, OF_WINDOW);
	ofRunApp(new ofApp());
}
