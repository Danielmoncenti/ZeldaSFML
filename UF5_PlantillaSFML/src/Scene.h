#pragma once

#include "Utils.h"

class Scene {
	public:
		Scene();
		~Scene();

		virtual void preLoad();
		virtual void unLoad(); //Liberar memoria sin borrar el puntero

		//Todos los hijos deberan hacer esto
		void onLoad();
		void onUpdate();
		void onRender();

		void setLoaded(bool load);
		void leaveScene();

	protected:
		virtual void init();
		virtual void enterScene();

		virtual void updateBegin();
		virtual void update();
		virtual void updateEnd();

		virtual void renderBegin();
		virtual void render();
		virtual void renderEnd();

		virtual void renderGUI();
		
		bool _SceneLoaded;
		bool _SceneEntered;

};