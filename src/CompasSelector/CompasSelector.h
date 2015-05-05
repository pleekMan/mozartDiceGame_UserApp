#pragma once

#include "ofMain.h"
#include "CompasButton.h"

#define COMPAS_COUNT 176 / 2 // EACH SCREEN HAS A GRID WITH HALF THE COMPASES
#define COLUMNS 8 // EACH SCREEN HAS 8 OUT OF THE 16 COLUMNS

class CompasSelector{

public:
	//CompasSelector();

	void setup(int clientID);
	void reset();
	void update();
	void render();

	ofImage& getButtonImage(int column){
		if (column < COLUMNS)
			return buttons[selectedCompases[column]].image;
	};

	CompasButton buttons[COMPAS_COUNT];
	ofPoint buttonSize;
	int activeColumn;
	int selectedCompases[COLUMNS];
	ofImage selectionBox;
	//ofPoint selectedCompasesPos[COLUMNS];

	int getSelectedButton(int x, int y); // NOT USED
	void saveSelectedButton(int x, int y); // CHECKS IF COLUMN IS ACTIVE, AND SAVES
	void setActiveColumn(int column);
	int getColumnCount();
	void toggleActiveColumn(int activeColumn);

	

	bool finishedSelecting;

	void mouseDragged(int button);
	void mouseMoved();
	void keyPressed(int key);
	void mousePressed(int x, int y, int button);

private:
	void createGrid(int clientID);
	


};

