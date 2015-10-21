#pragma once

#include "ofMain.h"

class CompasButton{

public:
	//CompasButton();

	void setup(float posX, float posY, string imagePath, int _id);
	void update();
	void render();

	int id;
	float x, y, width, height;
	bool active;
	bool isSelected;

	ofImage image;
	ofImage overlayInactive;
	ofImage overlaySelected;

	void setPosition(float _x, float _y);
	void setSize(float _x, float _y);
	void setImage(string path);
	void setActive(bool state);
	void toggleActive();
	bool isPointOver(ofPoint);
	bool isActive();

private:


};

