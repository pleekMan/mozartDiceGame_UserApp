#include "SceneManager.h"

void SceneManager::setup(){
	
	loadSettings();
	loadContent(clientID);
	compasSelector.setup(clientID);

	//finalProbability = 0;

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
	
	
	playHeadAnimation.setDuration(14.0); // 28 secs / 2
	playHeadAnimation.setPercentDone(0.0);
	playHeadAnimation.reset(0.0);
	playHeadAnimation.setCurve(LINEAR);
	
	int colorsAlpha = 200;
	partituraColors[0] = ofColor(64,67,122,colorsAlpha);
	partituraColors[1] = ofColor(70,137,139,colorsAlpha);
	partituraColors[2] = ofColor(70,153,110, colorsAlpha);
	partituraColors[3] = ofColor(88,163,73, colorsAlpha);
	partituraColors[4] = ofColor(180,177,78, colorsAlpha);
	partituraColors[5] = ofColor(188,123,81, colorsAlpha);
	partituraColors[6] = ofColor(195,83,83, colorsAlpha);
	partituraColors[7] = ofColor(185,82,160, colorsAlpha);

	atEjecucionCompas = 0;


	setState(0);

	enableRestart = true;
}

void SceneManager::loadSettings(){

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
		// DEFAULT TO:

		clientID = 0;

		netSender.setup("localhost", 12000);
		//netSender.setup("192.168.1.10", 12000); // (SEARCH TAG, DEFAULT, ARGUMENT NUMBER)
		netReciever.setup(12001);

		cout << "--------- SETTINGS FILE NOT LOADED, DEFAULTING: SENDER IP: LOCALHOST - 12000 " << endl;
	}

	// LOAD SETTINGS -------------- END

}

