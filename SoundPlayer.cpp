#include "SoundPlayer.h"

SoundPlayer::SoundPlayer(){
	music = NULL;
}

void SoundPlayer::init(int freq, int channels, int chunkSize){
	if( Mix_OpenAudio( freq, MIX_DEFAULT_FORMAT, channels, chunkSize ) == -1 ){
        cout<<"Error initializing sound player:\n Freq: "<<freq<<"   Channels: "<<channels<<"   Chunk Size: "<<chunkSize<<endl;
    }
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
void SoundPlayer::playSound(){
	if(sounds.size()>0){
		if(Mix_PlayChannel(2, sounds.front(), 0) == -1){
			cout<<"Error playing sound"<<endl;
		}
	}
}
void SoundPlayer::playSound(Note n){
	if(sounds.size()>n){
		if(Mix_PlayChannel(2, sounds[n], 0) == -1){
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
void SoundPlayer::cleanup(){
	Mix_FreeMusic(music);
	for(int i=0; i< sounds.size();i++){
		Mix_FreeChunk(sounds[i]);
	}
	Mix_CloseAudio();
}
