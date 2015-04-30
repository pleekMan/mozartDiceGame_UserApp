#include "CompasButton.h"

void CompasButton::setup(float posX, float posY, string imagePath, int _id){

	// NOT USED !!!

	id = _id;

	x = posX;
	y = posY;
	//image.loadImage("images/buttons/button" + ofToString)
	image.loadImage(imagePath);

	width = 2;
	height = 2;

	isSelected = false;

}
void CompasButton::update(){

}
void CompasButton::render(){

	ofSetColor(255);
	image.draw(x, y);

	if (!isSelected && !active){
		ofSetColor(100,0,100, 100);
		ofFill();
	}
	else {
		ofSetColor(0, 0);
		ofFill();
	}
	
	
	//ofNoFill();
	/*
	if (active)
	{
		ofNoFill();
	}
	else {
		ofFill();
	}
	*/

	ofRect(x, y, width, height);
}

void CompasButton::setPosition(float _x, float _y){
	x = _x;
	y = _y;
}

void CompasButton::setSize(float _x, float _y){
	width = _x;
	height = _y;
}

void CompasButton::setImage(string path){
	image.loadImage(path);
}

void CompasButton::setActive(bool state){
	active = state;
}

void CompasButton::toggleActive(){
	active = !active;
}

bool CompasButton::isActive(){
	return active;
}

bool CompasButton::isPointOver(ofPoint point){
	ofRectangle buttonArea;
	buttonArea.set(x, y, width, height);

	if (buttonArea.inside(point))
	{
		return true;
	}
	else{
		return false;
	}
}

