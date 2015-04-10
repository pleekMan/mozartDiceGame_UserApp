#include "SceneManager.h"

void SceneManager::setup(){

	compasSelector.setup();

	netSender.setup(HOST, SERVER_PORT);
	netReciever.setup(CLIENT_PORT);

	// SET LAYERS
	for (int i = 0; i < 4; i++)
	{
		stateLayers[i].allocate(ofGetWindowWidth(), ofGetWindowHeight());
		stateLayers[i].begin();
		ofClear(0);
		stateLayers[i].end();
	}

	layerTransition.setDuration(1.0);
	layerTransition.setPercentDone(0.0);
	layerTransition.reset(0.0);
	layerTransition.setCurve(AnimCurve::EASE_IN_EASE_OUT);

	splashScreen.loadImage("images/splashScreen.png");
	grillaCompases.loadImage("images/grilla.png");

	setState(0);


}
void SceneManager::update(){

	checkNetMessages();
	layerTransition.update(1.0 / ofGetFrameRate());


	// RENDER ONLY ACTUAL AND PREVIOUS LAYERS (UNTIL RANSITION IS FINISHED) (NOT STOPPING VIDEO)
	ofSetColor(255);

	if (sceneState == SCREENSAVER || (prevSceneState == SCREENSAVER && layerTransition.isAnimating())){
		stateLayers[SCREENSAVER].begin();
		ofBackground(0);
		splashScreen.draw(0, 0);

		stateLayers[SCREENSAVER].end();
	}

	if (sceneState == SELECTION || (prevSceneState == SELECTION && layerTransition.isAnimating())){
		stateLayers[SELECTION].begin();
		ofBackground(0);

		grillaCompases.draw(0, 0);
		compasSelector.render();

		
		stateLayers[SELECTION].end();

	}
	if (sceneState == VIDEO_EXPLAIN || (prevSceneState == VIDEO_EXPLAIN && layerTransition.isAnimating())){
		stateLayers[VIDEO_EXPLAIN].begin();
		ofBackground(0);
		
		stateLayers[VIDEO_EXPLAIN].end();

	}

	if (sceneState == EXECUTION || (prevSceneState == EXECUTION && layerTransition.isAnimating())){
		stateLayers[EXECUTION].begin();
		ofBackground(0);
		
		stateLayers[EXECUTION].end();
	}


}

void SceneManager::render(){
	
	ofSetColor(255);
	stateLayers[prevSceneState].draw(0, 0, 1280, 720);
	ofSetColor(255, 255.0 * layerTransition.getCurrentValue());
	stateLayers[sceneState].draw(0, 0, 1280, 720);

}

void SceneManager::checkNetMessages(){

	while (netReciever.hasWaitingMessages()){

		ofxOscMessage m;
		netReciever.getNextMessage(&m);

		if (m.getAddress() == "/goToState"){
			cout << "GO TO STATE: " << ofToString(m.getArgAsInt32(0)) << endl;
			setState(m.getArgAsInt32(0));
			compasSelector.reset();
		}

		if (m.getAddress() == "/activeColumn"){
			cout << "ACTIVE COLUMN: " << ofToString(m.getArgAsInt32(0)) << endl;

			compasSelector.setActiveColumn(m.getArgAsInt32(0));
		}
	}

}

void SceneManager::setState(int state){
	sceneState = state;
	prevSceneState = sceneState == 0 ? 3 : sceneState - 1;


	layerTransition.setPercentDone(0.0);
	layerTransition.reset(0.0);
	layerTransition.animateTo(1.0);

	if (sceneState == SCREENSAVER)
	{
		
	}

	else if (sceneState == SELECTION)
	{
		
	}

	else if (sceneState == VIDEO_EXPLAIN)
	{

	}
	else if (sceneState == EXECUTION)
	{
		
	}


}

void SceneManager::mousePressed(int x, int y, int button)
{
	
	if (sceneState == SCREENSAVER)
	{
		ofRectangle buttonArea = ofRectangle(ofPoint(350, 520), 650, 150);
		if (buttonArea.inside(x, y))
		{
			//setState(SELECTION);
			ofxOscMessage start;
			start.setAddress("/start");
			netSender.sendMessage(start);
		}
	}

	if (sceneState == SELECTION){
		// SEND -> SELECTED COMPASS
		int selectedCompas = compasSelector.getSelectedButton(x, y);
		if (selectedCompas != -1)
		{
			ofxOscMessage sendCompas;
			sendCompas.setAddress("/compasSelection");
			sendCompas.addIntArg(selectedCompas);
			netSender.sendMessage(sendCompas);
		}
	}
	

	
}


void SceneManager::mouseDragged(int button){


}

void SceneManager::mouseMoved(){

}

void SceneManager::keyPressed(int key){

	if (key == '0'){
		setState(SCREENSAVER);
	}

	if (key == '1'){
		setState(SELECTION);
	}
	if (key == '2'){
		setState(VIDEO_EXPLAIN);
	}
	if (key == '3'){
		setState(EXECUTION);
	}

}

