#include "LevelManager.h"

LevelManager::LevelManager(int lvl, Pane *p, SoundPlayer *sp){
    level = lvl;
    points = 0;
    pane = p;
    soundplayer = sp;
}


bool LevelManager::checkMatching(int index){
    if (index == notesClicked.size() && index == pattern.size()){
        notesClicked.clear();
        return true;
    }
    if (index < notesClicked.size() && index < pattern.size()){
        if (notesClicked[index] == pattern[index])
            return (checkMatching(index+1));
        else {
            notesClicked.erase(notesClicked.begin());
            if (notesClicked.size()==0)
                return false;
            else return checkMatching(0);
        }
    }
    else
        return false;
}

void LevelManager::checkPattern(Note note){
    bool match = checkMatching(0);
    cout<<match<<endl;
    
    if (match) {//temp game logic
        cout<<"match"<<endl;
        points += 5;
        pane->updatePoints(points);
        if (points >= 10){
            pane->updateLevel(2);
            soundplayer->stopNoteSequence();
            pattern = {E,B,D};
            soundplayer->playNoteSequence(pattern,6000);
        }
        else if (points >= 30) {
            pane->updateLevel(3);
            soundplayer->stopNoteSequence();
            pattern = {D, G, F};
            soundplayer->playNoteSequence(pattern,5000);
        }
    }
    else cout<<"nope"<<endl;
}