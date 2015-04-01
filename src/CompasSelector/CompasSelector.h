#pragma once

#include "ofMain.h"
#include "CompasButton.h"

#define COMPAS_COUNT 176

class CompasSelector{

public:
	//CompasSelector();

	void setup();
	void update();
	void render();

	CompasButton buttons[COMPAS_COUNT];

	void mouseDragged(int button);
	void mouseMoved();
	void keyPressed(int key);
	void mousePressed(int x, int y, int button);

private:


};

