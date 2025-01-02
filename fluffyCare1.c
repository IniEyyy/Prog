#include <stdio.h> //printf func, scanf func, FILE struct, fopen func, fclose func, fscanf func, fprintf func, sprintf func
#include <stdlib.h> //malloc func
#include <string.h> //strlen func, memmove func
#include <windows.h> //set colors
#include <conio.h> //getch func
#include <ctype.h> //toupper func

#define MAX 100
#define MAX_LAYANAN 10

#define COLOR_YELLOW 14
#define COLOR_BLUE 9
#define COLOR_GREEN 10
#define COLOR_WHITE 15
#define COLOR_RED 12
#define COLOR_GRAY 8
#define COLOR_NAVY 1
#define COLOR_LIME 10


typedef struct{
    char namaLayanan[50];
    int harga;
} Layanan;

typedef struct{
    char namaPemilik[50];
    char namaHewan[50];
    char jenisHewan[20];
    char layanan[50];
    int harga;
    char tanggal[15];
} Reservasi;

void clear();
int ask(char str[][100], int n);

void art();
int displayMenuLayanan(Layanan menu[], int jumlahLayanan, char *jenisHewan);
int displayMenu();
void addReservasi();
void displayReservasi();
void report();
void sortingReservasi();
void writeToFile(const char *filename);
void readToFile(const char *filename);
char* formatInt(int num);

// Daftar layanan
Layanan menuKucing[MAX_LAYANAN] = {
    {"Dry Grooming", 40000}, {"Basic Grooming", 60000},
    {"Basic Grooming + Anti Kutu/Anti Jamur", 100000}, {"Grooming Lengkap", 120000},
    {"Cukur Lion Cut", 90000}, {"Cukur Botak", 100000},
    {"Cukur Stylish", 125000}, {"Sikat & Pembersihan Gigi", 25000},
    {"Cabut Kutu", 35000}, {"Pengobatan Kulit", 110000}
};

Layanan menuAnjing[MAX_LAYANAN] = {
    {"Dry Grooming", 75000}, {"Basic Grooming", 100000},
    {"Basic Grooming + Anti Kutu/Anti Jamur", 135000}, {"Grooming Lengkap", 150000},
    {"Cukur Lion Cut", 130000}, {"Cukur Botak", 170000},
    {"Cukur Stylish", 205000}, {"Sikat & Pembersihan Gigi", 30000},
    {"Cabut Kutu", 60000}, {"Pengobatan Kulit", 150000}
};

Reservasi data[MAX];
int jumlahData = 0;

// Main Program
int main(){
    //art();
    clear();
    readToFile("reservasi.txt"); // Baca data lama dari file
    int pilihan;
    do{
        pilihan = displayMenu();
        //scanf("%d", &pilihan);
        switch (pilihan){
            case 1:
                addReservasi();
                break;
            case 2:
                sortingReservasi();
                displayReservasi();
                break;
            case 3:
                report();
                break;
            case 4:
                writeToFile("reservasi.txt");
                break;
            case 5:
                printf("\tTerima kasih telah menggunakan Fluffy Care Salon!\n");
                break;
            default:
                printf("\tPilihan tidak valid.\n");
        }
    } while (pilihan != 5);
    return 0;
}

void clear(){ //clear console screen
	system("cls");printf("\n\n");art();
}

int ask(char str[][100], int n){ //ask user to choose from provided options
	int a = 1, i;
	while(1){
		printf("\n\t%s\n", str[0]);
		for(i = 1; i <= n; i++){
			printf("\t%d. %s%s\n", i, str[i], (i==a)?" <":"");
		}
		printf("\n\tTekan %c atau W untuk ke atas\n\tTekan %c atau S untuk ke bawah\n\tTekan Enter atau Spacebar untuk memilih.\n\n\n\t",24,25);
		switch(getch()){
			case 'w': case 'W': case 72: if(a>1){a--;} break;
			case 's': case 'S': case 80: if(a<n){a++;} break;
			case ' ': case '\r': clear(); return a;
		}
		clear();
	}
}

void setColor(int colorCode){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, colorCode);
}

void art(){
    setColor(14);
    puts("\t+----------------------------------------------------------------+");
    puts("\t|	 ______ _        __  __          _____  		 |");       
    puts("\t|	|  ____| |      / _|/ _|        / ____| 		 |");            
    puts("\t|	| |__  | |_   _| |_| |_ _   _  | |     __ _ _ __ ___ 	 |");
    puts("\t|	|  __| | | | | |  _|  _| | | | | |    / _` | '__/ _ \\	 |");
    puts("\t|	| |    | | |_| | | | | | |_| | | |___| (_| | | |  __/	 |");
    puts("\t|	|_|    |_|\\__,_|_| |_|  \\__, |  \\_____\\__,_|_|  \\___|	 |");
    puts("\t|	                         __/ | 				 |");                     
    puts("\t|	                        |___/				 |");                       
    puts("\t+----------------------------------------------------------------+\n");
    setColor(7);
}

// Fungsi menampilkan menu utama
int displayMenu(){
	//tabgel string untuk display perintah dan pilihannya
	char last[6][100] = {
	"Pilih Menu",
	"Tambah Data Reservasi",
	"Daftar Data Reservasi",
	"Laporan Harian",
	"Simpan ke File",
	"Keluar"};
	return ask(last,5); //meminta pilihan dengan fungsi ask()
}

