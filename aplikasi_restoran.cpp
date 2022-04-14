#include <iostream>
#include <fstream>
#include <conio.h>
#include <string.h>
#include <string>
#include <cmath>

/*
  UTS Pemrograman berbasis objek C081

  Program aplikasi restoran

  Nama: Hanif Al Fathoni
  NPM: 20081010001
  Kelas: PBO C081
*/

using namespace std;

class Tampilan
{
public:
  void awal();
  void tipePengguna();
  void welcome();
};

class Menu
{
protected:
  int idMenu;
  char namaItem[40];
  int hargaItem;

public:
  friend class Staff;
  friend class MenuPelanggan;
  void tambahMenu();
  void tampilMenu();
  int idBaru();
  bool duplikasiItem(char[]);
};

class Pelanggan
{
public:
  char namaPelanggan[40];
  int nomorMeja;
  int idPemesanan[10];
};

class MenuPelanggan
{
public:
  void halamanPelanggan();
  bool validasiMeja(int);
  void pemesanan();
  int bill(int);
  void bayar(int);
};

class Staff : public Tampilan
{
private:
  char userId[20];
  char userPass[20];

public:
  bool validasiStaff();
  virtual void halamanStaff() = 0;
};

class User
{
private:
  char uid[20];
  char password[20];

public:
  char *getuid()
  {
    return uid;
  }
  char *getpassword()
  {
    return password;
  }
};

class MenuStaff : public Staff
{
public:
  void loginStaff(int);
  void halamanStaff();
  void tambahItem();
  void tampilItem();
};

void Menu::tambahMenu()
{
  ofstream file;
  Menu sm;
  MenuStaff ms;
  file.open("menu.txt", ios::app | ios::binary);
  if (file.is_open())
  {
    sm.idMenu = idBaru();
    cout << "Masukkan nama item: ";
    cin.sync();
    cin.getline(sm.namaItem, 40);
    cout << "Masukkan harga item: ";
    cin >> sm.hargaItem;
    if (duplikasiItem(namaItem))
    {
      cout << "\nItem ini telah ada di menu!\n\n";
      cout << "\nSilahkan tambah item baru\n\n";
      file.close();
      cout << "Tekan tombol apapun untuk melanjutkan\n";
      getch();
      system("cls");
      file.close();
      ms.halamanStaff();
    }
    else
    {
      file.write(reinterpret_cast<const char *>(&sm), sizeof(Menu));
      cout << "\nItem telah ditambahkan ke menu\n";
      file.close();
      cout << "Tekan tombol apapun untuk melanjutkan\n";
      getch();
      system("cls");
    }
  }
  else
  {
    cout << "Menu gagal ditampilkan!\n";
    file.close();
  }
  file.close();
}

void Menu::tampilMenu()
{
  Menu sm;
  ifstream file;
  file.open("menu.txt", ios::in | ios::binary);
  if (file.is_open())
  {
    cout << "\nId:  Nama Item:\t\tHarga(Rp.):\n";
    file.seekg(0);
    while (file.read(reinterpret_cast<char *>(&sm), sizeof(Menu)))
    {
      cout << sm.idMenu << "     " << sm.namaItem << "\t\t" << sm.hargaItem << "\n";
    }
    cout << endl;
    file.close();
  }
  else
  {
    cout << sm.namaItem;
    cout << "Menu gagal ditampilkan!\n";
    file.close();
  }
}

int Menu::idBaru()
{
  int hitungId = 1;
  ifstream file;
  Menu sm;
  file.open("menu.txt", ios::in | ios::binary);
  if (file.is_open())
  {
    file.seekg(0);
    while (file.read(reinterpret_cast<char *>(&sm), sizeof(Menu)))
    {
      hitungId++;
    }
    file.close();
  }
  else
  {
    cout << "Tidak bisa membuka file menu untuk mendapatkan id baru\n";
  }
  file.close();
  return hitungId;
}

bool Menu::duplikasiItem(char item[40])
{
  bool hasil = false;
  ifstream file;
  Menu sm;
  file.open("menu.txt", ios::in | ios::binary);
  if (file.is_open())
  {
    file.seekg(0);
    while (file.read(reinterpret_cast<char *>(&sm), sizeof(Menu)))
    {
      if (strcmp(sm.namaItem, item) == 0)
      {
        hasil = true;
      }
    }
    file.close();
  }
  else
  {
    cout << "Tidak bisa membuka file menu\n";
  }
  file.close();
  return hasil;
}

