#pragma once

#include "ofMain.h"
#include "CompasButton.h"

#define COMPAS_COUNT 176 / 2
#define COLUMNS 8

class CompasSelector{

public:
	//CompasSelector();

	void setup();
	void reset();
	void update();
	void render();

	CompasButton buttons[COMPAS_COUNT];
	int activeColumn;
	int selectedCompases[COLUMNS];
	ofImage selectionBox;

	int getSelectedButton(int x, int y); // NOT USED
	void saveSelectedButton(int x, int y); // CHECKS IF COLUMN IS ACTIVE, AND SAVES
	void setActiveColumn(int column);
	int getColumnCount();

	bool finishedSelecting;

	void mouseDragged(int button);
	void mouseMoved();
	void keyPressed(int key);
	void mousePressed(int x, int y, int button);

private:
	void createGrid();
	


};

