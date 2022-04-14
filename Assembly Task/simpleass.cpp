/*
[simpleass.cpp]
Assembly Instruction�� �ؽ�Ʈ���Ϸ� �Է¹޾� Machine Code�� ��ȯ�ϴ� ���α׷� 

�������� : 2020-04-01
������������ : 2020-04-02
�ۼ��� : 2020039091 ����� 
*/

#include  "simpleAssembly.h"

int main(int argc, char** argv)
{	
	//�μ� 3�� ( format : simpleass [input file] [output file] )
	if (argc == 3)
	{

		//Text File Open
		FILE *inputFile = fopen(argv[1], "rt");
		FILE *outputFile = fopen(argv[2], "wt");

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
		//input file tokenize
		char buffer[255];
		char *pStr;
		while (!feof(inputFile))
		{
			//get line
			pStr = fgets(buffer, 255, inputFile);
			//tokenize
			char *tPtr = strtok(pStr, " 	,");
		    while (tPtr != NULL)
		    {
		    	instruction.push_back(tPtr);
		        tPtr = strtok(NULL, " 	,");
		    }
		}

/*
		//debug
		for (int i = 0; i < instruction.size(); i++)
		{
			printf((char *)instruction[i].c_str());
			printf(" ");
		}
*/
		
		//������� ���������� instruction ���Ϳ� ��� instruction�� �и��Ǿ� ���������̴�.
		int index = 0;
		while(index < instruction.size())
		{
			if(instruction[index] == "add")
			{
				machineCode.push_back(add.op);
				machineCode.push_back(registerSelector(instruction[index + 1]));
				machineCode.push_back(registerSelector(instruction[index + 2]));
				machineCode.push_back(registerSelector(instruction[index + 3]));
				machineCode.push_back(shamt);
				machineCode.push_back(add.funct);
				index += 4;
			}
			
			else if(instruction[index] == "addi")
			{
				machineCode.push_back(addi.op);
				machineCode.push_back(registerSelector(instruction[index + 1]));
				machineCode.push_back(registerSelector(instruction[index + 2]));
				//const or address (16 bit) 
				machineCode.push_back(constantConverter(instruction[index + 3]));
				index += 4;
			}
			
			else if(instruction[index] == "sub")
			{
				machineCode.push_back(sub.op);
				machineCode.push_back(registerSelector(instruction[index + 1]));
				machineCode.push_back(registerSelector(instruction[index + 2]));
				machineCode.push_back(registerSelector(instruction[index + 3]));
				machineCode.push_back(shamt);
				machineCode.push_back(sub.funct);
				index += 4;
			}
			
			else if(instruction[index] == "lw")
			{
				machineCode.push_back(lw.op);
				machineCode.push_back(registerSelector(instruction[index + 1]));
				wordTokenizer(instruction[index + 2]);
				machineCode.push_back(registerSelector(tempToken[1]));
				//printf((char *)tempToken[1].c_str());
				//const or address (16 bit), tempToken[0];
				machineCode.push_back(constantConverter(tempToken[0]));
				index += 3;
			}
			
			else if(instruction[index] == "sw")
			{
				machineCode.push_back(sw.op);
				machineCode.push_back(registerSelector(instruction[index + 1]));
				wordTokenizer(instruction[index + 2]);
				machineCode.push_back(registerSelector(tempToken[1]));
				//const or address (16 bit), tempToken[0];
				machineCode.push_back(constantConverter(tempToken[0]));
				index += 3;
			}
		}
		
		//��ȯ�� ��� ��ִ´�. 
		for(int i = 0; i < machineCode.size(); i++)
		{
			fputs((char *)machineCode[i].c_str(), outputFile);
		} 
		
		//Text File Close & Stream Close Checker
		if (fclose(inputFile) != 0) { printf("Input file Error"); return 1; }
		else if (fclose(outputFile) != 0) { printf("Output file Error"); return 1; }
		
		printf("Task Complete.");
		return 1;
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
	add.op = "000000";
	add.funct = "100000";
	
	addi.op = "100000";
	addi.funct = "000000";
	
	sub.op = "000000";
	sub.funct = "010000";
	
	lw.op = "000001";
	lw.funct = "000000";
	
	sw.op = "000010";
	sw.funct = "000000";
}

string registerSelector(string regi)
{
	int index = 0;
	if(regi.at(1) == 't')
	{
		index = regi.at(2) - '0'; 
		return t[index];
	}	
	else if(regi.at(1) == 's')
	{
		index = regi.at(2) - '0';
		return s[index];
	}
}

void wordTokenizer(string s)
{
	char *tPtr = strtok((char *)s.c_str(), "()");
	while (tPtr != NULL)
	{
		tempToken.push_back(tPtr);
	    tPtr = strtok(NULL, "()");
	}
}

string constantConverter(string c)
{
	char binary[17] = "0000000000000000";
	int temp[16];
	
	int binaryIndex;
	int arrayIndex = 16;
	int binaryInt = atoi((char *)c.c_str());
	
	for(int i = 0; i < 16; i++)
	{
		temp[i] = binaryInt % 2;
    	binaryInt /= 2;
    }
    for(int i = arrayIndex; i >= 0; i--)
    {
    	binary[i - 1] = temp[16 - i] + '0';
	}
	
	string temp_s = binary;
	
	return temp_s;
}
