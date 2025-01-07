#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>



// Enum untuk jenis makanan
enum JenisMakanan {
    MAKANAN_UTAMA,
    MINUMAN,
    MAKANAN_RINGAN
};

// Struct untuk menyimpan data makanan
struct Makanan {
    char nama[30];
    enum JenisMakanan jenis;
    int harga;
};


// Fungsi swap untuk menukar dua elemen
void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Selection Sort
/*
Mencari nilai minimum dari dataset kemudian ditaruh ke depan, dari depan ke belakang
Best case: jika hanya perlu menukar angka terakhir
Waktu: cukup lama, namun lebih cepat dari bubble sort, karena dataset pengecekan terus berubah sesuai sisa yang belum diurutkan
*/
void selectionSort(struct Makanan arr[], int n) {
    int i, j, min_idx;
    for (i = 0; i < n - 1; i++) {
        // Inisialisasi indeks elemen minimum pada iterasi saat ini
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j].harga < arr[min_idx].harga) {
                min_idx = j;
            }
        }
        // Tukar seluruh struktur, bukan hanya anggota-anggotanya
        struct Makanan temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

// bagian dari Merge Sort
void merge(int arr[], int left, int mid, int right){
    int n1 = mid - left + 1, n2 = right - mid, L[n1], R[n2];
    for(int i=0; i<n1; i++){
        L[i] = arr[left+i];
	    for(int j=0; j<n2; j++){
	        R[j] = arr[mid+1+j];
		    int i=0, j=0, k=left;
		    while(i<n1 && j<n2){
		        if(L[i] <= R[j]){
		            arr[k] = L[i];
		            i++;
		        }else{
		            arr[k] = R[j];
		            j++;
		        }
		        k++;
		    }
		    while(i<n1){
		        arr[k] = L[i];
		        i++;
		        k++;
		    }
		    while(j<n2){
		        arr[k] = R[j];
		        j++;
		        k++;
		    }
		}
	}
}

// Merge Sort
/*
Melakukan pengulangan secara rekursif membagi dua dataset dan menggabungkannya kembali dengan dataset sementara sambil menukarnya jika angka dataset pertama lebih besar, (konsep divide and conquer)
Best case: dataset genap, acak secara berurut, misal 2 1 4 3 6 5
Waktu: O(n log n)
*/
void mergeSort(int arr[], int left, int right){
    if(left<right){
        int m = left + (right-left)/2;
        mergeSort(arr, left, m);
        mergeSort(arr, m+1, right);
        merge(arr, left, m, right);
    }
}

// Insertion Sort
/*
menggunakan dua array, satu terurut, dan satunya tidak terurut
	ambil elemen pertama, lakukan pengulangan dengan memandingkan pada elemen kiri atau yang telah terurut dan geser sesuai posisis yang tepat
Best case: 
Waktu: O(n) hingga O(n^2)
*/
void insertionSort(int arr[], int n){
	int i, key, j;
	for (i = 1; i<n; i++){
		key = arr[i];
		j = i - 1;
		while (j >= 0 && arr[j] > key){
	       arr[j+1] = arr[j];
	       j = j-1;
		}
		arr[j+1] = key;
	}
}

// Bubble Sort
/*
Mengecek setiap angka dengan angka di sebelahnya kemudian ditukar jika angka perama lebih besar
Best case: hanya angka urutan pertama dan kedua yang perlu ditukar
Waktu: pasti lama karena melakukan pengecekan dengan jumlah pengulangan yang sama O(n^2)
*/
void bubbleSort(int arr[], int n){
   int i, j;
   for(i = 0; i < n-1; i++){
		for (j = 0; j < n-i-1; j++){
			if (arr[j] > arr[j+1]){
				swap(&arr[j], &arr[j+1]);
			}
		}
	}
}

