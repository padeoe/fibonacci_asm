// NASM.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include <stdio.h>
#include "stdafx.h"
#include <Windows.h>
int fibonacci(int n);
void print_fibonacci(int n);

int a = 1, b = 2, c = 3;
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
char* format_int = "%d";
char* format_string = "%s";
char* tip_output = "쳲����������ǣ�";
char *tip = "\n����������n\n";
char *space = " ";
char *newline = "\n";
int input_n = 0;

int _tmain(int argc, _TCHAR* argv[])
{
	print_fibonacci(10);

	__asm
	{
input:		//��ʾ�û�����
		push tip
		call printf
		//��ȡ�û����뵽input��
		lea eax, [input_n]
			push eax
			push format_int
			call scanf_s
		
			//����û�������
			push tip_output
			push format_string
			call printf

/*			push input_n
			push format_int
			call printf*/
			//���쳲���������
			mov ecx, 1//i
nextF:
		    mov edx, input_n//int n=input_n;
			sub edx, ecx//n-i
			add edx, 1//n-i+1
			test edx,edx
			JE input//if(n-i+1==0) return;
			mov ebx,ecx

			mov eax, ecx
			and al, 01h
			cmp al, 0
			jne green
			je red

green:	push FOREGROUND_GREEN
			push h
			call SetConsoleTextAttribute
			jmp contin
red:
			push FOREGROUND_RED
			push h
			call SetConsoleTextAttribute
			jmp contin

contin:	
			//�����ǰ��ѭ������
			jmp fibonacci2
			push ebx
			push format_string
			call printf
printfi:	
			//�������õ��ĺ���ֵ	
			//������ո�
			push space
				call printf

			push esi
			push format_int
			call printf
			//׼������ѭ��
			add ebx,1//else i++;
			mov ecx,ebx
			jmp nextF


		   //ebp,esp,edi,esi
fibonacci2:
//			jmp return_one
//		    mov esi,ebx//�����ã�ֱ�ӷ��ز���
			mov ebp,ebx
			sub ebp,1
			test ebp,ebp
			je return_one
			jne judge_continue
judge_continue:
			mov ebp, ebx
			sub ebp, 2
			test ebp,ebp
			je return_one
			jne calculate
calculate:
			mov eax,1//int a=1
			mov ecx,1//int b=1
			mov edx,0//int c=0
			mov ebp,ebx//����n
			mov edi,2//int i=2
judge_edi:			sub ebp,edi//n-i
			test ebp,ebp
			mov ebp,ebx
			je return_result//if(n-i==0)
			jne moveforward
moveforward:
			mov edx,ecx
			add ecx,eax
			mov eax,edx
			mov edx,ecx
			add edi,1//i++
			jmp judge_edi
return_result:
			mov esi, edx
			jmp printfi
/**			mov ebp, 2
			mov esi, ebx
			jmp printfi**/

return_one:
			mov esi,1
			jmp printfi

	}
	return 0;
}

//C���Ե�쳲���������
/*���ص�n�����ֵ*/
/*int fibonacci(int n){
	int result = 0;
	if (n==2||n==1)
		return n;
	else
		return fibonacci(n - 1) + fibonacci(n - 2);
}*/
int fibonacci(int n){
	int a=1, b=1, c = 0;
	if (n == 2 || n == 1)
		return 1;
	else{
		for (int i = 2; i != n; i++){
			c = a + b;
			a = b;
			b = c;
		}
		return c;
	}

}


void print_fibonacci(int n){
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 1; n - i + 1 != 0; i++){
		if (i % 2 == 0){
			SetConsoleTextAttribute(h,FOREGROUND_GREEN);
			printf("%d\n", fibonacci(i));
		}
		else{
			SetConsoleTextAttribute(h, FOREGROUND_RED);
			printf("%d\n", fibonacci(i));
		}
	}
}