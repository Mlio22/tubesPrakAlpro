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

// Waktu Dihabiskan : 24

#define DATABASEFILE "DATABASE.txt"
#define TEMPFILE "temp.txt"
#define USERFILE "user.txt"

//	deklarasi struktur data pasien
struct data{
    int nomor,umur,status, kamar;
    char nama[50], tanggalLahir[8];
};

struct auth{
	char username[50], password[50];
};

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

	if(i < maxSize && strcmp(input, "\b") != 0){
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

int compareValueString(char string[], char search[]){
	if(strcmp(string, search) == 0){
		return 1;
	}
	else {
		return 0;
	}
}

int compareValueInt(int value, char search[]){
	if(value == atoi(search)){
		return 1;
	}
	else{
		return 0;
	}
}

void swapStruct(struct data *a, struct data *b){
	struct data temp = *a;
	*a = *b;
	*b = temp;
}

int compareDOB(char tanggal1[], char tanggal2[]){
	int i;
	char hari[2][2], bulan[2][2], tahun[2][4];
	int hari_int[2], bulan_int[2], tahun_int[2];

	for(i = 0; i<strlen(tanggal1); i++){
		if(i > 3){
			tahun[1][i-4] = tanggal1[i];
		}else if(i>1){
			bulan[1][i-2] = tanggal1[i];
		}else{
			hari[1][i] = tanggal1[i];
		}
	}

	for(i = 0; i<strlen(tanggal2); i++){
		if(i > 3){
			tahun[2][i-4] = tanggal2[i];
		}else if(i>1){
			bulan[2][i-2] = tanggal2[i];
		}else{
			hari[2][i] = tanggal2[i];
		}
	}

	for(i = 0; i < 2; i++){
		hari_int[i] = atoi(hari[i]);
		bulan_int[i] = atoi(bulan[i]);
		tahun_int[i] = atoi(tahun[i]);
	}

	// mulai dari tahun
	if(tahun_int[0] > tahun_int[1]){
		return 1;
	}else if(tahun_int[0] == tahun_int[1]){
		if(bulan_int[0] > bulan_int[1]){
			return 1;
		}else if(bulan_int[0] == bulan_int[1]){
			if(hari_int[0] > hari_int[1]){
				return 1;
			}
		}
	}
	return 0;
}


char* input;
int main(){
	char data[20];
    char nama[50], tanggalLahir[8], test, username[50], password[50], password_ver[50],line[256];
    int nomor, umur, status, kamar, valid=0, i, j, count = 0, totalData, menu;

	// login dan registrasi
	FILE *userdb, *db, *temp;

	userdb = fopen(USERFILE, "a+");
	db = fopen(DATABASEFILE, "a+");
	temp = fopen(TEMPFILE, "a+");

	fclose(userdb);
	fclose(db);
	fclose(temp);

	if((db = fopen(DATABASEFILE,"r+")) == NULL){
        printf("DATABASE Tidak bisa diakses!\nMohon periksa perizinan file");
        exit(0);
    }

	if((userdb = fopen(USERFILE,"r+")) == NULL){
        printf("DATABASE Tidak bisa diakses!\nMohon periksa perizinan file");
        exit(0);
    }

	// mengambil data pengguna (hehe)
	count = 0;
	//todo:	checking jika database kosong atau tidak
	while(fgets(line, sizeof(line), userdb) != NULL){
		count++;
	}
	
	if(count == 0){
		fprintf(userdb, "0#\n");
	}

	//todo:	mengambil data pasien
	fseek(userdb, 0, SEEK_SET);
    
	if(!feof(userdb)){
		fscanf(userdb, "%d#\n", &totalData);	
	}

	struct auth *user;
	user = (struct auth*)malloc(totalData * sizeof(struct auth));

	//todo:	membaca data pasien  
	i = 0;      
    while(!feof(userdb) && totalData > 0){
		fscanf(userdb, "%[^$]$%[^$]$\n", &user[i].username, &user[i].password);
        i++;
    }

	// ! menu login
	printf("SELAMAT DATANG!\n1.LOGIN\n2.REGISTRASI\n");
  	printf("Masukkan Menu (Tombol lain untuk keluar) : "); scanf("%d",&menu);
	system("cls");

	switch(menu){
		case 1:
		if(totalData == 0){
			printf("data kososng! silahkan buat akun baru");
			goto keluar;
		}

		while(1){
			printf("Masukkan Username : "); strcpy(username, inputDataString(50));
			printf("\nMasukkan Password : "); strcpy(password, inputDataString(50));

			for(i = 0; i < totalData; i++){
				if((strcmp(user[i].username, username) == 0) && (strcmp(user[i].password, password) == 0)){
					printf("bener kok");
					goto utama;
				}
			}
			system("cls");
			printf("Username atau password anda salah!\n");
		}
		
		break;

		case 2:

		while(1){
			printf("masukkan Username : "); strcpy(username, inputDataString(50));
			printf("\nmasukkan password : "); strcpy(password, inputDataString(50));
			printf("\nUlangi password : "); strcpy(password_ver, inputDataString(50));

			if(strcmp(password, password_ver) == 0){
				if((temp = fopen(TEMPFILE,"w+")) == NULL){
  				    printf("DATABASE Tidak bisa diakses!\nMohon periksa perizinan file");
  				    exit(0);
  				}
				
				fprintf(temp, "%d#\n", totalData+1);
				printf("%d# dengan posisi : %d\n", totalData+1,ftell(temp));
				for(i = 0; i<totalData; i++){
					fprintf(temp, "%s$%s$\n", user[i].username, user[i].password);
					printf("%s$%s$\n", user[i].username, user[i].password);
				}

				fprintf(userdb, "%s$%s$\n", username, password);
				printf("%s$%s$\n", username, password);

				fseek(userdb, 0, SEEK_SET);
				fseek(temp, 0, SEEK_SET);

				while((test = fgetc(temp)) != EOF){
					fputc(test, userdb);
				}
				fclose(temp);

				goto utama;
				break;
			}
			system("cls");
			printf("Password anda tidak sama!\n");
		}
		break;
	}

	//todo: Membaca Database

	utama:
	system("cls");
	printf("memeriksa database pasien..\n");
    int jumlahTab[6] = {1,1,1,1,1,1};

	count = 0;
	//todo:	checking jika database kosong atau tidak
	while(fgets(line, sizeof(line), db) != NULL){
		count++;
	}
	
	if(count == 0){
		fprintf(db, "0#\n");
	}
	
	//todo:	mengambil data pasien
	fflush(db);
	fseek(db, 0, SEEK_SET);
    
	if(!feof(db)){
		fscanf(db, "%d#\n", &totalData);	
	}
	
	printf("jumlah : %d\n", totalData);
	
	i = 0;
	
	struct data *pasien;
	pasien = (struct data*)malloc(totalData * sizeof(struct data));

	//todo:	membaca data pasien        
    while((!feof(db)) && totalData > 0){
        fscanf(db, "%d$%[^$]$%d$%[^$]$%d$%d$\n",&pasien[i].nomor,&pasien[i].nama, &pasien[i].umur, &pasien[i].tanggalLahir, &pasien[i].status, &pasien[i].kamar);
//        printf("%d\t%s\t%d\t%s\t%d\t%d\n", pasien[i].nomor, pasien[i].nama, pasien[i].umur, pasien[i].tanggalLahir, pasien[i].status, pasien[i].kamar);
        i++;
    }	

	//! menu utama
   	printf("Selamat Datang\n1. Tampilkan Data Pasien\n2. Tambahkan Data Pasien\n3. Ubah Data Pasien\n");
   	printf("Masukkan Menu (Tombol lain untuk keluar) : "); scanf("%d",&menu);

  	switch (menu){
	//! algoritma untuk menampilkan data
    	case 1:
	
        if(totalData == 0){
           printf("Database kosong");
           goto keluar;
        }
        
        // int jumlahTab[6] = {1,1,1,1,1,1};

	//! khusus
		kalimatTerpanjang("Nama Lengkap", &jumlahTab[1]);
		kalimatTerpanjang("Tanggal Lahir", &jumlahTab[3]);

	// todo: mencari panjang tiap section data
		for(int j=0; j<totalData; j++){

		// todo: mencari digit terpanjang untuk int
			digitTerpanjang(pasien[j].nomor, &jumlahTab[0]);
			digitTerpanjang(pasien[j].umur, &jumlahTab[2]);
			digitTerpanjang(pasien[j].status, &jumlahTab[4]);
			digitTerpanjang(pasien[i].kamar, &jumlahTab[5]);

		// todo: mencari digit terpanjang untuk string
			kalimatTerpanjang(pasien[j].nama, &jumlahTab[1]);
			kalimatTerpanjang(pasien[j].tanggalLahir, &jumlahTab[3]);
		}

	// todo: menulis bagian awal tampilan
		printf("|");
		judulDaftar("Nomor", jumlahTab[0]);
		judulDaftar("Nama Lengkap", jumlahTab[1] - 1);
		judulDaftar("Umur", jumlahTab[2]);
		judulDaftar("Tanggal Lahir", jumlahTab[3]-1);
		judulDaftar("Status", jumlahTab[4]);
		judulDaftar("Kamar", jumlahTab[5]);
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
			daftarDataInt(pasien[j].kamar, jumlahTab[5]);

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
					if((nama[i] <65 || (nama[i] > 90 && nama[i] < 97) || nama[i] > 122) && nama[i] != 32){
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

	//todo: memasukkan nomor Kamar pasien
		clearLine(1,3);
		clearLine(40,4);
		clearLine(40,5);
		clearLine(40,6);
		clearLine(40,7);
		clearLine(40,8);
		clearLine(5,2);

		valid = 0;


		while(valid == 0){
			printf("Masukkan Nomor kamar pasien");
			
			valid = 1;

			gotoxy(5,9);
			printf("Nomor Kamar :"); kamar = atoi(inputDataInt(3));
			if(kamar == 99999){
				goto keluar;
			}
		}

		clearScreenInput();

		if((temp = fopen(TEMPFILE,"w+")) == NULL){
  		    printf("DATABASE Tidak bisa diakses!\nMohon periksa perizinan file");
  		    exit(0);
  		}
		
		fprintf(temp, "%d#\n", totalData+1);

		for(i = 0; i<totalData; i++){
			fprintf(temp, "%d$%s$%d$%s$%d$%d$\n", pasien[i].nomor, pasien[i].nama, pasien[i].umur, pasien[i].tanggalLahir, pasien[i].status, pasien[i].kamar);
		}

		fprintf(temp, "%d$%s$%d$%s$%d$%d$\n", totalData+1, nama, umur, tanggalLahir, status, kamar);

		fseek(db, 0, SEEK_SET);
		fseek(temp, 0 , SEEK_SET);
		while((test = fgetc(temp)) != EOF){
			fputc(test, db);
		}
		fclose(temp);

		printf("Proses berhasil");
        break;
	//! algoritma untuk mengubah data pasien
    case 3:
		if(totalData == 0){
			printf("database kosong!");
			goto keluar;
		}
    	clearScreenInput();
		gotoxy(5,2);
		printf("tekan tombol arrow panah atas dan bawah untuk mengubah kategori");
		gotoxy(5,3);
		printf("Masukkan kata kunci maksimal 50 karakter");

		char demo = 0;
		int counter = 0, len = 0;
		char search[50];
		int i, bar;
		strcpy(search, "");
		struct data *result;

		while(1){
			clearLine(5,5);
			printf("cari berdasarkan ");

			if(counter > 5){
				counter = 0;
			}else if(counter < 0){
				counter = 5;
			}
			
			switch (counter)
			{
			case 0:
				printf("nomor\t\t : ");
				break;
			case 1:
				printf("nama\t\t : ");
				break;
			case 2:
				printf("umur\t\t : ");
				break;
			case 3:
				printf("tanggal lahir\t : ");
				break;
			case 4:
				printf("status\t\t : ");
				break;
			case 5:
				printf("kamar\t\t : ");
				break;
			}

			if(strlen(search) != 0){
				printf("%s", search);
			}

			while(1){
				demo = getch();
				if(demo == '\r' || demo == 27){
					break;
				}
				else if(demo == -32){
					demo = getch();
					if(demo == 72){
						counter++;
						break;
					}else if(demo == 80){
						counter--;
						break;
					}
				}else if(demo == '\b' && len > 0){
					search[len-1] = '\0';
					printf("\b \b");
					len--;
				}else if(demo != '\b'){
					search[len] = demo;
					printf("%c", search[len]);
					len++;
				}
			}
			if(demo == '\r' || demo == 27){
				break;
			}
		}

		int total = 0;
		result = (struct data*)malloc(total * sizeof(struct data));

	//todo : searching menggunakan binary search
		//* mencari data yang cocok dengan pencarian
		for(i = 0; i < totalData; i++){
			int same = 0;

			switch (counter)
			{
			case 0:
				same = compareValueInt(pasien[i].nomor, search);
				break;
			case 1:
				same = compareValueString(pasien[i].nama, search);
				break;
			case 2:
				same = compareValueInt(pasien[i].umur, search);
				break;
			case 3:
				same = compareValueString(pasien[i].tanggalLahir, search);
				break;
			case 4:
				same = compareValueInt(pasien[i].status, search);
				break;
			case 5:
				same = compareValueInt(pasien[i].kamar, search);
				break;
			}

			if(same == 1){
				total++;
				result = realloc(result, total * sizeof(struct data));
				result[total-1] = pasien[i];
			}
		}

		if(total == 0){
			printf("\n\npencarian tidak ditemukan");
	        break;
		}else{
			// mengubah menjadi lowercase
			for(i = 0; i<total; i++){
				for(j = 0; j<strlen(result[i].nama); j++){
					result[i].nama[j] = tolower(result[i].nama[j]);
				}
			}
		}

		counter = 0;
		
		while(1){

			clearScreenInput();
			printxy("Tekan enter untuk mengedit", 5,2);
			printxy("tekan atas atau bawah untuk mencari yang diedit",5,3);
			printxy("tekan kanan atau kiri untuk mengubah urutan",5,4);
			printxy("diurutkan berdasarkan : ", 5, 5); 

			if(counter > 5){
				counter = 0;	
			}

			if(counter < 0){
				counter = 5;
			}

			for(i = 0; i< total-1; i++){
				for(j = 0; j <total-i-1; j++){
					switch(counter){
				// bubble sort
					case 0:
					// berdasarkan nomor
					printf("Nomor");
					if(result[i+1].nomor < result[i].nomor){
						swapStruct(&result[i+1], &result[i]);
					}
					break;
					case 1:
					printf("Nama");
					// berdasarkan nama
					if(strcmp(result[i+1].nama, result[i].nama) == -1){
						swapStruct(&result[i+1], &result[i]);
					}
					break;
					case 2:
					printf("Umur");
					// berdasarkan umur
					if(result[i+1].umur< result[i].umur){
						swapStruct(&result[i+1], &result[i]);
					}
					break;
					case 3:
					printf("Tanggal Lahir");
					// berdasarkan tanggalLahir
					if(compareDOB(result[i].tanggalLahir, result[i+1].tanggalLahir)){
						swapStruct(&result[i+1], &result[i]);
					}
					break;
					case 4:
					printf("Status");
					// berdasarkan status
					if(result[i+1].status < result[i].status){
						swapStruct(&result[i+1], &result[i]);
					}
					break;
					case 5:
					printf("Kamar");
					// berdasarkan kamar
					if(result[i+1].kamar < result[i].kamar){
						swapStruct(&result[i+1], &result[i]);
					}
					break;	
					}	
				}
			}
			
			//! khusus
			kalimatTerpanjang("Nama Lengkap", &jumlahTab[1]);
			kalimatTerpanjang("Tanggal Lahir", &jumlahTab[3]);
	
			// todo: mencari panjang tiap section data
			for(int j=0; j<total; j++){

			// todo: mencari digit terpanjang untuk int
				digitTerpanjang(result[j].nomor, &jumlahTab[0]);
				digitTerpanjang(result[j].umur, &jumlahTab[2]);
				digitTerpanjang(result[j].status, &jumlahTab[4]);
				digitTerpanjang(result[i].kamar, &jumlahTab[5]);

			// todo: mencari digit terpanjang untuk string
				kalimatTerpanjang(result[j].nama, &jumlahTab[1]);
				kalimatTerpanjang(result[j].tanggalLahir, &jumlahTab[3]);
			}

			// todo: menulis bagian awal tampilan
			gotoxy(0,8);
			printf("|");
			judulDaftar("Nomor", jumlahTab[0]);
			judulDaftar("Nama Lengkap", jumlahTab[1] - 1);
			judulDaftar("Umur", jumlahTab[2]);
			judulDaftar("Tanggal Lahir", jumlahTab[3]-1);
			judulDaftar("Status", jumlahTab[4]);
			judulDaftar("Kamar", jumlahTab[5]);
			printf("\n");
		
			// todo: menulis bagian data tampilan
			for(int j=0; j<total; j++){
				printf("|");
				daftarDataInt(result[j].nomor, jumlahTab[0]);
				daftarDataString(result[j].nama, jumlahTab[1]);
				daftarDataInt(result[j].umur, jumlahTab[2]);
				daftarDataString(result[j].tanggalLahir, jumlahTab[3]);
				daftarDataInt(result[j].status, jumlahTab[4]);
				daftarDataInt(result[j].kamar, jumlahTab[5]);
				printf("\n");
			}

			int totalTab = 0;
		
			for(int j = 0; j < 6; j++){
				totalTab += jumlahTab[j];
			}

			bar = 9;

			while (1){
				gotoxy(totalTab*8+1, bar);
				printf("%d", counter);

				demo = getch();
				if(demo == '\r' || demo == 27){
					break;
				}
				else if(demo == -32){
					printf("\b \b");
					demo = getch();
					if(demo == 80 && bar < 8 + total){
						bar++;
					}else if(demo == 72 && bar > 9){
						bar--;
					}else if(demo == 77){
						// kekanan
						counter++;
						break;
					}else if(demo == 75){
						// kekiri
						counter--;
						break;
					}
				}
			}
			if(demo == '\r' || demo == 27){
					break;
			}
		}

		if(demo == '\r'){
			demo = '\0';

			char **input;
			input = malloc(5 * sizeof(char*));
			
			int max[5] = {50, 3, 8, 1, 3};

			for(j = 0; j < 5; j++){
				input[j] = malloc(max[j] * sizeof(char));
			}

			 strcpy(input[0], result[i].nama);
			 itoa(result[i].umur, input[1], 10);
			 strcpy(input[2], result[i].tanggalLahir);
			 itoa(result[i].status, input[3], 10);
			 itoa(result[i].kamar, input[4], 10);

			 for(j=0; j<5; j++){
				 printf("%s\n", input[j]);
			 }


			clearScreenInput();
			i = bar - 9;
			printxy("Tekan enter untuk menyimpan data", 5,2);
			printxy("tekan atas atau bawah untuk mencari yang diedit",5,3);

			printxy("Nama ", 5, 5); printf("\t\t : %s", input[0]);
			printxy("Umur ", 5, 6); printf("\t\t : %s", input[1]);
			printxy("tanggal Lahir ", 5, 7); printf("\t : %s", input[2]);
			printxy("Status ", 5,8); printf("\t\t : %s", input[3]);
			printxy("Kamar ", 5, 9); printf("\t\t : %s", input[4]);

			bar = 5;
			while(1){
				if(bar > 9){
					bar = 5;
				}else if(bar <5){
					bar = 9;
				}

				gotoxy(27+strlen(input[bar-5]), bar);

				demo = getch();
				if(demo == '\r'){
					// simpan data (buat fungsi)
					break;
				}else if(demo == 27){
					// batal
					break;
				}else if(demo == -32){
					demo = getch();
					if(demo == 80 && bar < 10){
						// kebawah
						bar++;
					}else if(demo == 72 && bar > 4){
						// keatas
						bar--;
					}
				}
				else if(demo == '\b' && strlen(input[bar-5]) > 0){
					input[bar-5][strlen(input[bar-5])-1] = '\0';
					printf("\b \b");
				}else if(strlen(input[bar-5]) < max[bar-5]){
					switch(bar-5){
						case 0:
							if(!((demo <65 || (demo > 90 && demo < 97) || demo > 122) && demo != 32)){
								printf("%c", demo);
								input[bar-5][strlen(input[bar-5])] = demo;
							}
							break;
						case 1:
						case 2:
						case 3:
						case 4:
							if(demo >= 48 && demo <= 57){
								input[bar-5][strlen(input[bar-5])] = demo;
								printf("%c", demo);
							}
							break;
					}
				}
			}

			if(demo == '\r'){

				clearScreenInput();
				printf("\nanda mengubah dari : %s -> %s\n", result[i].nama, input[0]);
				printf("anda mengubah dari : %d -> %s\n", result[i].umur,input[1]);
				printf("anda mengubah dari : %s -> %s\n", result[i].tanggalLahir, input[2]);
				printf("anda mengubah dari : %d -> %s\n", result[i].status, input[3]);
				printf("anda mengubah dari : %d -> %s\n", result[i].kamar, input[4]);

				printf("TEKAN ENTER JIKA ANDA SETUJU!");
				demo = getch();
				if(demo == '\r'){
					
					printf("oi");

					strcpy(result[i].nama, input[0]);
					result[i].umur = atoi(input[1]);
					strcpy(result[i].tanggalLahir, input[2]);
					result[i].status = atoi(input[3]);
					result[i].kamar = atoi(input[4]);
					
					// membuat file temporary
					// bisa dibuat fungsi pengopian data baru

					if((temp = fopen(TEMPFILE,"w+")) == NULL){
  					    printf("DATABASE Tidak bisa diakses!\nMohon periksa perizinan file");
  					    exit(0);
  					}
					
					fseek(temp, 0, SEEK_SET);
					fprintf(temp, "%d#\n", totalData);

					for(j = 0; j < totalData; j++){
						if(j == result[i].nomor-1){
							fprintf(temp, "%d$%s$%d$%s$%d$%d$\n", result[i].nomor, result[i].nama, result[i].umur, result[i].tanggalLahir, result[i].status, result[i].kamar);
						}
						else{
							fprintf(temp, "%d$%s$%d$%s$%d$%d$\n", pasien[j].nomor, pasien[j].nama, pasien[j].umur, pasien[j].tanggalLahir, pasien[j].status, pasien[j].kamar);
						}
					}

					fseek(db, 0, SEEK_SET);
					fseek(temp, 0 , SEEK_SET);
					while((test = fgetc(temp)) != EOF){
						fputc(test, db);
					}
					fclose(temp);
				}
			}
		}
		
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
	fclose(userdb);
    return 0;        
}
