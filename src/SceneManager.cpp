#include "SceneManager.h"

void SceneManager::setup(){

	compasSelector.setup();
}
void SceneManager::update(){

}
void SceneManager::render(){
	compasSelector.render();

}
void SceneManager::mousePressed(int x, int y, int button)
{
	compasSelector.mousePressed(x, y, button);
}


void SceneManager::mouseDragged(int button){


}

void SceneManager::mouseMoved(){

}

void SceneManager::keyPressed(int key){

	if (key == '1'){
	}

}

