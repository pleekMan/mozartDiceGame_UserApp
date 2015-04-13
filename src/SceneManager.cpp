#include "SceneManager.h"

void SceneManager::setup(){

	compasSelector.setup();

	netSender.setup(HOST, SERVER_PORT);
	netReciever.setup(CLIENT_PORT);

	// SET LAYERS
	for (int i = 0; i < 4; i++)
	{
		stateLayers[i].allocate(ofGetWindowWidth(), ofGetWindowHeight(), GL_RGB);
		stateLayers[i].begin();
		ofClear(0);
		stateLayers[i].end();
	}

	layerTransition.setDuration(0.2);
	layerTransition.setPercentDone(0.0);
	layerTransition.reset(0.0);
	layerTransition.setCurve(AnimCurve::EASE_IN_EASE_OUT);

	splashScreen.loadImage("images/splashScreen.png");
	grillaCompases.loadImage("images/grilla.png");

	videoDidactico.loadMovie("videos/3 - ANIMACION.mov");
	videoDidactico.setPaused(true);

	partituraRecorrida.loadMovie("videos/4 - EJECUCION.mov");
	partituraRecorrida.setPaused(true);

	setState(0);


}
void SceneManager::update(){

	checkNetMessages();
	layerTransition.update(1.0 / ofGetFrameRate());


	// RENDER ONLY ACTUAL AND PREVIOUS LAYERS (UNTIL TRANSITION IS FINISHED) (NOT STOPPING VIDEO)
	ofSetColor(255);

	if (sceneState == SCREENSAVER || (prevSceneState == SCREENSAVER && layerTransition.isAnimating())){
		stateLayers[SCREENSAVER].begin();
		ofBackground(0);
		splashScreen.draw(0, 0, stateLayers[SCREENSAVER].getWidth(), stateLayers[SCREENSAVER].getHeight());

		stateLayers[SCREENSAVER].end();
	}

	if (sceneState == SELECTION || (prevSceneState == SELECTION && layerTransition.isAnimating())){
		stateLayers[SELECTION].begin();
		ofClear(0);

		grillaCompases.draw(0, 0, stateLayers[SELECTION].getWidth(), stateLayers[SELECTION].getHeight());
		compasSelector.render();

		
		stateLayers[SELECTION].end();

	}
	if (sceneState == VIDEO_EXPLAIN || (prevSceneState == VIDEO_EXPLAIN && layerTransition.isAnimating())){
		
		stateLayers[VIDEO_EXPLAIN].begin();

		ofBackground(0);
		
		ofColor(255);
		videoDidactico.update();
		videoDidactico.draw(0, 0, stateLayers[VIDEO_EXPLAIN].getWidth(), stateLayers[VIDEO_EXPLAIN].getHeight());

		stateLayers[VIDEO_EXPLAIN].end();

	}

	if (sceneState == EXECUTION || (prevSceneState == EXECUTION && layerTransition.isAnimating())){
		stateLayers[EXECUTION].begin();
		ofBackground(0);
		
		ofColor(255);
		partituraRecorrida.update();
		partituraRecorrida.draw(0, 0, stateLayers[EXECUTION].getWidth(), stateLayers[EXECUTION].getHeight());

		stateLayers[EXECUTION].end();
	}


}

void SceneManager::render(){
	
	//ofPushMatrix();
	//ofScale(1.5, 1.5);
	ofPushStyle();

	ofSetColor(255,255);
	stateLayers[prevSceneState].draw(0, 0);
	ofSetColor(255, 255.0 * layerTransition.getCurrentValue());

	stateLayers[sceneState].draw(0, 0);

	ofPopStyle();

	//ofDrawBitmapString(ofToString(layerTransition.getCurrentValue()), 20, 20);
	//ofPopMatrix();
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
		videoDidactico.play();
	}
	else if (sceneState == EXECUTION)
	{
		partituraRecorrida.play();
	}


}

void SceneManager::mousePressed(int x, int y, int button)
{
	
	if (sceneState == SCREENSAVER)
	{
		ofRectangle buttonArea = ofRectangle(ofPoint(500, 780), 900, 300);
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

