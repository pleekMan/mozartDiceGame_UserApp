#include "CompasSelector.h"

void CompasSelector::setup(int clientID){

	createGrid(clientID);

	selectionBox.loadImage("images/selectionBox.png");

	reset();
}

void CompasSelector::createGrid(int clientID){

	// POSITION BUTTONS
	float initPosX = 156;
	float posX = initPosX;
	float posY = 190;
	float columnSpace = 35;
	buttonSize = ofPoint(180, 70.2);

	// CREATING BUTTONS AND LOADING IMAGES FOR THIS GRID
	// GET THE INDEX OUT OF A PRERENDERED INDEX FILE
	ofBuffer compasImageIndex = ofBufferFromFile("grillaMozart.txt", true);

	for (int i = 0; i < COMPAS_COUNT; i++)
	{
		buttons[i].setPosition(posX, posY);
		buttons[i].setSize(buttonSize.x, buttonSize.y);

		//BUTTON LOADING DEPENDS ON THE CLIENT ID
		if (clientID == 0){
			// GET NUMS AS STRINGS FROM FILE
			string lineInBuffer = "images/compases/" + compasImageIndex.getNextLine() + ".jpg";
			buttons[i].setImage(lineInBuffer);
			cout << " : " << lineInBuffer << endl;

			// WHEN REACHING MAX COLUMN, RETRIEVE FROM FILE THE NEXT 8 LINES, BUT DISCARD THEM (JUST TO BURN getNextLine()s)
			if (i % COLUMNS > COLUMNS - 2){
				cout << "--" << endl;
				for (int i = 0; i<COLUMNS; i++){
					compasImageIndex.getNextLine();
				}
			}
		}
		else {

			// ON CLIENT 1, DISCARDING FILE LINES SHOULD BE DONE BEFORE RETRIEVING THE USEFUL NUMBER
			if (i % COLUMNS == 0){
				cout << "--" << endl;
				for (int i = 0; i<COLUMNS; i++){
					compasImageIndex.getNextLine();
				}
			}

			string lineInBuffer = "images/compases/" + compasImageIndex.getNextLine() + ".jpg";
			buttons[i].setImage(lineInBuffer);
			cout << " : " << lineInBuffer << endl;

			
		}

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

	// INIT INDIVIDUAL SELECTED COMPASES POSITION (1 PER COLUMN) FOR HIGHLIGHTING
	/*
	for (int i = 0; i < COLUMNS; i++)
	{
		selectedCompasesPos[i] = ofPoint(buttons[i].x, buttons[i].y);
	}
	*/
}

void CompasSelector::reset(){

	activeColumn = 0;
	finishedSelecting = false;

	for (int i = 0; i < COMPAS_COUNT; i++){
		if (i % COLUMNS == activeColumn){
			buttons[i].setActive(true);
		} else{
			buttons[i].setActive(false);
		}

		buttons[i].isSelected = false;
	}


	for (int i = 0; i < COLUMNS; i++)
	{
		selectedCompases[i] = -1;
		//selectedCompasesPos[i] = ofPoint(buttons[i].x, buttons[i].y);
		
	}

}
void CompasSelector::update(){

}
void CompasSelector::render(){

	
	for (int i = 0; i < COMPAS_COUNT; i++)buttons[i].render();
	
	ofPushStyle();
	
	// DRAW OVER INACTIVE COLUMNS
	//ofSetColor(130, 0, 130, 75);
	ofSetColor(0, 75);
	ofFill();
	
	/*
	// DRAWING COLUMNS HIGHLIGHTERS (TOP AND BOTTOM SHADOW BOXES)
	
	for (int i = 0; i < COLUMNS; i++){
		if (i != activeColumn){
			ofPoint posTop = ofPoint(selectedCompasesPos[i].x, buttons[0].y);
			ofPoint sizeTop = ofPoint(buttonSize.x, selectedCompasesPos[i].y - buttons[0].y);
			ofRect(posTop, sizeTop.x, sizeTop.y);

			ofPoint posBottom = ofPoint(selectedCompasesPos[i].x, selectedCompasesPos[i].y + buttonSize.y);
			ofPoint sizeBottom = ofPoint(buttonSize.x, (buttonSize.y * 11) - (selectedCompasesPos[i].y - buttonSize.y));
			ofRect(posBottom, sizeBottom.x, sizeBottom.y);
		}
	}
	*/
	
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
				buttons[i].isSelected = true;


				selectedCompases[activeColumn] = i;

				//selectedCompasesPos[activeColumn] = ofPoint(buttons[i].x, buttons[i].y);


				//cout << "Button Pressed: " << ofToString(i) << endl;

				if (activeColumn < COLUMNS - 1)
				{
					activeColumn++;

				}
				else {
					activeColumn = 0;
					finishedSelecting = true;
					cout << "CompasSelector Finished Selecting" << endl;
				}

				toggleActiveColumn(activeColumn);



				break;
			}
		}
	}

	for (int i = 0; i < COMPAS_COUNT; i++)
	{
		cout << ofToString(buttons[i].active) << ":" << ofToString(buttons[i].isSelected) << " - ";
		if (i % COLUMNS == 7){
			cout << endl;
		}
	}

}

void CompasSelector::toggleActiveColumn(int column){

	for (int i = 0; i < COMPAS_COUNT; i++)
	{
		if (i % COLUMNS == column)
		{
			buttons[i].setActive(true);
		}
		else {
			buttons[i].setActive(false);
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

