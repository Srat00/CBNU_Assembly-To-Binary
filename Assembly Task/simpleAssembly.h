/*
[simpleAssembly.h]
Assembly Instruction을 Machine Code로 변환하는데 필요한 데이터를 제공하는 헤더 

생성일자 : 2020-04-02
최종수정일자 : 2020-04-02
작성자 : 2020039091 어록희 
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
