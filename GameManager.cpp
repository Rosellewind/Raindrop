#include "GameManager.h"
#include <ctime>

GameManager::GameManager(int lvl, Pane *p, SoundPlayer *sp){
    level = lvl;
    subLevel = 0;
    points = 0;
    pane = p;
    soundplayer = sp;
    newPattern();
    //seed psuedo random number generator
    srand ((unsigned int)time(NULL));
}

bool GameManager::checkMatching(int index){
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

void GameManager::checkPattern(Note note){
    notesClicked.push_back(note);
    bool match = checkMatching(0);
    cout<<match<<endl;
    
    if (match) {//temp game logic
        cout<<"match"<<endl;
        points += 5;
        pane->updatePoints(points);
        int temp = (int)(level+ 3)*.6;
        if (subLevel > (int)(level+ 3)*.6){ //2,3,3,4,4,5,6,6,7,7 sublevels
            level ++;
            subLevel = 0;
            pane->updateLevel(level);
        }
        soundplayer->stopNoteSequence();
        newPattern();
        soundplayer->playNoteSequence(pattern,6000);
    }
    else cout<<"nope"<<endl;
}

//easier- stepping, repeating
//harder- random

void GameManager::newPattern(){
    vector<Note> lastPattern(pattern);
    
    pattern.clear();
    //    vector<Note> lastPattern = pattern;
    cout<<"lastPattern: ";
    for (int i = 0; i<lastPattern.size(); i++) {
        cout<<lastPattern[i];
    }
    cout<<endl;
    
    
    
    Note previous = randomNote();
    subLevel ++;
    int numNotes = (int)(level + 6)*.35;  //2,2,3,3,3,4,4,4,5,5,5,6,6,7 numNotes
    if (level ==1){
        for (int i = 0; i < numNotes; i++){
            Note r = previous;               //repeat
            pattern.push_back(r);
        }
    }
    else if (level == 2){
        for (int i = 0; i < numNotes; i++){
            Note r = raiseNote(previous);    //step
            previous = r;
            pattern.push_back(r);
        }
    }
    else {
        for (int i = 0; i < numNotes; i++){
            Note r;
            if (rand()%(level+1))              //step?
                r = raiseNote(previous);
            else if (rand()%(level+1))         //repeat?
                r = previous;
            else
                r = randomNote();             //random note
            previous = r;
            pattern.push_back(r);
        }
    }
    if (isSamePattern(lastPattern, pattern)){
        newPattern();
    }
}
bool GameManager::isSamePattern(vector<Note> lastPattern,vector<Note> pattern){
    bool same = false;
    if (lastPattern.size() == pattern.size()) {
        for (int i = 0; i<lastPattern.size(); i++) {
            if (lastPattern[i] == pattern[i]) {
                same = true;
                break;
            }
        }
    }
    return same;
}

Note GameManager::intToNote(int i){
    Note newNote;
    if (i == 0)
        newNote = LC;
    else if (i == 1)
        newNote = D;
    else if (i == 2)
        newNote = E;
    else if (i == 3)
        newNote = F;
    else if (i == 4)
        newNote = G;
    else if (i == 5)
        newNote = A;
    else if (i == 6)
        newNote = B;
    else
        newNote = HC;
    return newNote;
}

Note GameManager::raiseNote(Note note){
    Note newNote;
    if (note == LC)
        newNote = D;
    else if (note == D)
        newNote = E;
    else if (note == E)
        newNote = F;
    else if (note == F)
        newNote = G;
    else if (note == G)
        newNote = A;
    else if (note == A)
        newNote = B;
    else if (note == B)
        newNote = HC;
    else
        newNote = LC;
    return newNote;
}

Note GameManager::randomNote(){
    return intToNote(rand()%(HC+2));
}

vector<Note> GameManager::getPattern(){
    return pattern;
}