#pragma once

#include "Renderer.h"
#include "ResourceManager.h"
#include "input.h"
#include "SceneDirector.h"
#include "SoundManager.h"

void initSingletons();

extern Renderer* sRenderer;
extern Input* sInput;
extern ResourceManager* sResManager;
extern SceneDirector* sDirector;
extern SoundManager* sSoundManager;