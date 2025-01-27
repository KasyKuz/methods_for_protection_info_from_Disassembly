#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include "check.cpp"
#include <stdlib.h>
#include <math.h>
#include <stdio.h> // необходим для работы printf
#include <conio.h>
#include <Windows.h>

//extern "C" void __fastcall asm_func(const char* lpText);
#define crc_key  680526887
using namespace std;
FILE* file;
int crc_flag = 1;

void control_crc();
void quickSort(int* numbers, int left, int right)
{
	int pivot; 
	int index; 
	int l_hold = left; 
	int r_hold = right;
	pivot = numbers[left];
	while (left < right) 
	{
		while ((numbers[right] > pivot) && (left < right))
			right--; 
		if (left != right) 
		{
			numbers[left] = numbers[right]; 
			left++; 
		}
		while ((numbers[left] < pivot) && (left < right))
			left++; 
		if (left != right) 
		{
			numbers[right] = numbers[left];
			right--; 
		}
	}
	numbers[left] = pivot; 
	index = left;
	left = l_hold;
	right = r_hold;
	if (left < index) 
		quickSort(numbers, left, index - 1);
	if (right > index)
		quickSort(numbers, index + 1, right);
}
bool isprime(int num)
{
	if ( num==1 || num ==2 || num==3 || (num * num) % 24 == 1 ) return true;
	return false;
}

void do_good_job() {
	file = fopen("job.txt", "r");
	int N;
	fscanf(file, "%d",&N);
	printf("%d\n", N);

	int* arr = new int[N];
	int cur;
	int num_prime=0;
	
	for (int i = 0; i < N; i++) {
		fscanf(file, "%d,", &cur);
		
		if (isprime(cur)) {
			
			arr[num_prime] = cur;
			num_prime++;
		
		}
	}
	
	__asm {
	jz  false_place2  ;
	jnz  false_place2 ;
false_place2:
	call control_crc;
		

	};
	
	//control_crc();

	int p_check = pass_check();
	int p_check2 = second_pass_check();

	if (p_check!= 1 || !crc_flag || p_check2==true) { print_cipher("<-??C;>0ь5?ьC>;:3ь:;ь-//1??"); return; }
	if (polynom != 0xEDB88320 || key_ch != 4) { print_cipher("<-??C;>0ь5?ьC>;:3ь:;ь-//1??"); return; }
	
	quickSort(arr,0, num_prime - 1);

	control_crc();
	if (pass_check() != 1 || !crc_flag) { print_cipher("<-??C;>0ь5?ьC>;:3ь:;ь-//1??ь:;ь5:2;>9-@5;:"); return; }
	if (polynom != 0xEDB88320 || key_ch != 4) { print_cipher("<-??C;>0ь5?ьC>;:3ь:;ь-//1??ь:;ь5:2;>9-@5;:"); return; }
	
	for (int i = 0; i < num_prime; i++) printf("%d ", arr[i]);
	printf("\n");

	int cur_len = 1;
	int max_num=arr[0];
	int max_len = 1;

	for (int i = 1; i < num_prime; i++) {
		if (arr[i] == arr[i - 1]) {
			cur_len++;
		}
		else {
			if (cur_len > max_len) max_num = arr[i - 1];
			max_len = max(max_len,cur_len);
			cur_len = 1;
		}
	}
	printf("lalalalalalala\n");
	__asm {
		xor eax, eax;
		jz false_place3;
	false_place3:
		call control_crc;
	};
	if (pass_check() != 1 || !crc_flag) { print_cipher("<-??C;>0ь5?ьC>;:3ь:;ь-//1??ь:;ь5:2;>9-@5;:"); return; }
	printf("%d %d\n", max_num, max_len);
	fclose(file);
}
void control_crc() {
	if (calculateCRC((BYTE*)pass_check) != crc_key) crc_flag = 0;
}

void print_cipher1(const char* s) {
	for (int i = 0; i < strlen(s); i++) {
		 
		printf("%c", (char)(s[i] - 4 * 7 * 11));
	}
	printf("\n");
}

int main()
{
	//key_ch = rand() % 37;
	//printf("%d\n", ((((0x23CAC3 - 0xAA) | 0x58) & 0x138) | 0x1161) + 0x23B94A);
	//printf("crc of pass_ckeck: %u\n", calculateCRC((BYTE*)pass_check));
	control_crc();
	int pch = pass_check();
	//print_cipher1("password is wrong no access no information");
	//print_cipher1("password is wrong no access");
	//print_cipher1("please enter passowrd for access:");
	//print_cipher1("code is debugging stop it!");
	/* 
	print_cipher1("wrong password");
	print_cipher1("no access");
	print_cipher1("right password");
	print_cipher1("serial number was made");
	*/
	BOOL isDebuggerPresent1 = false;
	if (CheckRemoteDebuggerPresent(GetCurrentProcess(), &isDebuggerPresent1)) {
		if (IsDebuggerPresent() || isDebuggerPresent1 || debug_check()) {
			print_cipher("/;01ь5?ь01.A335:3ь?@;<ь5@э");
			exit(0);
		}
			
	}
	//printf("check password result %d crc %d\n", pch, crc_flag);
	if (pch!=1 || !crc_flag) {
		print_cipher("C>;:3ь<-??C;>0");
		print_cipher(":;ь-//1??");
		return -1;
    }
	
	__asm {
		jmp false_place+1
		false_place:
			__emit(0x68)
		
	};
	do_good_job();
	/* 
	print_cipher(">534@ь<-??C;>0");
	if (polynom == 0xEDB88320 && key_ch == 4) {
		
		do_good_job();
	}
	*/
}

/* 
самоиндентифицирующийся код

дизассембл

*/