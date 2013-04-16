#include "SoundPlayer.h"

SoundPlayer::SoundPlayer(Pane *newpane){
	music = NULL;
	sequenceCounter = 0;
	done = false;
	pane = newpane;
}

void SoundPlayer::init(int freq, int channels, int chunkSize){
	if( Mix_OpenAudio( freq, AUDIO_S16SYS, channels, chunkSize ) == -1 ){
        cout<<"Error initializing sound player:\n Freq: "<<freq<<"   Channels: "<<channels<<"   Chunk Size: "<<chunkSize<<endl;
    }
    Mix_Init(MIX_INIT_OGG);
}

void SoundPlayer::load_sounds(string fname){
	ifstream in;
	int numSounds;
	string musicName, soundName;
	in.open(fname.c_str());

	//load music
	in>>musicName;
	music = Mix_LoadMUS(musicName.c_str());
	if(music == NULL){
		cout<<"Error loading music file "<<musicName<<endl;
	}

	//load sounds
	in>>numSounds;
	cout<<"loading "<<numSounds<<" sounds..."<<endl;
	for(int i=0;i<numSounds;i++){
		in>>soundName;
		Mix_Chunk *tempsound = Mix_LoadWAV(soundName.c_str());
		if(tempsound == NULL){
			cout<<"error loading sound "<<soundName<<endl;
		}
		else
			sounds.push_back(tempsound);
	}
	in.close();
}

void SoundPlayer::playMusic(){
	if(Mix_PlayMusic(music, -1) == -1){
		cout<<"Error playing music"<<endl;
	}
}

void SoundPlayer::setMusicVolume(int newVolume){
	int vol = newVolume;
	if(vol < 0)
		vol=0;
	else if(vol > MIX_MAX_VOLUME)
		vol = MIX_MAX_VOLUME;
	Mix_VolumeMusic(vol);
}

void SoundPlayer::playSound(){
	if(sounds.size()>0){
		if(Mix_PlayChannel(2, sounds.front(), 0) == -1){
			cout<<"Error playing sound"<<endl;
		}
	}
}

void SoundPlayer::playSound(Note n, int channel){
	Mix_Volume(channel,128);
	if(sounds.size()>n){
		if(Mix_PlayChannel(channel, sounds[n], 0) == -1){
			cout<<"Error playing sound"<<endl;
		}
	}
}

void SoundPlayer::togglePauseMusic(){
	//music is paused
	if(Mix_PausedMusic()==1){
		Mix_ResumeMusic();
	}
	//music is playing
	else{
		Mix_PauseMusic();
	}
}

void SoundPlayer::playNoteSequence(vector<Note> newNotes, int newDelay){
	notes = newNotes;
	sequenceCounter = 0;
	done = false;
	delay = newDelay;
	thread = SDL_CreateThread(SoundPlayer::sequenceThread, this);
	if(thread == NULL){
		cout<<"Error starting thread..."<<endl;
	}

}
void SoundPlayer::startNewSequence(vector<Note> newNotes, int newDelay){
	stopNoteSequence();
	int status;
	SDL_WaitThread(thread, &status);
	playNoteSequence(newNotes, newDelay);
}
void SoundPlayer::stopNoteSequence(){
	done=true;
}

int SoundPlayer::sequenceThread(void *player){
	SoundPlayer *sp = (SoundPlayer*)player;
	sp->playSound(sp->notes[sp->sequenceCounter]);
	sp->sequenceCounter++;

	while(!sp->done){
		if(sp->sequenceCounter>=sp->notes.size()){
			sp->sequenceCounter = 0;
			SDL_Delay(sp->delay);
		}
		if(Mix_Playing(2)==0){
			cout<<"Note: "<<sp->notes[sp->sequenceCounter]<<"  counter: "<<sp->sequenceCounter<<endl;
			sp->playSound(sp->notes[sp->sequenceCounter]);
			sp->pane->flashColor(sp->notes[sp->sequenceCounter]);
			sp->sequenceCounter++;
		}
	}
	return 0;
}
void SoundPlayer::cleanup(){
	Mix_FreeMusic(music);
	for(unsigned int i=0; i< sounds.size();i++){
		Mix_FreeChunk(sounds[i]);
	}
	Mix_Quit();
	Mix_CloseAudio();
}

SoundPlayer::~SoundPlayer(){
    cleanup();
}
