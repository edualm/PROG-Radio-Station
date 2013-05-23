//
//  User.cpp
//  Radio Station
//
//  Created by Jo�o Almeida on 19/05/13.
//

#include "Playlist.h"
#include "Music.h"

Playlist::Playlist() {
    
}

Playlist::~Playlist() {
    
}

bool Playlist::addSong(Music *theSong) {
    for (int i = 0; i < _thePlaylist.size(); i++)
        if (_thePlaylist[i] -> getId() == theSong -> getId())
            return false;
    
    _thePlaylist.push_back(theSong);
    
    return true;
}

bool Playlist::removeSong(Music *theSong){
    for (int i = 0; i < _thePlaylist.size(); i++)
        if (_thePlaylist[i] -> getId() == theSong -> getId()) {
            _thePlaylist.erase(_thePlaylist.begin() + i);
            
            return true;
        }
    
    return false;
}

const std::vector<Music *> Playlist::getAllTracks() {
    return _thePlaylist;
}

const std::vector<Music *> Playlist::search(int musicId, std::string title,  std::string artist, std::string author, std::string album, std::string music_genre, int year) {
    std::vector<Music *> returnVec;
    
    if (musicId != -1) // Do NOT search by music id
        for (int i = 0; i < _thePlaylist.size(); i++)
            if (_thePlaylist[i] -> getId() == musicId) {
                returnVec.push_back(_thePlaylist[i]);
                
                break;
            }
    
    if (title.compare(""))
        for (int i = 0; i < _thePlaylist.size(); i++)
            if (!(_thePlaylist[i] -> getTitle().compare(title)))
                returnVec.push_back(_thePlaylist[i]);
    
    if (artist.compare(""))
        for (int i = 0; i < _thePlaylist.size(); i++)
            if (!(_thePlaylist[i] -> getArtist().compare(artist)))
                returnVec.push_back(_thePlaylist[i]);
    
    if (author.compare(""))
        for (int i = 0; i < _thePlaylist.size(); i++)
            if (!(_thePlaylist[i] -> getAuthor().compare(author)))
                returnVec.push_back(_thePlaylist[i]);
    
    if (album.compare(""))
        for (int i = 0; i < _thePlaylist.size(); i++)
            if (!(_thePlaylist[i] -> getAlbum().compare(album)))
                returnVec.push_back(_thePlaylist[i]);
    
    if (music_genre.compare(""))
        for (int i = 0; i < _thePlaylist.size(); i++)
            if (!(_thePlaylist[i] -> getGenre().compare(music_genre)))
                returnVec.push_back(_thePlaylist[i]);
    
    if (year != -1)
        for (int i = 0; i < _thePlaylist.size(); i++)
            if (_thePlaylist[i] -> getYear() == year)
                returnVec.push_back(_thePlaylist[i]);
    
    return returnVec;
}

void Playlist::shuffle(){
    std::random_shuffle(_thePlaylist.begin(), _thePlaylist.end());
}

const unsigned int Playlist::count() {
    return (const unsigned int) _thePlaylist.size();
}

const std::vector<Music *> Playlist::topTenSongs() {
    if (topTenSongs().size() == 0)
        updateTopTen();
    
    return _topTen;
}

void Playlist::updateTopTen() {
    std::vector<Music *> newTopTen;
    
    int topCount = 0;
    
    for (int i = 0; i < 10; i++) {
        int localTop = 0;
        
        for (int j = 0; j < _thePlaylist.size(); j++) {
            int diff = _thePlaylist[i] -> getLikes() - _thePlaylist[i] -> getDislikes();
        
            if (diff > localTop)
                if (topCount == 0 || diff < topCount)
                    localTop = diff;
        }
        
        if (localTop != 0) {
            for (int j = 0; j < _thePlaylist.size(); j++) {
                int diff = _thePlaylist[i] -> getLikes() - _thePlaylist[i] -> getDislikes();
                
                if (localTop == diff)
                    newTopTen.push_back(_thePlaylist[i]);
            }
        }
        
        topCount = localTop;
    }
    
    _topTen = newTopTen;
}
