#include "SoundManager.h"

SoundManager* SoundManager::instance = NULL;
SoundManager* SoundManager::getInstance() {
	if (!instance) {
		instance = new SoundManager();
	}
	return instance;
}

SoundManager::SoundManager() {
	if (instance != NULL) { return; }
	_CurrentSoundIndex = 0;
	_SoundVector.resize(MAX_SOUNDS, NULL);
	_CurrentBGM = NULL;
}

SoundManager::~SoundManager() {

}

void SoundManager::playMusic(const char* filepath) {
	if (_CurrentBGM != NULL) { musicStop(); }
	_CurrentBGM = new sf::Music();
	if (!_CurrentBGM->openFromFile(filepath)) {
		std::cout << "Error opening music " << filepath << std::endl;
		return;
	}
	_CurrentBGM->play();
	_CurrentBGM->setLoop(true);
}

void SoundManager::musicPause() {
	if (_CurrentBGM == NULL) { return; }
	if (musicIsPlaying()) {
		_CurrentBGM->pause();
	}
}

void SoundManager::musicResume() {
	if (_CurrentBGM == NULL) { return; }
	if (!musicIsPlaying()) {
		_CurrentBGM->play();
	}
}

void SoundManager::musicStop() {
	if (_CurrentBGM == NULL) { return; }
	_CurrentBGM->stop();
	delete(_CurrentBGM);
	_CurrentBGM = NULL;
}

bool SoundManager::musicIsPlaying() {
	if (_CurrentBGM == NULL) { return false; }

	return _CurrentBGM->getStatus() == sf::Sound::Playing;
}

int SoundManager::playSound(const char* filepath, bool loop) {
	sf::SoundBuffer* buffer = getBuffer(filepath);
	if (_SoundVector[_CurrentSoundIndex] != NULL) {
		updateSoundFirstFreeSlot();
	}
	int soundID = _CurrentSoundIndex;
	_SoundVector[soundID] = new sf::Sound();
	_SoundVector[soundID]->setBuffer(*buffer);
	_SoundVector[soundID]->play();
	_SoundVector[soundID]->setLoop(loop);
	updateSoundFirstFreeSlot();

	return soundID;
}

void SoundManager::loadSound(const char* filepath) {
	getBuffer(filepath);
}

void SoundManager::soundPause(int soundID) {
	if (soundID < 0 || soundID >= MAX_SOUNDS) { return; }
	if (_SoundVector[soundID] == NULL) { return; }

	if (soundIsPlaying(soundID)) {
		_SoundVector[soundID]->pause();
	}
}

void SoundManager::soundResume(int soundID) {
	if (soundID < 0 || soundID >= MAX_SOUNDS) { return; }
	if (_SoundVector[soundID] == NULL) { return; }

	if (soundIsPlaying(soundID)) {
		_SoundVector[soundID]->play();
	}
}

void SoundManager::soundStop(int soundID) {
	if (soundID < 0 || soundID >= MAX_SOUNDS) { return; }
	if (_SoundVector[soundID] == NULL) { return; }

	_SoundVector[soundID]->stop();
	delete(_SoundVector[soundID]);
	_SoundVector[soundID] = NULL;
}

bool SoundManager::soundIsPlaying(int soundID) {
	if (soundID < 0 || soundID >= MAX_SOUNDS) { return false; }
	if (_SoundVector[soundID] == NULL) { return false; }
	return _SoundVector[soundID]->getStatus() == sf::Sound::Playing;;
}

sf::SoundBuffer* SoundManager::getBuffer(const char* file) {
	std::map<std::string, sf::SoundBuffer*>::iterator it = _SoundBufferMap.find(file);
	if (it == _SoundBufferMap.end()) {
		sf::SoundBuffer* buffer = new sf::SoundBuffer();
		if (!buffer->loadFromFile(file)) {
			std::cout << "Error opening " << file << std::endl;
			return NULL;
		}
		std::cout << "Add sound " << file << "(first request)" << std::endl;

		_SoundBufferMap.insert(std::pair<std::string, sf::SoundBuffer*>(file, buffer));
		it = _SoundBufferMap.find(file);
	}
	
	return it->second;
}

void SoundManager::updateSoundFirstFreeSlot() {
	_CurrentSoundIndex = 0;
	for (int i = 0; i < MAX_SOUNDS; i++) {
		if (_SoundVector[i] == NULL) {
			_CurrentSoundIndex = i;
			break;
		}
		else {
			sf::Time duration = _SoundVector[i]->getBuffer()->getDuration();
			sf::Time offset = _SoundVector[i]->getPlayingOffset();
			if ((offset.asMilliseconds() >= duration.asMilliseconds() || offset.asMilliseconds() == 0)
				&& !soundIsPlaying(i)) {
				soundStop(i);
				_CurrentSoundIndex = i;
				break;
			}
		}

	}
}
