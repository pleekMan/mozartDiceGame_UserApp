#include "SceneManager.h"

void SceneManager::setup(){

	compasSelector.setup();

	netSender.setup(HOST, SERVER_PORT);
	netReciever.setup(CLIENT_PORT);

}
void SceneManager::update(){

	checkNetMessages();

}

void SceneManager::render(){
	compasSelector.render();

}

void SceneManager::checkNetMessages(){

	while (netReciever.hasWaitingMessages()){

		ofxOscMessage m;
		netReciever.getNextMessage(&m);

		if (m.getAddress() == "/goToState"){
			cout << "GO TO STATE: " << ofToString(m.getArgAsInt32(0)) << endl;
			compasSelector.reset();
		}

		if (m.getAddress() == "/activeColumn"){
			cout << "ACTIVE COLUMN: " << ofToString(m.getArgAsInt32(0)) << endl;

			compasSelector.setActiveColumn(m.getArgAsInt32(0));
		}
	}

}
void SceneManager::mousePressed(int x, int y, int button)
{
	//compasSelector.mousePressed(x, y, button);
	
	int selected = compasSelector.getSelectedButton(x, y);

	if (selected != -1){

		ofxOscMessage m;
		m.setAddress("/compasSelection");
		m.addIntArg(selected);
		netSender.sendMessage(m);
	}
}


void SceneManager::mouseDragged(int button){


}

void SceneManager::mouseMoved(){

}

void SceneManager::keyPressed(int key){

	if (key == '1'){


	}

}

