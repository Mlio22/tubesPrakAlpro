/*
! catatan penting : 
! 1. compiler harus berjalan di mode c99 atau c11
! 	=> -std=c99
!	=> -std=c11
! 2. kode tidak bisa dijalankan di code blocks (bisa diperbaiki nanti)
*/

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

// Waktu Dihabiskan : 12

#define DATABASEFILE "DATABASE.txt"
#define MAX 256

/* 
* 	fungsi gotoxy dari internet 
* 	sumber : https://helloacm.com/modern-gotoxy-alternative-c/
*/
BOOL gotoxy(const WORD x, const WORD y) {
    COORD xy;
    xy.X = x;
    xy.Y = y;
    return SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy);
}

int kalimatTerpanjang(char data[], int *tab){
	// printf("panjang Nama lengkap adalah : %d", strlen(data));
	if((strlen(data)/7)+1 > *tab){
		*tab = strlen(data)/7 +1;
	}
}

void digitTerpanjang(int data, int *tab){
	char demo[10];

	sprintf(demo, "%d", data);
	if(strlen(demo)/7 > *tab){
		*tab = strlen(demo)/7 +1 ;
	}
}

void judulDaftar(char kata[], int tab){
	int i;
	printf("%s", kata);
	for(i = 0; i<tab; i++){
		printf("\t");
	}
	printf("|");
}

void daftarDataInt(int data, int tab){
	printf("%d", data);
	char demo[10];

	sprintf(demo, "%d", data);
	if(strlen(demo)/7 >= 1){
		tab -= strlen(demo)/7;
	}
	
	for(int j=0; j<tab; j++){
		printf("\t");
	}
	
	printf("|");
}

void daftarDataString(char data[], int tab){
	printf("%s", data);

	if(strlen(data)/7 >= 1){
		tab -= strlen(data)/7;
	}
	
	for(int j=0; j<tab; j++){
		printf("\t");
	}
	
	printf("|");
}

void clearScreenInput(){
	system("cls");
	gotoxy(3,1); 
	printf("TEKAN TOMBOL ESC UNTUK MEMBATALKAN");
}

const char* inputDataString(int maxSize){
	char* input = (char*)malloc(maxSize * sizeof(char));
	char demo;
	strcpy(input, " ");
	int i=0;

	// algoritma input data
	while(1){
		demo = getch();

		if(demo == 27){
			strcpy(input, "");
			break;
		}

		if(demo == '\r'){
			break;
		}

		if(demo == '\b' && i > 0){
			input[i-1] = '\0';
			printf("\b \b");
			i--;
		}else{
			if(i < maxSize){
				input[i] = demo;
				printf("%c", input[i]);
				i++;
			}
		}
	}

	if(i != strlen(input)){
		for(int j=i; j<=strlen(input); j++){
			input[j] = '\0';
		}
	}
	return input;
}

void inputDataInt(){

}

//	deklarasi struktur data pasien
struct data
{
    int nomor,umur,status;
    char nama[50], tanggalLahir[8], penyakit[50];
};