// Fungsi menampilkan menu layanan
int displayMenuLayanan(Layanan menu[], int jumlahLayanan, char jenisHewan[]){
	char menuLayanan[jumlahLayanan][100];
	//memasukkan format ke dalam tabel string untuk digunakan di fungsi ask()
	for(int i = 0; i < jumlahLayanan; i++){
	    sprintf(menuLayanan[i+1], "%s: Rp%s", i+1, menu[i].namaLayanan, formatInt(menu[i].harga)); 
	}
	char temp[100]; // menyesuaikan ukuran sesuai kebutuhan
	sprintf(temp, "Menu Layanan %s", jenisHewan); //memformat string untuk ditambahkan ke tabel string indeks 0, yaitu hanya sebagai display dalam fungsi ask() dan bukan pilihan.
	strcpy(menuLayanan[0], temp);
	
	return ask(menuLayanan, jumlahLayanan);
}

// Fungsi menambah data reservasi
void addReservasi(){
    if(jumlahData >= MAX){
        printf("\tKapasitas penuh, tidak dapat menambah data.\n");
        return;
    }
    
    printf("\n\tNama Pemilik: ");
    scanf(" %[^\n]", data[jumlahData].namaPemilik);
    
    printf("\tNama Hewan: ");
    scanf(" %[^\n]", data[jumlahData].namaHewan);
    
    printf("\tJenis Hewan (Kucing/Anjing): ");
    scanf(" %[^\n]", data[jumlahData].jenisHewan);
	data[jumlahData].jenisHewan[0] = toupper(data[jumlahData].jenisHewan[0]);
	
	int pilihan = displayMenuLayanan(menuKucing, MAX_LAYANAN, data[jumlahData].jenisHewan);
	
    if(strcmp(data[jumlahData].jenisHewan,"Kucing") == 0){
        strcpy(data[jumlahData].layanan, menuKucing[pilihan - 1].namaLayanan);
        data[jumlahData].harga = menuKucing[pilihan-1].harga;
    }else{
        strcpy(data[jumlahData].layanan, menuAnjing[pilihan - 1].namaLayanan);
        data[jumlahData].harga = menuAnjing[pilihan-1].harga;
    }

    printf("\tPilih tanggal(dd-mm-yyyy): ");
    scanf(" %[^\n]",data[jumlahData].tanggal);
	
    jumlahData++;
    printf("\tReservasi berhasil ditambahkan!\n");
}


// Fungsi menampilkan daftar reservasi
void displayReservasi(){
    printf("\n\tDaftar Reservasi:\n");
    for (int i=0 ; i<jumlahData; i++){
        printf("\t%d. %s, %s (%s) - %s, Rp%s, %s\n", i+1,
           data[i].namaPemilik, data[i].namaHewan,
		   data[i].jenisHewan, data[i].layanan,
		   formatInt(data[i].harga), data[i].tanggal);
    }
}

// Fungsi laporan
void report(){
    int totalPendapatan = 0;
    for(int i=0; i<jumlahData; i++){
        totalPendapatan += data[i].harga;
    }
    printf("\n\tLaporan Harian\n");
    printf("\tTotal Pelanggan: %d\n", jumlahData);
    printf("\tTotal Pendapatan: Rp%s\n", formatInt(totalPendapatan));
}

// Fungsi mengurutkan reservasi
void sortingReservasi(){
    for(int i=0; i<jumlahData-1; i++){
        for(int j=0; j<jumlahData-i-1 ; j++){
            if(strcmp(data[j].tanggal, data[j + 1].tanggal) > 0 || (strcmp(data[j].tanggal, data[j + 1].tanggal) == 0 && strcmp(data[j].namaPemilik, data[j+1].namaPemilik) > 0)){
                Reservasi temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }
    printf("\n\tReservasi diurutkan berdasarkan tanggal dan nama pemilik.\n");
}

// Fungsi untuk menyimpan data ke file
void writeToFile(const char *filename){
    FILE *file = fopen(filename, "w"); // "w" menimpa/ membuat file
    if(file == NULL){
        printf("\tGagal membuka file untuk menyimpan data.\n");
        return;
    }
	
    // Simpan jumlah data
    fprintf(file, "%d\n", jumlahData);

    // Tulis semua data ke file
    for(int i = 0; i < jumlahData; i++){
        fprintf(file, "%s; %s; %s; %s; %d; %s\n",
            data[i].namaPemilik, data[i].namaHewan,
            data[i].jenisHewan, data[i].layanan,
            data[i].harga, data[i].tanggal);
    }

    fclose(file);
    printf("\tData berhasil disimpan ke file.\n");
}

// Fungsi read file
void readToFile(const char *filename){
    FILE *file = fopen(filename,"r");
    if(file == NULL){
        printf("\tTidak ada data sebelumnya (file belum dibuat).\n");
        return;
    }
	
    fscanf(file, "%d\n", &jumlahData); // Baca jumlah data
    for(int i=0; i<jumlahData; i++){
        fscanf(file, " %[^;]; %[^;]; %[^;]; %[^;]; %d; %[^\n]\n",
           data[i].namaPemilik,
           data[i].namaHewan,
           data[i].jenisHewan,
           data[i].layanan,
           &data[i].harga,
           data[i].tanggal);
    }

    fclose(file);
    printf("\tData berhasil dimuat dari file.\n");
}

//Fungsi untuk memformat angka
char* formatInt(int angka){
    char *str = malloc(20*sizeof(char));
    if(str == NULL){
        fprintf(stderr, "Memory allocation failed!\n");
        return NULL; 
    }
    
	//memasukkan angka ke string
    sprintf(str, "%d", angka);
    int len = strlen(str);
	
    for(int i=len-3; i>0; i-=3){
    	//memindahkan string setiap tiga angka
        memmove(&str[i+1], &str[i], len-i);
        str[i] = '.';
        len++;
    }
	
    return str;
}
