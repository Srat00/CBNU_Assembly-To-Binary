/*
[simpleass.cpp]
Assembly Instruction을 텍스트파일로 입력받아 Machine Code로 변환하는 프로그램 

생성일자 : 2020-04-01
최종수정일자 : 2020-04-02
작성자 : 2020039091 어록희 
*/

#include  "simpleAssembly.h"

int main(int argc, char** argv)
{	
	//인수 3개 ( format : simpleass [input file] [output file] )
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
		1. 파일 불러오기 
		2. 어셈블리파일에서 Instruction 분리
		3. 해당 Instruction 에서 요소 분리
		4. 포맷에 맞게 2진수로 변환
		5. 변환한 2진수를 Output에 저장 (while NULL, goto 2 ) 
		6. 저장된 Output파일에서 4글자마다 공백추가 
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
		
		//여기까지 진행했으면 instruction 벡터에 모든 instruction이 분리되어 들어가있을것이다.
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
		
		//변환된 기계어를 써넣는다. 
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
		printf("유효하지 않은 인수입니다. \n\n >> try 'simpleass [input file] [output file]' ");
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
