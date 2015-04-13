#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxAnimatableFloat.h"
#include "CompasSelector/CompasSelector.h"

#define HOST "192.168.2.1"
#define SERVER_PORT 10000
#define CLIENT_PORT 10001

enum SceneState{
	SCREENSAVER,
	SELECTION,
	VIDEO_EXPLAIN,
	EXECUTION
};


class SceneManager{

public:
	//SceneManager();

	void setup();
	void update();
	void render();

	CompasSelector compasSelector;

	ofxOscSender netSender;
	ofxOscReceiver netReciever;

	int sceneState;
	int prevSceneState;
	ofFbo stateLayers[4];

	ofxAnimatableFloat layerTransition;

	ofImage splashScreen;
	ofImage grillaCompases;

	ofVideoPlayer videoDidactico;
	ofVideoPlayer partituraRecorrida;

	void setState(int state);

	void mousePressed(int x, int y, int button);
	void mouseDragged(int button);
	void mouseMoved();
	void keyPressed(int key);

private:

	void checkNetMessages();

};