// Bagian dari quick sort untuk memenuhi recursion
int partition(int array[], int low, int high){
    int pivot = array[high];
    int i = (low-1);
    for(int j = low; j <= high-1; j++){
        if(array[j] <= pivot){
            i++;
            swap(&array[i], &array[j]);
        }
    }
    swap(&array[i+1], &array[high]);
    return (i+1);
}

// Quick Sort
/*
Melakukan rekursi dengan 
	mengambil pivot,
	mengambil angka dari kiri yang lebih besar dari pivot,
	mengambil angka dari kanan yang lebih kecil dari pivot,
	menukar angka besar dengan angka kecil,
	kemudian menukar angka besar dengan pivot
(pada subarray di sebelah kiri pivot dan subarray di sebelah kanan pivot.)

Best Case: ketika pivot yang diambil tepat seperti mengambil median dari tiga elemen, dan data sudah terurut sebagian

Waktu: berubah ubah, tergantung dataset O(n^2) hingga A(n log n)
*/
void quickSort(int array[], int low, int high){
    if(low<high){
        int pi = partition(array, low, high);
        quickSort(array, low, pi-1);
        quickSort(array, pi+1, high);
    }
}


// Binary Search
/*
Membagi array menjadi dua bagian secara berulang.
Membandingkan elemen tengah dengan nilai yang dicari.
Jika nilai yang dicari lebih kecil dari elemen tengah, pencarian dilanjutkan pada bagian kiri.
Jika nilai yang dicari lebih besar dari elemen tengah, pencarian dilanjutkan pada bagian kanan.
Binary search lebih cepat dibanding dengan Linear Serch.
*/
int binarySearch(int arr[], int l, int r, int x){
    if(r >= l){
        int mid = l + (r - l) / 2;
        if(arr[mid] == x)
            return mid;
        if(arr[mid] > x)
            return binarySearch(arr, l, mid - 1, x);
        return binarySearch(arr, mid + 1, r, x);
    }
    return -1;
}

// Linear Search
/*
Mencari elemen secara berurutan dari awal hingga akhir array.
Linear Search adalah algoritma yang paling sederhana tetapi juga paling lambat.
*/
int linearSearch(int arr[], int n, int x){
    for(int i = 0; i < n; i++){
        if(arr[i] == x){
            return i;
		}
	}
    return -1;
}

// Interpolation Search
/*
Menggunakan interpolasi untuk memperkirakan posisi elemen yang dicari.
Lebih efisien daripada Binary Search untuk data yang terdistribusi secara merata.	
*/
int interpolationSearch(int arr[], int lo, int hi, int x){
    int pos;
    if(x < arr[lo])
        return -1;
    if(x > arr[hi])
        return -1;
    pos = lo + (((double)(hi - lo)/(arr[hi]-arr[lo]))*(x-arr[lo]));
    if(arr[pos] == x)
        return pos;
    if(arr[pos] < x)
        return interpolationSearch(arr, pos + 1, hi, x);
    return interpolationSearch(arr, lo, pos - 1, x);
}


// Fungsi untuk menghitung total harga berdasarkan jenis makanan dan jumlah pesanan
float hitungTotalHarga(struct Makanan makanan, int jumlah){
    return makanan.harga*jumlah;
}

// Fungsi untuk menampilkan jenis menu dalam bentuk string
const char* jenisMenu(enum JenisMakanan jenis){
    switch(jenis){
        case MAKANAN_UTAMA: return "Makanan Utama";
        case MINUMAN: return "Minuman";
        case MAKANAN_RINGAN: return "Makanan Ringan";
        default: return "?";
    }
}

//Fungsi untuk memformat angka
char* formatInt(int angka){
    char *str = malloc(20 * sizeof(char));
    if(str == NULL){
        fprintf(stderr, "Memory allocation failed!\n");
        return NULL; 
    }
	
    sprintf(str, "%d", angka);
    int len = strlen(str);
	
    for(int i =len-3; i>0; i-=3){
        memmove(&str[i+1], &str[i], len-i);
        str[i] = '.';
        len++;
    }
	
    return str;
}

