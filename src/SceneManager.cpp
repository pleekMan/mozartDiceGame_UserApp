#include "SceneManager.h"

void SceneManager::setup(){
	
	// LOAD SETTINGS -------------- BEGIN
	if (settings.loadFile("settings.xml"))
	{
		clientID = int(settings.getValue("SETTINGS:clientID", 0)); // ZERO IS FOR DEFAULT VALUE IF TREE NODE NOT FOUND

		string serverIP = settings.getValue("SETTINGS:serverIP", "192.168.1.10", 0);
		int serverPort = settings.getValue("SETTINGS:servertPort", 12000, 0);
		int clientsPort = settings.getValue("SETTINGS:clientPort", 12001, 0);

		netSender.setup(serverIP, serverPort); // (SEARCH TAG, DEFAULT, ARGUMENT NUMBER)
		netReciever.setup(clientsPort);
	}
	else {
		clientID = 1;

		//netSender.setup("localhost", 12001);
		netSender.setup("192.168.1.10", 12000); // (SEARCH TAG, DEFAULT, ARGUMENT NUMBER)
		netReciever.setup(12001);

		cout << "--------- SETTINGS FILE NOT LOADED, DEFAULTING ---------" << endl;
	}

	// LOAD SETTINGS -------------- END

	loadContent(clientID);

	compasSelector.setup();

	// SET LAYERS
	for (int i = 0; i < 4; i++)
	{
		stateLayers[i].allocate(ofGetWindowWidth(), ofGetWindowHeight(), GL_RGB);
		stateLayers[i].begin();
		ofClear(0);
		stateLayers[i].end();
	}

	layerTransition.setDuration(1.0);
	layerTransition.setPercentDone(0.0);
	layerTransition.reset(0.0);
	layerTransition.setCurve(EASE_IN_EASE_OUT);

	playHeadAnimation.setDuration(35.0);
	playHeadAnimation.setPercentDone(0.0);
	playHeadAnimation.reset(0.0);
	playHeadAnimation.setCurve(LINEAR);

	setState(0);


}

void SceneManager::loadContent(int client){

	//splashScreen.loadImage("images/splashScreen.png");

	welcomeVideo.loadMovie("videos/1 - SCREENSAVER.mov");
	welcomeVideo.setPaused(true);
	buttonPressed.loadImage("images/welcomeButton.png");

	videoDidactico.loadMovie("videos/3 - ANIMACION.mov");
	videoDidactico.setLoopState(OF_LOOP_NONE);
	videoDidactico.play();
	videoDidactico.setPaused(true);
	

	//partituraRecorrida.loadMovie("videos/4 - EJECUCION.mov");
	//partituraRecorrida.setPaused(true);

	string grilla = "images/grilla_" + ofToString(client) + ".jpg";
	grillaCompases.loadImage(grilla);

	if (clientID == 0){
		grillaPreBox.loadImage("images/SelectionPreBox_A.jpg");
	}
	else {
		grillaPreBox.loadImage("images/SelectionPreBox_B.jpg");
	}
	grillaPostBox.loadImage("images/SelectionPostBox.jpg");

	partituraFinal.loadImage("images/partitura.jpg");
	playHeadImage.loadImage("images/playHead.png");
	returnButton.loadImage("images/returnButton.png");

	font.loadFont("Conduit ITC Bold.ttf", 30, true, false, false, 0.0, 0.0);

}

