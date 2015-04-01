#include "CompasSelector.h"

void CompasSelector::setup(){

	// INIT BUTTONS
	for (int i = 0; i < COMPAS_COUNT; i++)
	{
		buttons[i].setup(0.0, 0.0, "images/buttons/button_" + ofToString(i), i);
	}

	// POSITION BUTTONS
	float posX = 20;
	float posY = 20;
	for (int i = 0; i < COMPAS_COUNT; i++)
	{
		buttons[i].setPosition(posX, posY);

		cout << ofToString(buttons[i].x) + " - " + ofToString(buttons[i].y) << endl;

		if (posX > (ofGetWindowWidth() - 100))
		{
			posX = 20;
			posY += buttons[i].height;
		}
		else {
			posX += buttons[i].width;
		}

		
	}
}
void CompasSelector::update(){

}
void CompasSelector::render(){

	for (int i = 0; i < COMPAS_COUNT; i++)
	{
		buttons[i].render();
	}

}

void CompasSelector::mousePressed(int x, int y, int button)
{
	for (int i = 0; i < COMPAS_COUNT; i++)
	{
		if (buttons[i].isPointOver(ofPoint(ofGetMouseX(),ofGetMouseY()))){
			buttons[i].toggleActive();
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