void MenuStaff::tambahItem()
{
  Menu sm;
  sm.tambahMenu();
  halamanStaff();
}

void MenuStaff::tampilItem()
{
  Menu sm;
  sm.tampilMenu();
  cout << "Tekan tombol apapun untuk melanjutkan...\n\n";
  getch();
  system("cls");
  halamanStaff();
}

bool Staff::validasiStaff()
{
  cout << "Enter User Id: \n";
  cin >> userId;
  cout << "Enter User Password: \n";
  int p = 0;
  do
  {
    userPass[p] = getch();
    if (userPass[p] != '\r')
    {
      cout << "*";
    }
    p++;
  } while (userPass[p - 1] != '\r');

  userPass[p - 1] = '\0';
  if ((strcmp(userId, "staff") == 0 && strcmp(userPass, "staff123") == 0)) // user staff, password staff123
  {
    return 1;
  }
  return 0;
}

void MenuStaff::loginStaff(int i)
{
  int pilihan;
  system("cls");
  if (validasiStaff())
  {
    cout << "\nLogin Berhasil!\n";
    cout << "Tekan tombol apapun untuk melanjutkan...\n";
    getch();
    system("cls");
    halamanStaff();
  }
  else
  {
    cout << "\nHarap masukkan User Id atau Password dengan benar, anda memiliki " << 3 - i << " kesempatan tersisa. \n";
    cout << "Tekan tombol apapun untuk melanjutkan...\n";
    getch();
    if (i < 3)
    {
      loginStaff((i + 1));
    }
    else
    {
      cout << "Anda telah gagal memasukkan User Id atau Password lebih dari 3 kali...\n";
      cout << "Coba lagi beberapa saat lagi!\n";
      exit(0);
    }
  }
}

void MenuStaff::halamanStaff()
{
  char pilihan;
  User u;
  cout << "HALAMAN STAFF...\n";
  cout << "1. Tambah item makanan ke menu\n";
  cout << "2. Tampilkan semua item pada menu\n";
  cout << "3. Kembali ke menu sebelumnya\n";
  Menu sm;
  cout << "Masukkan pilihan anda: ";
  cin >> pilihan;
  switch (pilihan)
  {
  case '1':
    tambahItem();
    break;
  case '2':
    tampilItem();
    break;
  case '3':
    system("cls");
    welcome();
    break;
  default:
  {
    cout << "Pilihan anda tidak valid!\n";
    cout << "Tekan tombol apapun untuk melanjutkan...\n";
    getch();
    system("cls");
    halamanStaff();
  }
  }
}

void MenuPelanggan::halamanPelanggan()
{
  system("cls");
  Menu m;
  Tampilan t;
  char pilihan;
  int nomorMeja;
  cout << "HALAMAN PELANGGAN...\n";
  cout << "1. Tampilkan menu restoran\n";
  cout << "2. Pesan makanan\n";
  cout << "3. Tampilkan bill atau tagihan\n";
  cout << "4. Bayar bill atau tagihan\n";
  cout << "5. Kembali ke menu sebelumnya\n";
  cout << "Masukkan pilihan anda: ";
  cin >> pilihan;
  switch (pilihan)
  {
  case '1':
  {
    m.tampilMenu();
    cout << "Tekan tombol apapun untuk melanjutkan...\n";
    getch();
    halamanPelanggan();
  }
  break;
  case '2':
    pemesanan();
    break;
  case '3':
    cout << "Masukkan nomor meja anda: ";
    cin >> nomorMeja;
    while (!validasiMeja(nomorMeja))
    {
      cout << "\nMeja tersebut kosong! Tidak ada riwayat bill!\n Masukkan nomor meja yang valid: ";
      cin >> nomorMeja;
    }
    bill(nomorMeja);
    cout << "Tekan tombol apapun untuk melanjutkan...\n";
    getch();
    halamanPelanggan();
    break;
  case '4':
    cout << "Masukkan nomor meja anda: ";
    cin >> nomorMeja;
    while (!validasiMeja(nomorMeja))
    {
      cout << "\nMeja tersebut kosong! Tidak ada riwayat bill!\n Masukkan nomor meja yang valid: ";
      cin >> nomorMeja;
    }
    bayar(nomorMeja);
    break;
  case '5':
    system("cls");
    t.welcome();
    break;
  default:
  {
    cout << "Pilihan anda tidak valid!\n";
    cout << "Tekan tombol apapun untuk melanjutkan...\n";
    getch();
    halamanPelanggan();
  }
  }
}