void SceneManager::update(){

	checkNetMessages();
	layerTransition.update(1.0 / ofGetFrameRate());

	

	// RENDER ONLY ACTUAL AND PREVIOUS LAYERS (UNTIL TRANSITION IS FINISHED) (NOT STOPPING VIDEO)
	ofSetColor(255);

	if (sceneState == SCREENSAVER || (prevSceneState == SCREENSAVER && layerTransition.isAnimating())){
		stateLayers[SCREENSAVER].begin();
		ofBackground(0);
		//splashScreen.draw(0, 0, stateLayers[SCREENSAVER].getWidth(), stateLayers[SCREENSAVER].getHeight());

		welcomeVideo.update();
		welcomeVideo.draw(0, 0, stateLayers[SCREENSAVER].getWidth(), stateLayers[SCREENSAVER].getHeight());

		if (layerTransition.isAnimating() && sceneState == SELECTION){
		buttonPressed.draw(494, 793);
		}

		stateLayers[SCREENSAVER].end();
	}

	if (sceneState == SELECTION || (prevSceneState == SELECTION && layerTransition.isAnimating())){
		stateLayers[SELECTION].begin();
		ofClear(0);

		grillaCompases.draw(0, 0, stateLayers[SELECTION].getWidth(), stateLayers[SELECTION].getHeight());
		compasSelector.render();

		ofSetColor(255);
		if (atPreSelection)
		{
			grillaPreBox.draw(0, 0);
		}
		else if (atPostSelection)
		{
			grillaPostBox.draw(0, 0);
		}
		
		stateLayers[SELECTION].end();

	}
	if (sceneState == VIDEO_EXPLAIN || (prevSceneState == VIDEO_EXPLAIN && layerTransition.isAnimating())){
		
		stateLayers[VIDEO_EXPLAIN].begin();

		ofBackground(0);
		
		ofColor(255);
		videoDidactico.update();
		videoDidactico.draw(0, 0, stateLayers[VIDEO_EXPLAIN].getWidth(), stateLayers[VIDEO_EXPLAIN].getHeight());
		
		/*
		if (videoDidactico.getIsMovieDone() && !videoDidactico.isPaused()){
			videoDidactico.setPaused(true);
			setState(EXECUTION);
		}
		*/

		if (videoDidactico.getPosition() > 0.2){
			ofSetColor(100);
			font.drawString("Probabilidad de la secuencia elegida: ", 220, 740);
			font.drawString(ofToString(randomNumber) + " en 45.949.729.863.572.161", 240, 790);
		}
		
		stateLayers[VIDEO_EXPLAIN].end();

	}

	if (sceneState == EXECUTION || (prevSceneState == EXECUTION && layerTransition.isAnimating())){
		stateLayers[EXECUTION].begin();
		ofBackground(0);
		
		ofColor(255);
		partituraFinal.draw(0, 0);

		// PLAYHEAD ANIMATION - BEGIN ---------------------------------
		playHeadAnimation.update(1.0 / ofGetFrameRate());

		float totalPartituraLength = 3350;
		float playHeadX = 40 + (totalPartituraLength * playHeadAnimation.getCurrentValue()); // initOffset + (totalPartituraLength * anim)
		float playHeadY = 300;

		if (playHeadAnimation.getCurrentValue() > 0.5){
			playHeadY = 550;
			playHeadX -= totalPartituraLength * 0.5;
		}

		//cout << ofToString(playHeadAnimation.getCurrentValue()) << endl;

		playHeadImage.draw(playHeadX, playHeadY);

		// PLAYHEAD ANIMATION - END ---------------------------------

		returnButton.draw(0, 0);


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

		cout << "RECEIVED MESSAGE WITH ADDRESS: " << m.getAddress() << endl;

		if (m.getAddress() == "/goToState"){
			int incomingState = m.getArgAsInt32(0);
			cout << "GO TO STATE: " << ofToString(incomingState) << endl;
			
			setState(incomingState);

			//if(incomingState == SELECTION)compasSelector.reset();
		}

		if (sceneState == SELECTION){
			if (m.getAddress() == "/unlockScreen" && clientID == 1){
				atPreSelection = false;
			}
		}

		/*
		if (m.getAddress() == "/activeColumn"){
			cout << "ACTIVE COLUMN: " << ofToString(m.getArgAsInt32(0)) << endl;

			compasSelector.setActiveColumn(m.getArgAsInt32(0));
		}
		*/
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
		welcomeVideo.play();
	}

	else if (sceneState == SELECTION)
	{
		compasSelector.reset();

		atPreSelection = true;
		atPostSelection = false;
	}

	else if (sceneState == VIDEO_EXPLAIN)
	{
		videoDidactico.setFrame(0);
		videoDidactico.setPaused(false);

		randomNumber = int(ofRandom(100, 1000));
		
	}
	else if (sceneState == EXECUTION)
	{
		//partituraRecorrida.play();
		playHeadAnimation.setPercentDone(0.0);
		playHeadAnimation.reset(0.0);
		playHeadAnimation.animateTo(1.0);
		
	}


}

void SceneManager::setClientID(int id){
	clientID = id;
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

		if (clientID == 0){
			if (atPreSelection)
			{
				atPreSelection = false;
			}
			else {
				compasSelector.mousePressed(x, y, button);
			}
		}
		else {
			if (!atPreSelection)
			{
				compasSelector.mousePressed(x, y, button);
			}
		}

		// IF FINISHED SELECTING	
		if (compasSelector.finishedSelecting){
			ofxOscMessage sendCompas;
			sendCompas.setAddress("/compasSelection");
			sendCompas.addIntArg(clientID);
			for (int i = 0; i < compasSelector.getColumnCount(); i++)
			{
				sendCompas.addIntArg(compasSelector.selectedCompases[i]);
			}
			netSender.sendMessage(sendCompas);
			cout << "COMPASES SELECTED MESSAGE SENT" << endl;

			atPostSelection = true;

		}

		// SEND -> SELECTED COMPASS

		/*
		int selectedCompas = compasSelector.getSelectedButton(x, y);
		if (selectedCompas != -1)
		{
			ofxOscMessage sendCompas;
			sendCompas.setAddress("/compasSelection");
			sendCompas.addIntArg(clientID);
			sendCompas.addIntArg(selectedCompas);
			netSender.sendMessage(sendCompas);
		
		}
		*/
	}

	if (sceneState == VIDEO_EXPLAIN){

		//videoDidactico.setPaused(false);
		videoDidactico.setFrame(0);
		//videoDidactico.play();

		// SEND -> SELECTED COMPASS
			ofxOscMessage sendCompas;
			sendCompas.setAddress("/goToState");
			sendCompas.addIntArg(3);
			netSender.sendMessage(sendCompas);
	}
	if (sceneState == EXECUTION){
		// SEND -> SELECTED COMPASS
			ofxOscMessage sendCompas;
			sendCompas.setAddress("/goToState");
			sendCompas.addIntArg(0);
			netSender.sendMessage(sendCompas);
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

