#include "CompasSelector.h"

void CompasSelector::setup(){

	createGrid();

	for (int i = 0; i < 16; i++)
	{
		selectedCompases[i] = 0;
	}

	selectionBox.loadImage("images/selectionBox.png");

	reset();
}

void CompasSelector::createGrid(){

	// POSITION BUTTONS
	float initPosX = 156;
	float posX = initPosX;
	float posY = 187;
	float columnSpace = 17.25;
	ofPoint buttonSize = ofPoint(89.3, 70.5);

	for (int i = 0; i < COMPAS_COUNT; i++)
	{
		buttons[i].setPosition(posX, posY);
		buttons[i].setSize(buttonSize.x, buttonSize.y);

		//cout << ofToString(buttons[i].x) + " - " + ofToString(buttons[i].y) << endl;

		if (i % 16 == (16 - 1) && i > 1)
		{
			posX = initPosX;
			posY += buttonSize.y;
		}
		else {
			posX += buttonSize.x + columnSpace;
		}


	}

}

void CompasSelector::reset(){
	activeColumn = 0;
	for (int i = 0; i < COMPAS_COUNT; i++){
		buttons[i].setActive(false);
	}
}
void CompasSelector::update(){

}
void CompasSelector::render(){

	/*
	for (int i = 0; i < COMPAS_COUNT; i++)
	{
		buttons[i].render();
	}
	*/

	ofPushStyle();
	
	// DRAW OVER INACTIVE COLUMNS
	ofSetColor(130,0,130, 75);
	ofFill();
	
	//ofSetColor(255,5,5);
	//ofNoFill();
	
	for (int i = 0; i < 16; i++){
		if (i != activeColumn){
			ofPoint pos = ofPoint(buttons[i].x, buttons[0].y);
			ofPoint size = ofPoint(buttons[0].width, buttons[0].height * 11);
			ofRect(pos, size.x, size.y);
		}
	}

	ofSetColor(255);
	selectionBox.draw(156 + activeColumn * (buttons[0].width + 17.25) - 33, 0);

	ofPopStyle();

}

int CompasSelector::getSelectedButton(int x, int y){

	int selected = -1;

	for (int i = 0; i < COMPAS_COUNT; i++)
	{
		// CHECK IF THE BUTTON PRESSED BELONGS TO THE ACTIVE COLUMN
		if (i % 16 == activeColumn){
			// CHECK POINER OVER BUTTON
			if (buttons[i].isPointOver(ofPoint(x, y))){
				buttons[i].toggleActive();
				selected = i;
				cout << "Button Pressed: " << ofToString(i) << endl;
				break;
			}
		}
	}


	return selected;
}

void CompasSelector::setActiveColumn(int column){
	activeColumn = column;
}

bool CompasSelector::finishedSelecting(){
	return false;
}

void CompasSelector::mousePressed(int x, int y, int button)
{
	for (int i = 0; i < COMPAS_COUNT; i++)
	{
		if (buttons[i].isPointOver(ofPoint(ofGetMouseX(), ofGetMouseY()))){
			buttons[i].toggleActive();
			break;
		}
	}
}

void CompasSelector::mouseDragged(int button){



}

void CompasSelector::mouseMoved(){

}

void CompasSelector::keyPressed(int key){

	if (key == '1'){
	}
}

