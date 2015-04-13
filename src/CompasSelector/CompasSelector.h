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
	int selectedCompases[16];
	ofImage selectionBox;

	int getSelectedButton(int x, int y);
	void setActiveColumn(int column);

	bool finishedSelecting();

	void mouseDragged(int button);
	void mouseMoved();
	void keyPressed(int key);
	void mousePressed(int x, int y, int button);

private:
	void createGrid();


};

