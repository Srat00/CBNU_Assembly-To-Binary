/*
[simpleass.cpp]
Assembly Instruction을 텍스트파일로 입력받아 Machine Code로 변환하는 프로그램 

생성일자 : 2020-04-01
최종수정일자 : 2020-04-02
작성자 : 2020039091 어록희 
*/

#include <stdio.h>
#include <String.h>
#include  "simpleAssembly.h"

int main(int argc, char** argv)
{	
	//인수 3개 ( format : simpleass [input file] [output file] )
	if (argc == 3)
	{
		//Text File Open
		FILE* inputFile = fopen(argv[1], "rt");
		FILE* outputFile = fopen(argv[2], "wt");

		//Stream Open Checker
		if (inputFile == NULL) { printf("Input file Error"); return 1; }
		else if (outputFile == NULL) { printf("Output file Error");	return 1; }
		
		/*
		TODO 
		1. 파일 불러오기 
		2. 어셈블리파일에서 Instruction 분리
		3. 해당 Instruction 에서 요소 분리
		4. 포맷에 맞게 2진수로 변환
		5. 변환한 2진수를 Output에 저장 (while NULL, goto 2 ) 
		6. 저장된 Output파일에서 4글자마다 공백추가 
		*/
		instructionInit();

		
		//Text File Close & Stream Close Checker
		if (fclose(inputFile) != 0) { printf("Input file Error"); return 1; }
		else if (fclose(outputFile) != 0) { printf("Output file Error"); return 1; }
	}
	else
	{
		printf("유효하지 않은 인수입니다. \n\n >> try 'simpleass [input file] [output file]' ");
		return 1;
	}
	return 0;
}

void instructionInit()
{
	add.op = 0;
	add.funct = 32;
	add.format = 0;
	
	addi.op = 32;
	addi.funct = 0;
	addi.format = 1;
	
	sub.op = 0;
	sub.funct = 16;
	sub.format = 0;
	
	lw.op = 1;
	lw.funct = 0;
	lw.format = 1;
	
	sw.op = 2;
	sw.funct = 0;
	sw.format = 1;
}
