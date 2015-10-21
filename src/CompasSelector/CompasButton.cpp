#include "CompasButton.h"

void CompasButton::setup(float posX, float posY, string imagePath, int _id){

	// NOT USED !!!

	id = _id;

	x = posX;
	y = posY;
	//image.loadImage("images/buttons/button" + ofToString)
	image.loadImage(imagePath);
	overlayInactive.loadImage("images/button_inactive.png");
	overlaySelected.loadImage("images/button_selected.png");


	width = 2;
	height = 2;

	isSelected = false;

}
void CompasButton::update(){

}
void CompasButton::render(){

	ofSetColor(255);
	//ofRect(x,y,163,81);
	

	/*
	if (!isSelected && !active){
		ofSetColor(100,0,100, 100);
		ofNoFill();
	}
	else {
		ofSetColor(0, 0);
		ofNoFill();
	}
	*/

	if(isSelected){
		overlaySelected.draw(x,y,163,85);
	} else if(!active){
		overlayInactive.draw(x,y,163,85);
	}
	
	ofSetColor(255);
	image.draw(x, y, image.getWidth() * 0.5, image.getHeight() * 0.5);

	//ofRect(x, y, width, height);
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
	overlayInactive.loadImage("images/button_inactive.png");
	overlaySelected.loadImage("images/button_selected.png");
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