void MenuPelanggan::pemesanan()
{
  int idItem;
  char pilihan;
  Menu m;
  Pelanggan p;
  cout << "Masukkan nama anda: ";
  cin.sync();
  cin.getline(p.namaPelanggan, 40);
  cout << "Masukkan nomor meja yang anda pilih: ";
  cin >> p.nomorMeja;
  while (validasiMeja(p.nomorMeja))
  {
    cout << "\nMeja telah ditempati!\nMasukkan nomor meja lain: ";
    cin >> p.nomorMeja;
  }
  cout << "\n\n Menu hari ini! \n\n";
  m.tampilMenu();
  int i = 0;
  do
  {
    cout << "\nMasukkan id makanan yang ingin anda pesan: ";
    cin >> p.idPemesanan[i];
    i++;
    cout << "Apakah anda ingin menambah pesanan? [Y/N]: ";
    cin >> pilihan;
  } while (pilihan == 'Y' || pilihan == 'y');

  fstream file;
  file.open("pesanan.txt", ios::app | ios::binary);
  if (file.is_open())
  {
    file.write(reinterpret_cast<const char *>(&p), sizeof(Pelanggan));
    file.close();
  }
  else
  {
    cout << "File tidak dapat dibuka!\n";
  }
  cout << "Tekan tombol apapun untuk melanjutkan...\n";
  getch();
  halamanPelanggan();
}

int MenuPelanggan::bill(int nm)
{
  Pelanggan p;
  Menu m;
  float totalHarga = 0, ppn = 0, tagihan = 0;
  int totalTagihan;
  ifstream file, file1;
  file.open("pesanan.txt", ios::in | ios::binary);
  if (file.is_open())
  {
    file.seekg(0);
    while (file.read(reinterpret_cast<char *>(&p), sizeof(Pelanggan)))
    {
      if (p.nomorMeja == nm)
      {
        cout << "\nNama pelanggan: " << p.namaPelanggan;
        cout << "\nNomor meja: " << nm << "\n";
        int k = 0;
        cout << "\n\t\tBill atau Tagihan: \n\n";
        cout << "\t---------------------------------------------\n";
        cout << "\t|\tNama Item\t\tHarga(Rp.)\t|\n";
        cout << "\t---------------------------------------------\n";
        while (p.idPemesanan[k])
        {
          file1.open("menu.txt", ios::in | ios::binary);
          file1.seekg(0);
          while (file1.read(reinterpret_cast<char *>(&m), sizeof(Menu)))
            if (p.idPemesanan[k] == m.idMenu)
            {
              cout << "\t|\t" << m.namaItem << "\t\t\t" << m.hargaItem << "\t\t|\n";
              totalHarga += m.hargaItem;
              ppn = totalHarga * 10 / 100;
              tagihan = totalHarga + ppn;
              totalTagihan = round(tagihan);
            }
          file1.close();
          k++;
        }
        cout << "\t|\tTotal Harga Makanan\t\t" << totalHarga << "\t\t|";
        cout << "\n\t|\tPPn (10%)\t\t" << ppn << "\t\t|";
        cout << "\t---------------------------------------------";
        cout << "\n\t|\tTotal Tagihan\t\t" << tagihan << "\t\t|\n";
        cout << "\t---------------------------------------------\n\n";
      }
    }
    file.close();
    file1.close();
  }
  else
  {
    cout << "File tidak dapat dibuka!\n";
  }
  return totalTagihan;
}