void SceneManager::loadContent(int client){

	/*
	welcomeVideo.loadMovie("videos/1 - SCREENSAVER.mov");
	welcomeVideo.play();
	welcomeVideo.setPaused(true);
	*/

	welcomeScreen.loadImage("images/splashScreen.png");

	buttonPressed.loadImage("images/welcomeButton.png");
	
	string animetaPorClient = "videos/3 - ANIMACION_client-" + ofToString(clientID) + ".mov";
	videoDidactico.loadMovie(animetaPorClient);
	videoDidactico.setLoopState(OF_LOOP_NONE);
	videoDidactico.play();
	videoDidactico.setPaused(true);
	
	/*
	partituraFinal.loadMovie("videos/4 - PARTITURA.mov");
	partituraFinal.setLoopState(OF_LOOP_NORMAL);
	partituraFinal.play();
	partituraFinal.setPaused(true);
	*/

	string ejecucionBackImage = "images/ejecucionBack_client-" + ofToString(client) + ".png";
	ejecucionBack.loadImage(ejecucionBackImage);
	partituraShadow.loadImage("images/partituraFinalShadow.png");

	string grilla = "images/grilla_" + ofToString(client) + ".png";
	grillaCompases.loadImage(grilla);

	if (clientID == 0){
		grillaPreBox.loadImage("images/SelectionPreBox_client-0.png");
	}
	else {
		grillaPreBox.loadImage("images/SelectionPreBox_client-1.png");
	}
	grillaPostBox.loadImage("images/SelectionPostBox.png");

	//partituraFinal.loadImage("images/partitura.jpg");
	//playHeadImage.loadImage("images/playHead.png");
	returnButton.loadImage("images/returnButton.jpg");

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
		
		welcomeScreen.draw(0, 0, stateLayers[SCREENSAVER].getWidth(), stateLayers[SCREENSAVER].getHeight());

		//welcomeVideo.update();
		//welcomeVideo.draw(0, 0, stateLayers[SCREENSAVER].getWidth(), stateLayers[SCREENSAVER].getHeight());

		if (layerTransition.isAnimating() && sceneState == SELECTION){
		buttonPressed.draw(1048,713);
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
		if (videoDidactico.getPosition() > 0.35){
			ofSetColor(100);
			font.drawString("Probabilidad de la secuencia elegida: ", 220, 740);
			//font.drawString(ofToString(finalProbability) + " en 45.949.729.863.572.161", 240, 790);
			font.drawString("1 en 45.949.729.863.572.161", 260, 790);
		}
		*/
		stateLayers[VIDEO_EXPLAIN].end();

	}

	if (sceneState == EXECUTION || (prevSceneState == EXECUTION && layerTransition.isAnimating())){
		
		stateLayers[EXECUTION].begin();
		ofBackground(0);
		
		ofColor(255);
		//partituraFinal.update();
		//partituraFinal.draw(0, 0);
		ejecucionBack.draw(0,0);

		ofPoint partituraAnchor = clientID == 0 ? ofPoint(96,534) : ofPoint(0,534);

		playHeadAnimation.update(1.0 / ofGetFrameRate());

		// DRAW COLOR RECTANGLES -- BEGIN
		ofRectangle rectangleSize = ofRectangle(0,0,228,127);
		atEjecucionCompas = floor((playHeadAnimation.getPercentDone() * 8));		
		float rectPosX = partituraAnchor.x + (rectangleSize.getWidth() * atEjecucionCompas);

		ofSetColor(partituraColors[atEjecucionCompas]);
		ofFill();
		ofRect(rectPosX, partituraAnchor.y,rectangleSize.getWidth(), rectangleSize.getHeight());

		partituraShadow.draw(partituraAnchor);

		// DRAW COLOR RECTANGLES -- END

		ofSetColor(0,255,127);
		ofDrawBitmapString("PlayHead at: " + ofToString(playHeadAnimation.getCurrentValue()) + " -- Compas: " + ofToString(atEjecucionCompas), 20,20);
		
		
		// DRAW PARTITURA COMPASES FROM CompasButtons IMAGES
		//int imageWidth = 205;
		for (int i = 0; i < 8; i++){
			compasSelector.getButtonImage(i).draw(partituraAnchor.x + (rectangleSize.getWidth() * i), partituraAnchor.y + 10, compasSelector.getButtonImage(i).width * 1.2,  compasSelector.getButtonImage(i).height * 1.2);
		}


		/*
		// PLAYHEAD ANIMATION - BEGIN ---------------------------------
		//playHeadAnimation.update(1.0 / ofGetFrameRate());

		float totalPartituraLength = 1660;
		float playHeadX = 30 + (totalPartituraLength * playHeadAnimation.getCurrentValue()); // initOffset + (totalPartituraLength * anim)
		float playHeadY = 380;

		
		if (playHeadAnimation.getCurrentValue() > 0.5){
			playHeadY = 550;
			playHeadX -= totalPartituraLength * 0.5;
		}
		

		//cout << ofToString(playHeadAnimation.getCurrentValue()) << endl;

		//playHeadImage.draw(playHeadX, playHeadY);

		// PLAYHEAD ANIMATION - END ---------------------------------

		*/

		if(enableRestart){
			ofSetColor(255);
			returnButton.draw(1508,722);
		}
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

		cout << "MSG RECEIVED -> ADDRESS: " << m.getAddress() << endl;

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
		if (m.getAddress() == "/probability"){
			finalProbability = m.getArgAsInt32(0);
			cout << "USER PROBABILITY: " << ofToString(finalProbability) << endl;
		}
		*/

		/*
		if (m.getAddress() == "/activeColumn"){
			cout << "ACTIVE COLUMN: " << ofToString(m.getArgAsInt32(0)) << endl;

			compasSelector.setActiveColumn(m.getArgAsInt32(0));
		}
		*/

		if (sceneState == EXECUTION){
			if (m.getAddress() == "/enableRestart"){
				enableRestart = true;
			}
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
		//partituraFinal.setPaused(true);

		//welcomeVideo.setFrame(0);
		//welcomeVideo.setPaused(false);
	}

	else if (sceneState == SELECTION)
	{
		//welcomeVideo.setPaused(true);
		compasSelector.reset();

		atPreSelection = true;
		atPostSelection = false;
	}

	else if (sceneState == VIDEO_EXPLAIN)
	{
		videoDidactico.setFrame(0);
		videoDidactico.setPaused(false);
		//videoDidactico.setFrame(0);
		//videoDidactico.play();

		//randomNumber = int(ofRandom(100, 1000));
		
	}
	else if (sceneState == EXECUTION)
	{
		videoDidactico.setPaused(true);

		//partituraFinal.setFrame(0);
		//partituraFinal.setPaused(false);

		playHeadAnimation.setPercentDone(0.0);
		playHeadAnimation.reset(0.0);

		atEjecucionCompas = 0;

		if(clientID == 0){
			playHeadAnimation.animateTo(1.0);
		} else {
			playHeadAnimation.animateToAfterDelay(1.0, playHeadAnimation.getDuration());
		}

		enableRestart = false;
		
		
	}


}

void SceneManager::setClientID(int id){
	clientID = id;
}


void SceneManager::mousePressed(int x, int y, int button)
{
	
	if (sceneState == SCREENSAVER)
	{
		ofRectangle buttonArea = ofRectangle(ofPoint(1048, 701), buttonPressed.getWidth(), buttonPressed.getHeight());
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
				cout << ofToString(compasSelector.selectedCompases[i]) + " | ";
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
		if(enableRestart){
			ofxOscMessage sendCompas;
			sendCompas.setAddress("/goToState");
			sendCompas.addIntArg(0);
			netSender.sendMessage(sendCompas);

			enableRestart = false;
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


	if (key == 's'){
		if (clientID == 1){
			atPreSelection = false;
		}
	}

}

