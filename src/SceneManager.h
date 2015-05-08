#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxAnimatableFloat.h"
#include "ofxXmlSettings.h"	
#include "CompasSelector/CompasSelector.h"

/*
//#define LOCALHOST_NETWORK_CONFIG

#ifdef LOCALHOST_NETWORK_CONFIG
#define HOST "localhost"
#else
#define HOST "192.168.1.10" // BROADCAST IP
#endif

#define SERVER_PORT 12000
#define CLIENT_PORT 12001
*/

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

	ofxXmlSettings settings;

	int clientID; // WHICH USER SCREEN IS IT (DETERMINES GRID COMPASES AND IT'S BACKGROUND IMAGE)
	void setClientID(int id);
	void loadContent(int client);

	CompasSelector compasSelector;

	ofxOscSender netSender;
	ofxOscReceiver netReciever;

	int sceneState;
	int prevSceneState;
	ofFbo stateLayers[4];
	bool atPreSelection;
	bool atPostSelection;

	ofxAnimatableFloat layerTransition;

	ofVideoPlayer welcomeVideo;
	ofImage buttonPressed;

	//ofImage splashScreen;
	ofImage grillaCompases;
	ofImage grillaPreBox;
	ofImage grillaPostBox;
	

	ofVideoPlayer videoDidactico;
	//ofVideoPlayer partituraRecorrida;

	ofTrueTypeFont font;
	int randomNumber;
	//int finalProbability; // SERVER CALCULATES (USING ALL 16 COMPASES) AND SENDS BACK TO CLIENTS

	ofImage partituraFinal;
	ofImage playHeadImage;
	ofxAnimatableFloat playHeadAnimation;
	ofImage returnButton;

	void setState(int state);

	void mousePressed(int x, int y, int button);
	void mouseDragged(int button);
	void mouseMoved();
	void keyPressed(int key);

private:

	void checkNetMessages();

};

