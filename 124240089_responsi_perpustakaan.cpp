#include <iostream>
#include <string>
using namespace std;

struct Buku {
    string judul;
    string pengarang;
    int tahunTerbit;
    Buku* kiri;
    Buku* kanan;

    Buku(string j, string p, int t) {
        judul = j;
        pengarang = p;
        tahunTerbit = t;
        kiri = kanan = nullptr;
    }
};

struct AksiUndo {
    string jenisAksi; 
    Buku* dataBuku;
};

struct NodeUndo {
    AksiUndo aksi;
    NodeUndo* next;
};

Buku* akar = nullptr;
NodeUndo* topUndo = nullptr;

// Stack manual
void pushUndo(AksiUndo aksi) {
    NodeUndo* nodeBaru = new NodeUndo{aksi, topUndo};
    topUndo = nodeBaru;
}

bool isEmptyUndo() {
    return topUndo == nullptr;
}

AksiUndo popUndo() {
    if (isEmptyUndo()) return {"", nullptr};
    NodeUndo* temp = topUndo;
    AksiUndo aksi = temp->aksi;
    topUndo = topUndo->next;
    delete temp;
    return aksi;
}

bool bandingkanJudul(const string& a, const string& b) {
    return a < b;
}

Buku* tambahBuku(Buku* akar, Buku* bukuBaru) {
    if (akar == nullptr) return bukuBaru;

    if (bukuBaru->judul == akar->judul) {
        cout << "Judul \"" << bukuBaru->judul << "\" sudah ada.\n";
        delete bukuBaru;
        return akar;
    }

    if (bandingkanJudul(bukuBaru->judul, akar->judul)) {
        akar->kiri = tambahBuku(akar->kiri, bukuBaru);
    } else {
        akar->kanan = tambahBuku(akar->kanan, bukuBaru);
    }

    return akar;
}

void tampilkanDescending(Buku* akar) {
    if (akar) {
        tampilkanDescending(akar->kanan);
        cout << akar->judul << " - " << akar->pengarang << " - " << akar->tahunTerbit << endl;
        tampilkanDescending(akar->kiri);
    }
}

Buku* cariPengganti(Buku* node) {
    while (node && node->kiri != nullptr)
        node = node->kiri;
    return node;
}

Buku* hapusBuku(Buku* akar, string judul, Buku*& bukuDihapus) {
    if (akar == nullptr) return nullptr;

    if (judul < akar->judul) {
        akar->kiri = hapusBuku(akar->kiri, judul, bukuDihapus);
    } else if (judul > akar->judul) {
        akar->kanan = hapusBuku(akar->kanan, judul, bukuDihapus);
    } else {
        bukuDihapus = new Buku(akar->judul, akar->pengarang, akar->tahunTerbit);

        if (akar->kiri == nullptr) {
            Buku* temp = akar->kanan;
            delete akar;
            return temp;
        } else if (akar->kanan == nullptr) {
            Buku* temp = akar->kiri;
            delete akar;
            return temp;
        }

        Buku* pengganti = cariPengganti(akar->kanan);
        akar->judul = pengganti->judul;
        akar->pengarang = pengganti->pengarang;
        akar->tahunTerbit = pengganti->tahunTerbit;
        akar->kanan = hapusBuku(akar->kanan, pengganti->judul, bukuDihapus);
    }

    return akar;
}

int main() {
    int pilihan;
    do {
        cout << "\n=== Menu Perpustakaan ===\n";
        cout << "1. Tambah Buku\n";
        cout << "2. Tampilkan Daftar Buku (Z-A)\n";
        cout << "3. Hapus Buku\n";
        cout << "4. keluar\n";
        cout << "Pilih: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1: {
                string judul, pengarang;
                int tahun;
                cout << "Judul: ";
                getline(cin, judul);
                cout << "Pengarang: ";
                getline(cin, pengarang);
                cout << "Tahun Terbit: ";
                cin >> tahun;
                cin.ignore();

                Buku* bukuBaru = new Buku(judul, pengarang, tahun);
                akar = tambahBuku(akar, bukuBaru);
                pushUndo({"tambah", new Buku(judul, pengarang, tahun)});
                break;
            }
            case 2:
                cout << "\n=== Daftar Buku (Z-A) ===\n";
                tampilkanDescending(akar);
                break;
            case 3: {
                string judul;
                cout << "Judul buku yang akan dihapus: ";
                getline(cin, judul);
                Buku* bukuDihapus = nullptr;
                akar = hapusBuku(akar, judul, bukuDihapus);
                if (bukuDihapus != nullptr) {
                    pushUndo({"hapus", bukuDihapus});
                    cout << "Buku berhasil dihapus.\n";
                } else {
                    cout << "Buku tidak ditemukan.\n";
                }
                break;
            }
            case 4:
                cout << "Terima kasih telah menggunakan sistem kami.\n";
                break;
            default:
                cout << "Pilihan tidak valid!\n";
                break;
           
        }

    } while (pilihan != 4);

    return 0;
}
