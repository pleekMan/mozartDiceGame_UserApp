#include "CompasButton.h"

void CompasButton::setup(float posX, float posY, string imagePath, int _id){

	id = _id;

	x = posX;
	y = posY;
	//image.loadImage("images/buttons/button" + ofToString)
	image.loadImage(imagePath);

	
		width = 50;
		height = 30;



}
void CompasButton::update(){

}
void CompasButton::render(){

	ofSetColor(255, 0, 0);
	if (active)
	{
		ofNoFill();
	}
	else {
		ofFill();
	}
	
	ofRect(x, y, width, height);
}

void CompasButton::setPosition(float _x, float _y){
	x = _x;
	y = _y;
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

