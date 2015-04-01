#pragma once

#include "ofMain.h"
#include "CompasSelector/CompasSelector.h"

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

	void mousePressed(int x, int y, int button);
	void mouseDragged(int button);
	void mouseMoved();
	void keyPressed(int key);

private:


};

