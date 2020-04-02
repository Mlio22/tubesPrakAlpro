/*
! catatan penting : 
! 1. compiler harus berjalan di mode c99
! 	=> -std=c99
! 2. kode tidak bisa dijalankan di code blocks (bisa diperbaiki nanti)
*/

#include <stdio.h>
#include <string.h>
#include <windows.h>

// Waktu Dihabiskan : 7

#define DATABASEFILE "DATABASE.txt"

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

//	deklarasi struktur data pasien
struct data
{
    int nomor,umur,status;
    char nama[50], tanggalLahir[8];
};


int main(){
	//todo: Membaca Database
    FILE *db;
    
    char data[20];
    char nama[50], tanggalLahir[8]; 
    int nomor, umur, status;

    if((db = fopen(DATABASEFILE,"r+")) == NULL){
        printf("DATABASE Tidak bisa diakses!\nMohon periksa perizinan file");
        exit(0);
    }

	//todo:	checking jika database kosong atau tidak
	char line[256];
	fgets(line, sizeof(line), db);
	
	if(strlen(line) == 0){
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
        fscanf(db, "%d$%[^$]$%d$%[^$]$%d\n",&pasien[i].nomor,&pasien[i].nama,&pasien[i].umur, &pasien[i].tanggalLahir, &pasien[i].status);
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
        
        int jumlahTab[5] = {1,1,1,1,1};

	//! khusus
		kalimatTerpanjang("Nama Lengkap", &jumlahTab[1]);

	// todo: mencari panjang tiap section data
		for(int j=0; j<totalData; j++){

		// todo: mencari digit terpanjang untuk int
			digitTerpanjang(pasien[j].nomor, &jumlahTab[0]);
			digitTerpanjang(pasien[j].umur, &jumlahTab[2]);
			digitTerpanjang(pasien[j].status, &jumlahTab[4]);

		// todo: mencari digit terpanjang untuk string
			kalimatTerpanjang(pasien[j].nama, &jumlahTab[1]);
			kalimatTerpanjang(pasien[j].tanggalLahir, &jumlahTab[3]);
		}

	// todo: menulis bagian awal tampilan
		printf("|");
		judulDaftar("Nomor", jumlahTab[0]);
		judulDaftar("Nama Lengkap", jumlahTab[1] - 1);
		judulDaftar("Umur", jumlahTab[2]);
		judulDaftar("DOB", jumlahTab[3]);
		judulDaftar("status", jumlahTab[4]);
		printf("\n");

	// todo: menulis bagian data tampilan
		for(int j=0; j<totalData; j++){
			printf("|");
			daftarDataInt(pasien[j].nomor, jumlahTab[0]);
			daftarDataString(pasien[j].nama, jumlahTab[1]);
			daftarDataInt(pasien[j].umur, jumlahTab[2]);
			daftarDataString(pasien[j].tanggalLahir, jumlahTab[3]);
			daftarDataInt(pasien[j].status, jumlahTab[4]);

			printf("\n");
		}

        break;

	//! algoritma untuk menambahkan data pasien
    case 2:
  	    fflush(stdin);
        printf("Masukkan Nama : "); gets(nama);
        printf("Masukkan Umur : "); scanf("%d",&umur);
        fflush(stdin);
  	    printf("Masukkan Tanggal Lahir : "); gets(tanggalLahir);
  	    printf("Masukkan status : "); scanf("%d", &status);

        fprintf(db, "%d$%s$%d$%s$%d\n", totalData+1, nama, umur, tanggalLahir, status);
        fflush(db);
        fseek(db, 0, SEEK_SET);
        fprintf(db, "%d#\n",++totalData);

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
