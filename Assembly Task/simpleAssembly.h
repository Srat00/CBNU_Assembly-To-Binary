/*
[simpleAssembly.h]
Assembly Instruction�� Machine Code�� ��ȯ�ϴµ� �ʿ��� �����͸� �����ϴ� ��� 

�������� : 2020-04-02
������������ : 2020-04-02
�ۼ��� : 2020039091 ����� 
*/


//Instruction set Init
struct INST
{
	char op;
	char funct;
	bool format; // R_FORMAT = 0, I_FORMAT = 1
};

INST add, addi, sub, lw, sw;


//Register Number Init
const char t[10] = {8, 9, 10, 11, 12, 13, 14, 15, 24, 25};
const char s[8]  = {16, 17, 18, 19, 20, 21, 22, 23};

//Function Init
void instructionInit(); //Instruction Set Number Init 
