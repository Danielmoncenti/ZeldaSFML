#include "Scene.h"
#include "singletons.h"

Scene::Scene() {
	_SceneLoaded = false;
	_SceneEntered = false;

}

Scene::~Scene() {

}

void Scene::onLoad() {
	if (!_SceneLoaded) {
		init();
		setLoaded(true);
	}
	if (!_SceneEntered) {
		_SceneEntered = true;
		enterScene();
	}
}

void Scene::onUpdate() {
	if (!_SceneLoaded) { return; }
	updateBegin();
	update();
	updateEnd();
}

void Scene::onRender() {
	if (!_SceneLoaded) { return; }

	//Actua como un Update()
	//Pintar cosas
	sRenderer->windowClear();

	renderBegin();
	render();
	renderEnd();
	renderGUI();

	//Acabo de pintar cosas
	sRenderer->windowRefresh();
}

void Scene::setLoaded(bool load) {
	_SceneLoaded = load;
}

void Scene::leaveScene() {
	_SceneEntered = false;
}

void Scene::preLoad() {

}

void Scene::unLoad() {

}

void Scene::init() {

}

void Scene::enterScene() {

}

void Scene::updateBegin() {

}

void Scene::update() {

}

void Scene::updateEnd() {

}

void Scene::renderBegin() {

}

void Scene::render() {

}

void Scene::renderEnd() {

}

void Scene::renderGUI() {

}
