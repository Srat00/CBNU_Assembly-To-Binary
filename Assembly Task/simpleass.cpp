/*
[simpleass.cpp]
Assembly Instruction�� �ؽ�Ʈ���Ϸ� �Է¹޾� Machine Code�� ��ȯ�ϴ� ���α׷� 

�������� : 2020-04-01
������������ : 2020-04-02
�ۼ��� : 2020039091 ����� 
*/

#include <stdio.h>
#include <String.h>
#include  "simpleAssembly.h"

int main(int argc, char** argv)
{	
	//�μ� 3�� ( format : simpleass [input file] [output file] )
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
		1. ���� �ҷ����� 
		2. ��������Ͽ��� Instruction �и�
		3. �ش� Instruction ���� ��� �и�
		4. ���˿� �°� 2������ ��ȯ
		5. ��ȯ�� 2������ Output�� ���� (while NULL, goto 2 ) 
		6. ����� Output���Ͽ��� 4���ڸ��� �����߰� 
		*/
		instructionInit();

		
		//Text File Close & Stream Close Checker
		if (fclose(inputFile) != 0) { printf("Input file Error"); return 1; }
		else if (fclose(outputFile) != 0) { printf("Output file Error"); return 1; }
	}
	else
	{
		printf("��ȿ���� ���� �μ��Դϴ�. \n\n >> try 'simpleass [input file] [output file]' ");
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
