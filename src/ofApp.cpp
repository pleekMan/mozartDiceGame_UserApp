#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	ofSetBackgroundAuto(true);
	ofEnableAlphaBlending();
	//ofBlendMode(OF_BLENDMODE_ADD);
	ofBackground(0);

	sceneManager.setup();
}

//--------------------------------------------------------------
void ofApp::update(){

	sceneManager.update();

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0);
	sceneManager.render();

	ofSetColor(255, 0, 0);
	ofDrawBitmapString(ofToString(ofGetMouseX()) + " | " + ofToString(ofGetMouseY()), ofGetMouseX() + 10, ofGetMouseY() - 10);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	sceneManager.keyPressed(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	sceneManager.mouseMoved();
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	sceneManager.mouseDragged(button);
	
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	sceneManager.mousePressed(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