int main(){
    int jumlahMenu;

    // Minta input jumlah menu makanan
    printf("\n\n\n\tMasukkan jumlah menu yang tersedia: ");
    scanf("%d",&jumlahMenu); getchar();

    struct Makanan menu[jumlahMenu];
	
    // Minta input data menu makanan
    for(int i = 0; i < jumlahMenu; i++) {
        printf("\n\n\t 1. Makanan Utama\n\t 2. Minuman\n\t 3. Makanan Ringan\n\tMasukkan jenis menu: ");
        int jenis;
        scanf("%d",&jenis); getchar();
        
		printf("\tMasukkan nama menu ke-%d: ", i+1);
		scanf("%[^\n]s",&menu[i].nama); getchar();
		
        printf("\tMasukkan harga menu ke-%d: ", i+1);
        scanf("%d",&menu[i].harga); getchar();
		
        menu[i].jenis = jenis-1; // mengonversi input dengan enum
    }
    
    selectionSort(menu,sizeof(menu)/sizeof(menu[0])); //SORT
	
	// Menulis data menu ke file CSV
	FILE *fp = fopen("menu.csv", "w");
    if (fp == NULL) {
        printf("Error membuka file!\n");
        return 1;
    }

    for(int i = 0; i < jumlahMenu; i++){
        fprintf(fp, "%s, %d, %d\n", menu[i].nama, menu[i].jenis, menu[i].harga);
    }
    fclose(fp);
	
    // Menampilkan menu dan meminta pemesanan
    printf("\n\t- - - Menu Makanan - - -\n");
    for(int i = 0; i < jumlahMenu; i++){
        printf("\t%d. %s (%s) | Harga: %s\n", i+1, menu[i].nama, jenisMenu(menu[i].jenis), formatInt(menu[i].harga));
    }
	
    // Pemesanan
    int pilihan, jumlah;
    int totalHarga = 0;
	
    while(1){
        printf("\n\tPilih menu (masukkan 0 untuk memesan): ");
        scanf("%d", &pilihan); getchar();
		
        if (pilihan == 0){
            break;
        }else if (pilihan < 1 || pilihan > jumlahMenu){
            printf("\tPilihan tidak valid. Silakan coba lagi.\n");
            continue;
        }

        printf("\tMasukkan jumlah pesanan: ");
        scanf("%d", &jumlah); getchar();
		
        // Menambahkan total harga
        totalHarga += hitungTotalHarga(menu[pilihan-1], jumlah);
    }
	
	// Membaca data menu dari file CSV dan menampilkannya
	printf("\n\t- - - Riwayat Pemesanan - - -\n");
    fp = fopen("menu.csv", "r");
    if(fp == NULL){
        printf("\n\tError membuka file!\n");
        return 1;
    }
	
    char line[100];
    while(fgets(line, sizeof(line), fp)){
        char nama[30], jenisStr[15];
        int harga;
        if (sscanf(line, "%[^,], %[^,], %d", nama, jenisStr, &harga) == 3){
        	// Konversi string jenis menjadi enum
        	enum JenisMakanan jenis;
	        if(strcmp(jenisStr, "Makanan Utama") == 0){
	            jenis = MAKANAN_UTAMA;
	        }else if(strcmp(jenisStr, "Minuman") == 0){
	            jenis = MINUMAN;
	        }else{
	            jenis = MAKANAN_RINGAN;
	        }
        	printf("\t%s (%s) | Harga: %s\n", nama, jenisMenu(jenis), formatInt(harga));
		}else{
			printf("Error, gagal membaca data dari file CSV.\n");
		}
    }
    fclose(fp);
    
    // Menampilkan total harga
    printf("\n\tTotal harga pesanan Anda: %s\n", formatInt(totalHarga));
	
    return 0;
}