void MenuPelanggan::bayar(int noMeja)
{
  fstream file, filetemp;
  int ketemu = 0;
  float kembalian = 0, tagihan, tagihanDibayar;
  Pelanggan p;
  file.open("pesanan.txt", ios::in | ios::binary);
  if (file == NULL)
  {
    cout << "File tidak dapat dibuka!";
  }
  filetemp.open("temp.txt", ios::out | ios::binary);
  if (filetemp == NULL)
  {
    cout << "File tidak dapat dibuka!";
  }
  file.seekg(0);
  while (file.read(reinterpret_cast<char *>(&p), sizeof(Pelanggan)) != NULL)
  {
    if (noMeja == p.nomorMeja)
    {
      tagihan = bill(noMeja);
      do
      {
        cout << "\n\nJumlah yang harus dibayarkan adalah Rp. " << tagihan;
        cout << "\nMasukkan nominal yang anda bayarkan: ";
        cin >> tagihanDibayar;
        if (tagihanDibayar > tagihan)
        {
          kembalian = tagihanDibayar - tagihan;
          cout << "\nRp. " << tagihan << " telah dibayar. Terima kasih! Ini kembalian anda Rp." << kembalian;
          tagihanDibayar = tagihan;
        }
        else if (tagihanDibayar < tagihan)
        {
          kembalian = tagihan - tagihanDibayar;
          cout << "\nRp. " << tagihan << " telah dibayar. Pembayaran kurang, mohon bayar Rp." << kembalian << " lagi";
          tagihan = kembalian;
        }
        else
        {
          cout << "\nRp. " << tagihan << " telah dibayar. Terima kasih!";
        }
      } while (tagihanDibayar != tagihan);
      ketemu = 1;
    }
    else
    {
      filetemp.write(reinterpret_cast<const char *>(&p), sizeof(Pelanggan));
    }
  }

  if (!ketemu)
  {
    cout << "\nTidak ditemukan meja dengan nomor meja: " << noMeja;
  }

  file.close();
  filetemp.close();

  remove("pesanan.txt");
  rename("temp.txt", "pesanan.txt");
  if (ketemu == 1)
  {
    cout << "\n\nTerima kasih telah berkunjung ke restoran kami!\n\n";
    exit(0);
  }
  cout << "\nTekan tombol apapun untuk melanjutkan...\n";
  getch();
  system("cls");
  halamanPelanggan();
}

bool MenuPelanggan::validasiMeja(int a)
{
  FILE *fp;
  bool hasil = false;
  Pelanggan p;
  fp = fopen("pesanan.txt", "r");
  if (fp == NULL)
  {
    cout << "File tidak dapat dibuka!\n";
  }
  else
  {
    while (fread(&p, sizeof(Pelanggan), 1, fp))
    {
      if (p.nomorMeja == a)
      {
        hasil = true;
      }
    }
    fclose(fp);
    return hasil;
  }
}

void Tampilan::awal()
{
  system("cls");
  cout << endl
       << endl
       << endl
       << endl
       << endl;
  cout << "\t\t\t\t******************************************************** \n";
  cout << "\t\t\t\t\t\t Selamat Datang di Restaurant \n";
  cout << "\t\t\t\t******************************************************** \n";
  cout << "\n\n\n\t\t\t\t\t\tTekan tombol apapun untuk melanjutkan...\n";
  getch();
  system("cls");
}

void Tampilan::tipePengguna()
{
  cout << "Pilih tipe pengguna \n";
  cout << "1. Pelanggan \n";
  cout << "2. Staff \n";
  cout << "3. Exit \n";
}

void Tampilan::welcome()
{
  char pilihan;
  MenuPelanggan mp;
  MenuStaff ms;
  tipePengguna();
  cout << "Masukkan pilihan anda: ";
  cin >> pilihan;

  switch (pilihan)
  {
  case '1':
    mp.halamanPelanggan();
    break;
  case '2':
    ms.loginStaff(1);
    break;
  case '3':
    cout << "\n\nTerima kasih telah berkunjung ke restaurant kami!\n\n";
    exit(0);
    break;
  default:
  {
    cout << "Pilihan anda tidak valid!\n";
    cout << "Tekan tombol apapun untuk melanjutkan...\n";
    getch();
    system("cls");
    welcome();
  }
  }
}

int main()
{
  Tampilan t;
  t.awal();
  t.welcome();
  getch();
  return 0;
}
