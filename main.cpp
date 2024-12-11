#include <iostream>
#include "playlist.cpp"

using namespace std;

int main() {
    Playlist* playlists = nullptr;
    int choice;
    string playlistName, title, singer, filename; // Deklarasi di awal

    while (true) {
        // Menampilkan menu
        cout << "\n=== Playlist Manager ===\n";
        cout << "1. Buat Playlist\n";
        cout << "2. Tambahkan lagu dalam playlist\n";
        cout << "3. Tampilkan Playlist\n";
        cout << "4. Hapus lagu\n";
        cout << "5. Muat Playlist dari file\n";
        cout << "6. Urutkan lagu (judul)\n"; // Mengubah opsi "Cari lagu" menjadi "Urutkan lagu"
        cout << "7. Menyimpan Playlist ke file\n";
        cout << "8. Exit\n";
        cout << "Masukkan pilihan: ";
        cin >> choice;

        // Memproses pilihan pengguna
        if (choice == 8) {
            cout << "Keluar dari program..." << endl;
            break;
        }

        switch (choice) {
            case 1: {
                cout << "Masukkan nama playlist: ";
                cin >> playlistName;
                createPlaylist(playlists, playlistName);
                cout << "Playlist '" << playlistName << "' berhasil dibuat!\n";
                break;
            }
            case 2: {
                cout << "Masukkan nama playlist: ";
                cin >> playlistName;
                Playlist* current = playlists;
                while (current != nullptr && current->name != playlistName) {
                    current = current->next;
                }
                if (current == nullptr) {
                    cout << "Playlist tidak ditemukan!\n";
                } else {
                    cout << "Masukkan judul lagu: ";
                    cin >> title;
                    cout << "Masukkan penyanyi: ";
                    cin >> singer;
                    addSong(current, title, singer);
                    cout << "Lagu berhasil ditambahkan ke playlist '" << playlistName << "'!\n";
                }
                break;
            }
            case 3: {
                Playlist* current = playlists;
                if (current == nullptr) {
                    cout << "Belum ada playlist yang dibuat.\n";
                } else {
                    while (current != nullptr) {
                        cout << "\nPlaylist: " << current->name << endl;
                        displaySongs(current);
                        current = current->next;
                    }
                }
                break;
            }
            case 4: {
                cout << "Masukkan nama playlist: ";
                cin >> playlistName;
                Playlist* current = playlists;
                while (current != nullptr && current->name != playlistName) {
                    current = current->next;
                }
                if (current == nullptr) {
                    cout << "Playlist tidak ditemukan!\n";
                } else {
                    cout << "Masukkan judul lagu yang ingin dihapus: ";
                    cin >> title;
                    removeSong(current, title);
                }
                break;
            }
            case 5: {
                cout << "Masukkan nama file: ";
                cin >> filename;
                cout << "Masukkan nama playlist baru: ";
                cin >> playlistName;
                loadPlaylistFromFile(playlists, filename, playlistName);
                break;
            }
            case 6: { // Mengubah logika dari pencarian ke pengurutan
                cout << "Masukkan nama playlist: ";
                cin >> playlistName;
                Playlist* current = playlists;
                while (current != nullptr && current->name != playlistName) {
                    current = current->next;
                }
                if (current == nullptr) {
                    cout << "Playlist tidak ditemukan!\n";
                } else {
                    sortSongs(current);
                    cout << "Lagu dalam playlist '" << playlistName << "' telah diurutkan secara alfabetis berdasarkan judul.\n";
                }
                break;
            }
            case 7: {
                cout << "Masukkan nama playlist: ";
                cin >> playlistName;
                Playlist* current = playlists;
                while (current != nullptr && current->name != playlistName) {
                    current = current->next;
                }
                if (current == nullptr) {
                    cout << "Playlist tidak ditemukan!\n";
                } else {
                    cout << "Masukkan nama file untuk menyimpan: ";
                    cin >> filename;
                    savePlaylistToFile(current, filename);
                }
                break;
            }
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi.\n";
                break;
        }
    }

    return 0;
}
