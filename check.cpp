
#define _CRT_SECURE_NO_WARNINGS
#define _UNICODE
#define UNICODE
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>
#include <tchar.h> 

#define polynom 0xEDB88320
#define true_password ((((0x23CAC3 - 0xAA) | 0x58) & 0x138) | 0x1161) + 0x23B94A //2345667 - obfuscation???
#define check_str "glhebjfnk;sld,;xkkjklhbkvgfcxd"
using namespace std;

FILE* password_file;
FILE* serial_file;
int serial_num = 0;
int key_ch = 4;
int crc_n = 0;
bool Check_Tick();
bool debug_check();

void generated_key() {
	serial_file = fopen("serial.txt", "a");
	char key[15];
	key[0] = 'K';
	key[1] = 'E';
	key[2] = 'Y';
	key[3] = '$';
	fprintf(serial_file, "KEY$");
	for (int i = 4; i < 14; i++) {
		key[i] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890"[rand() % 36];
		//printf("%c", key[i]);
		fprintf(serial_file, "%c", key[i]);
	}
	key[14] = '$';
	printf("\n");
	fprintf(serial_file, "$\n");
	//fprintf(serial_file, "%s\n", generated_key());
	fclose(serial_file);
	return;
}
uint32_t calculateCRC(BYTE* ptr) {
	uint32_t crc = 0xFFFFFFFF;
	size_t i = 0;
	while (ptr[i]) {
		crc ^= ptr[i];
		for (size_t j = 0; j < 8; j++) {
			if (crc & 1) {
				crc = (crc >> 1) ^ polynom;
			}
			else {
				crc >>= 1;
			}
		}
		i++;
	}
	return ~crc;
}


void print_cipher(const char* s) {

	for (int i = 0; i < strlen(s); i++) {
		
		if (s[i] + key_ch * 7 * 11 == 304) printf(" ");
		else printf("%c", (char)(s[i] + key_ch * 7 * 11));
	}
	printf("\n");
}

int pass_check() {
	password_file = fopen("password.txt", "r");
	int cur_password;
	fscanf(password_file, "%d", &cur_password);
	
	fclose(password_file);
	if (true_password == cur_password && !debug_check()) {
		
		//if (Check_Tick() == false) return 0;
		
		if (crc_n == 0) { print_cipher("?1>5-8ü:A9.1>üC-?ü9-01"); generated_key(); crc_n++; }
		
		return 1;
	}
	return 0;
}

bool second_pass_check() {
	std::string pass2;
	print_cipher("<81-?1ü1:@1>ü<-??;C>0ü2;>ü-//1??");
    //scanf_s("%s", &pass2);   ///////encode later
	std::cin >> pass2;
	std::string compare_pass = { "somepassforcompare" };
	if (compare_pass.compare(pass2)==0) {
		return false;
	}
	else {
		return false;
	}

	return true;
}

#define SERIAL_THRESHOLD 0x10000 // 10,000h ticks


bool Check_Tick()

{
	TCHAR pName[] = TEXT(check_str);
	DWORD LocalSerial = 0;
	size_t strlen = _tcslen(pName);

	DWORD Counter = GetTickCount(); // Could be replaced with timeGetTime()

	// Generate serial 
	for (unsigned int i = 0; i < strlen; i++)
	{
		LocalSerial += (DWORD)pName[i];
		LocalSerial ^= 0xDEADBEEF;
	}

	Counter = GetTickCount() - Counter; // Could be replaced with timeGetTime() 
	if (Counter >= SERIAL_THRESHOLD) return false;

	return true;
}
bool debug_check() {
	HANDLE hOlly = FindWindow(TEXT("OLLYDBG"), NULL);
	HANDLE hWinDbg = FindWindow(TEXT("WinDbgFrameClass"), NULL);
	if (hOlly || hWinDbg) return true;
	return false;
}

void multiply_x(int* x, int multiplier)
{
	*x *= multiplier;
}

void add_to_x(int* x, int increment)
{
	*x += increment;
}
void selfcode() {
	int x = 0;
	int i;

	void (*fp)(int*, int);

	for (i = 1; i < 6; ++i) {
		fp = (i % 2) ? add_to_x : multiply_x;

		fp(&x, i);

		printf("%d\n", x);
	}
}
//vertual machines
bool Registry() {
	HKEY rKey;
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Enum\\PCI\\VEN_15AD & DEV_0405 & SUBSYS_040515AD & REV_00", 0,KEY_QUERY_VALUE, &rKey) == ERROR_SUCCESS) {
		RegCloseKey(rKey);
		return true;
	}
	return false;
}