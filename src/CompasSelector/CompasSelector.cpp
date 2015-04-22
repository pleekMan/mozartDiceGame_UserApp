#include "CompasSelector.h"

void CompasSelector::setup(){

	createGrid();

	selectionBox.loadImage("images/selectionBox.png");

	reset();
}

void CompasSelector::createGrid(){

	// POSITION BUTTONS
	float initPosX = 156;
	float posX = initPosX;
	float posY = 190;
	float columnSpace = 35;
	ofPoint buttonSize = ofPoint(180, 70.2);

	for (int i = 0; i < COMPAS_COUNT; i++)
	{
		buttons[i].setPosition(posX, posY);
		buttons[i].setSize(buttonSize.x, buttonSize.y);

		//cout << ofToString(buttons[i].x) + " - " + ofToString(buttons[i].y) << endl;

		if (i % COLUMNS == (COLUMNS - 1) && i > 1)
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
	finishedSelecting = false;

	for (int i = 0; i < COMPAS_COUNT; i++){
		buttons[i].setActive(false);
	}

	for (int i = 0; i < COLUMNS; i++)
	{
		selectedCompases[i] = -1;
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
	//ofSetColor(130, 0, 130, 75);
	ofSetColor(0, 75);
	ofFill();
	
	//ofSetColor(255,5,5);
	//ofNoFill();
	
	for (int i = 0; i < COLUMNS; i++){
		if (i != activeColumn){
			ofPoint pos = ofPoint(buttons[i].x, buttons[0].y);
			ofPoint size = ofPoint(buttons[0].width, buttons[0].height * 11);
			ofRect(pos, size.x, size.y);
		}
	}

	ofSetColor(255);
	selectionBox.draw(156 + activeColumn * (buttons[0].width + 35) - 47, 0);

	ofPopStyle();

}

int CompasSelector::getSelectedButton(int x, int y){ // NOT USED

	int selected = -1;

	for (int i = 0; i < COMPAS_COUNT; i++)
	{
		// CHECK IF THE BUTTON PRESSED BELONGS TO THE ACTIVE COLUMN
		if (i % COLUMNS == activeColumn){
			// CHECK POINTER OVER BUTTON
			if (buttons[i].isPointOver(ofPoint(x, y))){
				//buttons[i].toggleActive();
				selected = i;
				cout << "Button Pressed: " << ofToString(i) << endl;
				break;
			}
		}
	}


	return selected;
}

void CompasSelector::saveSelectedButton(int x, int y){

	for (int i = 0; i < COMPAS_COUNT; i++)
	{
		// CHECK IF THE BUTTON PRESSED BELONGS TO THE ACTIVE COLUMN
		if (i % COLUMNS == activeColumn){
			// CHECK POINTER OVER BUTTON
			if (buttons[i].isPointOver(ofPoint(x, y))){
				buttons[i].toggleActive();
				selectedCompases[activeColumn] = i;
				
				cout << "Button Pressed: " << ofToString(i) << endl;

				if (activeColumn < COLUMNS - 1)
				{
					activeColumn++;
				}
				else {
					activeColumn = 0;
					finishedSelecting = true;
				}

				
				break;
			}
		}
	}

}

void CompasSelector::setActiveColumn(int column){
	activeColumn = column;
}

int CompasSelector::getColumnCount(){
	return COLUMNS;
}


void CompasSelector::mousePressed(int x, int y, int button)
{

	saveSelectedButton(x, y);

	/*
	for (int i = 0; i < COMPAS_COUNT; i++)
	{
		if (buttons[i].isPointOver(ofPoint(ofGetMouseX(), ofGetMouseY()))){
			buttons[i].toggleActive();
			break;
		}
	}
	*/
}

void CompasSelector::mouseDragged(int button){



}

void CompasSelector::mouseMoved(){

}

void CompasSelector::keyPressed(int key){

	if (key == '1'){
	}
}

