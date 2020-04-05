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
#include <stdlib.h>

// Waktu Dihabiskan : 17

#define DATABASEFILE "DATABASE.txt"

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
	gotoxy(5,1); 
	printf("TEKAN TOMBOL ESC UNTUK MEMBATALKAN");
}

void clearLine(WORD xLine, WORD yLine){
	gotoxy(xLine, yLine);
	int i = xLine;
	while(i < 80){
		printf(" ");
		i++;
	}
	printf("\n");
	gotoxy(xLine, yLine);
}

void printxy(char text[], const WORD x, const WORD y){
	gotoxy(x,y);
	printf("%s", text);
}

const char* inputDataString(int maxSize){
	char* input = (char*)malloc(maxSize * sizeof(char));
	char demo;
	strcpy(input, " ");
	int i = 0;

	// algoritma input data string(alphabet + angka + simbol)

	while(1){
		demo = getch();

		if(demo == 27){
			strcpy(input, "\b");
			break;
		}

		if(demo == '\r'){
			break;
		}

		if(demo == '\b' && i > 0){
			input[i-1] = '\0';
			printf("\b \b");
			i--;
		}else if(demo != '\b'){
			if(i < maxSize){
				input[i] = demo;
				printf("%c", input[i]);
				i++;
			}
		}
	}

	if(i != strlen(input) && strcmp(input, "\b") != 0){
		for(int j=i; j<=strlen(input); j++){
			input[j] = '\0';
		}
	}
	return input;
}

const char* inputDataInt(int maxSize){
	char* input = (char*)malloc(maxSize * sizeof(char));
	char demo;
	strcpy(input, " ");
	int i=0;

	// algoritma input data (hanya integer)
	while(1){
		demo = getch();

		if(demo == 27){
			return "99999";
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
			if(i < maxSize && (demo >= 48 && demo <= 57)){
				input[i] = demo;
				printf("%c", input[i]);
				i++;
			}
		}
	}

	if(i != strlen(input) && strcmp(input, "\b") != 0){
		for(int j=i; j<=strlen(input); j++){
			input[j] = '\0';
		}
	}

	return input;
}

//	deklarasi struktur data pasien
struct data{
    int nomor,umur,status;
    char nama[50], tanggalLahir[8], penyakit[50];
};

