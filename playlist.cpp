#include <iostream>
#include <fstream>
#include <string>
#include "playlist.h"
using namespace std;

// Implementasi fungsi
void createPlaylist(Playlist*& playlists, const string& name) {
    Playlist* newPlaylist = new Playlist;
    newPlaylist->name = name;
    newPlaylist->head = nullptr;
    newPlaylist->next = playlists;
    playlists = newPlaylist;
}

void addSong(Playlist* playlist, const string& title, const string& singer) {
    Song* newSong = new Song;
    newSong->title = title;
    newSong->singer = singer;
    newSong->next = playlist->head;
    playlist->head = newSong;
}

void displaySongs(const Playlist* playlist) {
    const Song* current = playlist->head;
    while (current != nullptr) {
        cout << "Title: " << current->title << ", Singer: " << current->singer << endl;
        current = current->next;
    }
}

void removeSong(Playlist* playlist, const string& title) {
    Song *current = playlist->head, *prev = nullptr;

    while (current != nullptr && current->title != title) {
        prev = current;
        current = current->next;
    }

    if (current == nullptr) {
        cout << "Lagu tidak ditemukan!" << endl;
        return;
    }

    if (prev == nullptr) {
        playlist->head = current->next;
    } else {
        prev->next = current->next;
    }

    delete current;
    cout << "Lagu '" << title << "' telah dihapus." << endl;
}

void sortSongs(Playlist* playlist, bool bySinger) {
    if (!playlist->head || !playlist->head->next) return;

    for (Song* i = playlist->head; i->next != nullptr; i = i->next) {
        for (Song* j = i->next; j != nullptr; j = j->next) {
            if ((bySinger && i->singer > j->singer) || (!bySinger && i->title > j->title)) {
                swap(i->title, j->title);
                swap(i->singer, j->singer);
            }
        }
    }
}

void savePlaylistToFile(const Playlist* playlist, const string& filename) {
    ofstream file(filename);
    if (!file) {
        cout << "Gagal membuka file untuk menulis!" << endl;
        return;
    }

    const Song* current = playlist->head;
    while (current != nullptr) {
        file << current->title << "|" << current->singer << endl;
        current = current->next;
    }

    file.close();
    cout << "Playlist telah disimpan ke file '" << filename << "'." << endl;
}

void loadPlaylistFromFile(Playlist*& playlists, const string& filename, const string& playlistName) {
    ifstream file(filename);
    if (!file) {
        cout << "Gagal membuka file untuk membaca!" << endl;
        return;
    }

    createPlaylist(playlists, playlistName);

    string line, title, singer;
    while (getline(file, line)) {
        size_t delimiterPos = line.find('|');
        if (delimiterPos != string::npos) {
            title = line.substr(0, delimiterPos);
            singer = line.substr(delimiterPos + 1);
            addSong(playlists, title, singer);
        }
    }

    file.close();
    cout << "Playlist '" << playlistName << "' berhasil dimuat dari file '" << filename << "'." << endl;
}

void deletePlaylist(Playlist*& playlists) {
    while (playlists != nullptr) {
        Playlist* tempPlaylist = playlists;
        Song* currentSong = playlists->head;

        while (currentSong != nullptr) {
            Song* tempSong = currentSong;
            currentSong = currentSong->next;
            delete tempSong;
        }

        playlists = playlists->next;
        delete tempPlaylist;
    }
}