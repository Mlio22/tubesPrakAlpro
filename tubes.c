// ! catatan penting : compiler harus berjalan di mode c99
// ! -std=c99
#include <stdio.h>
#include <string.h>
#include <windows.h>

// Waktu Dihabiskan : 7

#define DATABASEFILE "DATABASE.txt"

//	fungsi dan prosedur dari project sebelumnya
int digitTerpanjang(float data, int ket){
	char hasil2[20];
	int terpanjang = 1;
	sprintf(hasil2,"%f",data);

	if((strlen(hasil2) - 8 + ket) > 4){
		terpanjang = (strlen(hasil2)/6) +1;
	}
	return terpanjang;
}

void kalimatAwal(char kata[5],int tab){
	printf("|%s",kata);
	for (int j=0;j<tab;j++){
		printf("\t");
	}
}

void kalimatIterasi(int data, int tab){
	printf("|%d",data);
	for (int j=0;j<tab;j++){
		printf("\t");
	}
}

void kalimatData(float data, int tab, int ket){
	char hasil2[10];
	sprintf(hasil2,"%f",data);
	switch (ket){
		case 1:
			printf("|%.1f",data);
			break;
		case 2:
			printf("|%.2f",data);
			break;
		case 3:
			printf("|%.3f",data);
			break;
		case 4:
			printf("|%.4f",data);
			break;
		case 5:
			printf("|%.5f",data);
			break;
		case 6:
			printf("|%.6f",data);
			break;
	}
	if(strlen(hasil2) - 6 + ket >= 6){
		tab -= ((strlen(hasil2) - (6-ket-1))/8
		);
	}
	for (int j=0;j<tab;j++){
		printf("\t");	
	}
}

//	deklarasi struktur data pasien
struct data
{
    int nomor,umur,status;
    char nama[50], tanggalLahir[8];
};


int main(){
    // Membaca Database
    FILE *db;
    
    char data[20];
    char nama[50], tanggalLahir[8]; 
    int nomor, umur, status;

    if((db = fopen(DATABASEFILE,"r+")) == NULL){
        printf("DATABASE Tidak bisa diakses!\nMohon periksa perizinan file");
        exit(0);
    }

	//	checking jika database kosong atau tidak
	char line[256];
	fgets(line, sizeof(line), db);
	
	if(strlen(line) == 0){
		fprintf(db, "0#\n");
	}
    
    // mengambil data pasien
    int totalData;
	fflush(db);
	fseek(db, 0, SEEK_SET);
    
	if(!feof(db)){
		fscanf(db, "%d#\n", &totalData);	
	}
	
	int i = 0;
	
	struct data pasien[totalData];
    // membaca data pasien
        
    while(!feof(db) && totalData > 0){
        fscanf(db, "%d$%[^$]$%d$%[^$]$%d\n",&pasien[i].nomor,&pasien[i].nama,&pasien[i].umur, &pasien[i].tanggalLahir, &pasien[i].status);
        i++;
    }		
   
   // menu utama
   int menu;
   
   printf("Selamat Datang\n1. Tampilkan Data Pasien\n2. Tambahkan Data Pasien\n3. Ubah Data Pasien\n");
   printf("Masukkan Menu (Tombol lain untuk keluar) : "); scanf("%d",&menu);

  switch (menu)
  {
    case 1:
        if(totalData == 0){
           printf("Database kosong");
           goto keluar;
        }
        if(i>0){
        	printf("|No\t|Nama\t|Umur\t|DOB\t|status\t|\n");
        	for(int j=0; j<i; j++){
         		printf("|%d\t|%s\t|%d\t|%s\t|Status: %d|\n",pasien[j].nomor, pasien[j].nama, pasien[j].umur, pasien[j].tanggalLahir, pasien[j].status);
        	}	
		}
        break;
        
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