char* input;
int main(){
	//todo: Membaca Database
    FILE *db;
    
    char data[20];
    char nama[50], tanggalLahir[8], penyakit[50]; 
    int nomor, umur, status;

    if((db = fopen(DATABASEFILE,"r+")) == NULL){
        printf("DATABASE Tidak bisa diakses!\nMohon periksa perizinan file");
        exit(0);
    }

	//todo:	checking jika database kosong atau tidak
	char line[256];
	fgets(line, sizeof(line), db);
	
	if(strlen(line) <= 1){
		fprintf(db, "0#\n");
	}
    
	//todo:	mengambil data pasien
    int totalData;
	fflush(db);
	fseek(db, 0, SEEK_SET);
    
	if(!feof(db)){
		fscanf(db, "%d#\n", &totalData);	
	}
	
	int i = 0;
	
	struct data pasien[totalData];

	//todo:	membaca data pasien        
    while(!feof(db) && totalData > 0){
        fscanf(db, "%d$%[^$]$%d$%[^$]$%d%$[^$]\n",&pasien[i].nomor,&pasien[i].nama,&pasien[i].umur, &pasien[i].tanggalLahir, &pasien[i].status, &pasien[i].penyakit);
        i++;
    }		
   
//! menu utama
  	int menu;
   
   	printf("Selamat Datang\n1. Tampilkan Data Pasien\n2. Tambahkan Data Pasien\n3. Ubah Data Pasien\n");
   	printf("Masukkan Menu (Tombol lain untuk keluar) : "); scanf("%d",&menu);

  	switch (menu){
	//! algoritma untuk menampilkan data
    	case 1:
	
        if(totalData == 0){
           printf("Database kosong");
           goto keluar;
        }
        
        int jumlahTab[6] = {1,1,1,1,1,1};

	//! khusus
		kalimatTerpanjang("Nama Lengkap", &jumlahTab[1]);
		kalimatTerpanjang("Tanggal Lahir", &jumlahTab[3]);
		kalimatTerpanjang("Penyakit", &jumlahTab[5]);

	// todo: mencari panjang tiap section data
		for(int j=0; j<totalData; j++){

		// todo: mencari digit terpanjang untuk int
			digitTerpanjang(pasien[j].nomor, &jumlahTab[0]);
			digitTerpanjang(pasien[j].umur, &jumlahTab[2]);
			digitTerpanjang(pasien[j].status, &jumlahTab[4]);

		// todo: mencari digit terpanjang untuk string
			kalimatTerpanjang(pasien[j].nama, &jumlahTab[1]);
			kalimatTerpanjang(pasien[j].tanggalLahir, &jumlahTab[3]);
			kalimatTerpanjang(pasien[j].penyakit, &jumlahTab[5]);
		}

	// todo: menulis bagian awal tampilan
		printf("|");
		judulDaftar("Nomor", jumlahTab[0]);
		judulDaftar("Nama Lengkap", jumlahTab[1] - 1);
		judulDaftar("Umur", jumlahTab[2]);
		judulDaftar("Tanggal Lahir", jumlahTab[3]-1);
		judulDaftar("Status", jumlahTab[4]);
		judulDaftar("Penyakit", jumlahTab[5]-1);
		printf("\n");
		
	//! todo : membuat baris pemisah judul dan data

	// todo: menulis bagian data tampilan
		for(int j=0; j<totalData; j++){
			printf("|");
			daftarDataInt(pasien[j].nomor, jumlahTab[0]);
			daftarDataString(pasien[j].nama, jumlahTab[1]);
			daftarDataInt(pasien[j].umur, jumlahTab[2]);
			daftarDataString(pasien[j].tanggalLahir, jumlahTab[3]);
			daftarDataInt(pasien[j].status, jumlahTab[4]);
			daftarDataString(pasien[j].penyakit, jumlahTab[5]);

			printf("\n");
		}

        break;

	//! algoritma untuk menambahkan data pasien
    case 2:
	// untuk memasukkan nama pasien
		clearScreenInput();
				
		gotoxy(5,2);
		printf("Periksa Nama Pasien dengan teliti");

		gotoxy(7,4);
		// 
		printf("Nama :"); strcpy(nama, inputDataString(50));
		printf("nama yang anda tulis = %s", nama);
	// untuk memasukkan umur pasien
		// clearScreenInput();
				
		// gotoxy(5,2);
		// printf("Periksa Nama Pasien dengan teliti");

		// gotoxy(7,4);
		// printf("Nama :"); fflush(stdin); gets(nama);
		// goto

		// fflush(stdin);
        // printf("Masukkan Nama : "); gets(nama);
        // printf("Masukkan Umur : "); scanf("%d",&umur);
        // fflush(stdin);
  	    // printf("Masukkan Tanggal Lahir : "); gets(tanggalLahir);
  	    // printf("Masukkan status : "); scanf("%d", &status);
  	    // fflush(stdin);
		// printf("Masukkan Nama Penyakit : "); gets(penyakit);

        // fprintf(db, "%d$%s$%d$%s$%d$%s\n", totalData+1, nama, umur, tanggalLahir, status, penyakit);
        // fflush(db);
        // fseek(db, 0, SEEK_SET);
        // fprintf(db, "%d#\n",++totalData);

        break;
	//! algoritma untuk mengubah data pasien
    case 3:
        printf("Anda masuk ke menu 3");
        break;
    default:
        printf("Anda masuk ke menu keluar\n");
        printf("Keluar Lu ASW!\n");
        goto keluar;
        break;
    }

    keluar:
    printf("\nanda keluar");
    fclose(db);
    return 0;        
}
