#include <iostream>
#include <cstring> 
using namespace std;

const int MAX_SIZE = 100; 

struct Mahasiswa {
    char nama[50];
    char nim[15];
    float ipk;
};

void inputData(Mahasiswa data[], int& n) {
    cout << "Masukkan jumlah data (maks " << MAX_SIZE << "): ";
    cin >> n;
    if (n > MAX_SIZE) {
        cout << "Jumlah data melebihi batas maksimum. Mengatur ke " << MAX_SIZE << endl;
        n = MAX_SIZE;
    }
    cin.ignore(); 
    for (int i = 0; i < n; i++) {
        cout << "Data Mahasiswa ke-" << (i + 1) << endl;
        cout << "Nama: ";
        cin.getline(data[i].nama, 50);
        cout << "NIM: ";
        cin.getline(data[i].nim, 15);
        cout << "IPK: ";
        cin >> data[i].ipk;
        cin.ignore(); 
    }
}

void tampilData(Mahasiswa data[], int n) {
    cout << "Data Mahasiswa:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Mahasiswa ke-" << (i + 1) << endl;
        cout << "Nama: " << data[i].nama << endl;
        cout << "NIM: " << data[i].nim << endl;
        cout << "IPK: " << data[i].ipk << endl;
    }
}

void searching(Mahasiswa data[], int n) {
    char nim[15];
    cout << "Masukkan NIM yang dicari: ";
    cin >> nim;
    bool found = false;
    for (int i = 0; i < n; i++) {
        if (strcmp(data[i].nim, nim) == 0) {
            cout << "Data Mahasiswa ditemukan:" << endl;
            cout << "Nama: " << data[i].nama << endl;
            cout << "NIM: " << data[i].nim << endl;
            cout << "IPK: " << data[i].ipk << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Data Mahasiswa dengan NIM " << nim << " tidak ditemukan." << endl;
    }
}

void sorting(Mahasiswa data[], int n) {
    
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (data[j].ipk > data[j + 1].ipk) {
            
                Mahasiswa temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }
    cout << "Data setelah diurutkan berdasarkan IPK:" << endl;
    tampilData(data, n);
}

int main() {
    Mahasiswa data[MAX_SIZE];
    int n = 0; 
    int pilihan;

    do {
        cout << "Menu:" << endl;
        cout << "1. Input Data" << endl;
        cout << "2. Tampilkan Data" << endl;
        cout << "3. Searching" << endl;
        cout << "4. Sorting" << endl;
        cout << "5. Exit" << endl;
        cout << "Pilih opsi (1-5): ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                inputData(data, n);
                break;
            case 2:
                tampilData(data, n);
                break;
            case 3:
                searching(data, n);
                break;
            case 4:
                sorting(data, n);
                break;
            case 5:
                cout << "Keluar dari program." << endl;
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    } while (pilihan != 5);

    return 0;
}