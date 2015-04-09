#pragma once

#include "ofMain.h"
#include "CompasButton.h"

#define COMPAS_COUNT 176

class CompasSelector{

public:
	//CompasSelector();

	void setup();
	void reset();
	void update();
	void render();

	CompasButton buttons[COMPAS_COUNT];
	int activeColumn;

	int getSelectedButton(int x, int y);
	void setActiveColumn(int column);

	void mouseDragged(int button);
	void mouseMoved();
	void keyPressed(int key);
	void mousePressed(int x, int y, int button);

private:


};