char* input;
int main(){
	//todo: Membaca Database
    FILE *db;
    
    char data[20];
    char nama[50], tanggalLahir[8], penyakit[50]; 
    int nomor, umur, status, valid=0;

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

	//todo: menambahkan data pasien
    case 2:
	//todo: untuk memasukkan nama pasien
		clearScreenInput();
		gotoxy(5,2);
				
		while(valid == 0){
			printf("Periksa Nama Pasien dengan teliti (hanya huruf)");
			strcpy(nama, "");
			clearLine(5,5);

			valid = 1;

			printf("Nama : "); strcpy(nama, inputDataString(50));
			if(strcmp(nama, "\b") == 0){
				printf("anda keluar");
				goto keluar;
			}

		//* proses validasi nama
			if(strlen(nama)>0){
				for(int i=0; i<strlen(nama); i++){
					if(nama[i] <65 || (nama[i] > 90 && nama[i] < 97) || nama[i] > 122){
						gotoxy(5,2);
						printf("nama tidak valid! ");
						valid = 0;
						break;
					}
				}
			}else{
				gotoxy(5,2);
				printf("nama tidak valid! ");
				valid = 0;
			}
		}

	//todo: memasukkan umur pasien
		clearLine(5,2);
		gotoxy(5,2);
		printf("Tuliskan umur pasien dengan benar");

		gotoxy(5,6);

		printf("Umur : "); umur = atoi(inputDataInt(3));

		if(umur == 99999){
			printf("anda keluar");
			goto keluar;
		}

	//todo: memasukkan tanggal Lahir pasien
		clearLine(1,2);
		valid = 0;
		gotoxy(5,2);

		//* proses validasi tanggal lahir
		while(valid == 0){
			printf("Tuliskan Tanggal Lahir Pasien dengan benar\n");
			gotoxy(5,3);
			printf("Format penulisan : ddmmyyyy (8 digit)");

			valid = 1;

			clearLine(5, 7);
			gotoxy(5,7);
			printf("Tanggal Lahir : ");
			strcpy(tanggalLahir, inputDataInt(8));
			

			if(strcmp(tanggalLahir, "99999") == 0){
				goto keluar;
			}

			//* algoritma validasi tanggal lahir
			if(strlen(tanggalLahir) != 8){
				gotoxy(5,2);
				printf("Penulisan tanggal lahir tidak valid! ");
				valid = 0;
			}else{
				// mengubah masing masing tanggal lahir menjadi integer
				int dd = (tanggalLahir[0] - '0')*10 + (tanggalLahir[1] - '0');
				int mm = (tanggalLahir[2] - '0')*10 + (tanggalLahir[3] - '0');
				int yyyy = (tanggalLahir[4] - '0')*1000 + (tanggalLahir[5] - '0')*100 + (tanggalLahir[6] - '0')*10 + (tanggalLahir[7] - '0');

				// algoritma check tanggal lahir (termasuk kabisat)

				if(yyyy < 1900 || yyyy > 2020){
					gotoxy(5,2);
					printf("Penulisan tanggal lahir tidak valid! ");
					valid = 0;
				}

				switch(mm){
				case 1:
				case 3:
				case 5:
				case 7:
				case 8:
				case 10:
				case 12:
					if(dd < 1 || dd > 31){
						gotoxy(5,2);
						printf("Penulisan tanggal lahir tidak valid! ");
						valid = 0;
					}
					break;
				case 4:
				case 6:
				case 9:
				case 11:
					if(dd < 1 || dd > 30){
						gotoxy(5,2);
						printf("Penulisan tanggal lahir tidak valid! ");
						valid = 0;
					}
					break;
				case 2:
					if(yyyy % 400 == 0 || (yyyy % 100 != 0 && yyyy % 4 == 0)){
						if(dd < 1 || dd > 29){
							gotoxy(5,2);
							printf("Penulisan tanggal lahir tidak valid! ");
							valid = 0;
						}
					}
					else{
						if(dd < 1 || dd > 28){
							gotoxy(5,2);
							printf("Penulisan tanggal lahir tidak valid! ");
							valid = 0;
						}
					}
					break;
				default:
					gotoxy(5,2);
					printf("Penulisan tanggal lahir tidak valid! ");
					valid = 0;
					break;
				}
			}
		}

	//todo: memasukkan status penyakit
		clearLine(1,3);
		valid = 0;
		clearLine(5,2);

		while(valid == 0){
			printf("Masukkan status penyakit pasien (sesuai angka indikator)\n");
			clearLine(14, 8);
			printxy("Indikator :",40, 4);
			printxy("1 : ICU / Gawat darurat", 40, 5);
			printxy("2 : Sakit Keras", 40, 6);
			printxy("3 : Sakit biasa", 40, 7);
			printxy("4 : Sembuh", 40, 8);

			valid = 1;

			gotoxy(5,8);
			printf("status : "); status = atoi(inputDataInt(1));

			if(status == 99999){
				goto keluar;
			}

		//* validasi status
			if(status < 1 || status > 4){
				gotoxy(5,2);
				printf("Status tidak valid! ");
				valid = 0;
			}
		}


	//todo: memasukkan nama Penyakit pasien
		clearLine(1,3);
		clearLine(40,4);
		clearLine(40,5);
		clearLine(40,6);
		clearLine(40,7);
		clearLine(40,8);
		clearLine(5,2);

		valid = 0;


		while(valid == 0){
			printf("Masukkan Nama penyakit pasien dengan benar(max 50 karakter)\n");
			strcpy(penyakit, "");

			valid = 1;

			gotoxy(5,9);
			printf("Nama Penyakit :"); strcpy(penyakit, inputDataString(50));
			if(strcmp(nama, "\b") == 0){
				printf("anda keluar");
				goto keluar;
			}

			if(strlen(penyakit)<1){
				gotoxy(5,2);
				printf("nama penyakit tidak valid! ");
				valid = 0;
			}
		}


		clearScreenInput();

		printf("\nanda menulis nama: %s\nUmur: %d\nTanggal Lahir: %s\nStatus : %d\nNama Penyakit : %s", nama, umur, tanggalLahir, status, penyakit);

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
	free(input);
    return 0;        
}
