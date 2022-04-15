/*
[simpleass.cpp]
Assembly Instruction을 텍스트파일로 입력받아 Machine Code로 변환하는 프로그램 

생성일자 : 2022-04-01
최종수정일자 : 2022-04-15
작성자 : 2020039091 어록희 
*/

#include  "simpleAssembly.h"

int main(int argc, char** argv)
{	
	/*
	Instruction
	1. 파일 불러오기 
	2. 어셈블리파일에서 Instruction 분리
	3. 해당 Instruction 에서 요소 분리
	4. 포맷에 맞게 2진수로 변환
	5. 변환한 2진수를 Temp.txt에 저장 (while NULL, goto 2 ) 
	6. 저장된 Output파일에서 4글자마다 공백추가 
	7. Temp.txt 삭제 
	*/
		
	//인수 3개 ( format : simpleass [input file] [output file] )
	if (argc == 3)
	{
		//Text File Open
		FILE *inputFile = fopen(argv[1], "rt");
		FILE *tempFile = fopen("temp.txt", "wt");

		//Stream Open Checker
		if (inputFile == NULL) { printf("Input file Error"); return 1; }
		else if (tempFile == NULL) { printf("Output file Error");	return 1; }
		
		//Instruction Set Initialize
		instructionInit();
		
		//Input file Tokenize
		char buffer[255];
		char *pStr;
		while (!feof(inputFile))
		{
			//Get Line
			pStr = fgets(buffer, 255, inputFile);
			//Tokenize
			char *tPtr = strtok(pStr, " ,\n\t");
			//Save to Instruction Vector
		    while (tPtr != NULL)
		    {
		    	instruction.push_back(tPtr);
		        tPtr = strtok(NULL, " ,\n\t");
		    }
		}
				
		//여기까지 진행했으면 instruction 벡터에 모든 instruction이 분리되어 들어가있을 것이다.
		
		//Instruction to Binary
		int index = 0;
		while(index < instruction.size())
		{
			if(instruction[index] == "add")
			{
				machineCode.push_back(add.op);
				machineCode.push_back(registerSelector(instruction[index + 1])); //rs
				machineCode.push_back(registerSelector(instruction[index + 2])); //rt
				machineCode.push_back(registerSelector(instruction[index + 3])); //rd
				machineCode.push_back(shamt);
				machineCode.push_back(add.funct);
				index += 4;
			}
			
			else if(instruction[index] == "addi")
			{
				machineCode.push_back(addi.op);
				machineCode.push_back(registerSelector(instruction[index + 1])); //rs
				machineCode.push_back(registerSelector(instruction[index + 2])); //rt
				machineCode.push_back(constantConverter(instruction[index + 3])); //const or address (16 bit) 
				index += 4;
			}
			
			else if(instruction[index] == "sub")
			{
				machineCode.push_back(sub.op);
				machineCode.push_back(registerSelector(instruction[index + 1])); //rs
				machineCode.push_back(registerSelector(instruction[index + 2])); //rt
				machineCode.push_back(registerSelector(instruction[index + 3])); //rd
				machineCode.push_back(shamt);
				machineCode.push_back(sub.funct);
				index += 4;
			}
			
			else if(instruction[index] == "lw")
			{
				machineCode.push_back(lw.op);
				machineCode.push_back(registerSelector(instruction[index + 1])); //rs
				wordTokenizer(instruction[index + 2]); //$reg(const) format Tokenize
				machineCode.push_back(registerSelector(tempToken[1])); //rt
				machineCode.push_back(constantConverter(tempToken[0])); //const or address 
				index += 3;
				tempToken.clear(); 
			}
			
			else if(instruction[index] == "sw")
			{
				machineCode.push_back(sw.op);
				machineCode.push_back(registerSelector(instruction[index + 1])); //rs
				wordTokenizer(instruction[index + 2]); //$reg(const) format Tokenize
				machineCode.push_back(registerSelector(tempToken[1])); //rt
				machineCode.push_back(constantConverter(tempToken[0])); //const or address
				index += 3;
				tempToken.clear();
			}
		}
		
		//Binary File Write
		for(int i = 0; i < machineCode.size(); i++) fputs((char *)machineCode[i].c_str(), tempFile);

		//여기까지 진행했다면 temp.txt 파일에 변환된 Machine Code가 들어있을 것이다. 
		
		//Text File Close & Stream Close Checker
		if (fclose(inputFile) != 0) { printf("Input file Error"); return 1; }
		else if (fclose(tempFile) != 0) { printf("Temp file Error"); return 1; }
		
		//Output Postprocess
		FILE *tempFileProcess = fopen("temp.txt", "r+");
		FILE *outputFile = fopen(argv[2], "wt");
		
		//File Size Checker
		fseek(tempFileProcess, 0, SEEK_END);
    	int outSize = ftell(tempFileProcess); //File Size Check 
    	fseek(tempFileProcess, 0, SEEK_SET); //Cursor to Start 
    	
    	//Output Vector Set
    	vector<char> outputStream;
    	while(!feof(tempFileProcess))
    	{
    		char temp = fgetc(tempFileProcess); //Read char
        	outputStream.push_back(temp);
		}
				
		//File Re-Arrange 
		int outVectorSize = outputStream.size();
		for(int i = 0; i < outVectorSize - 1; i++)
		{
			if(i == 4) fputc(' ', outputFile); //Add Blank  
			if(i % 4 == 0 && i != 0 && i != 4) fputc(' ', outputFile); //Add Blank  
			if(i % 32 == 0 && i != 0) fputc('\n', outputFile); //Add Line Break
			
			fputc(outputStream[i], outputFile);
		}
    	
		//Text File Close & Stream Close Checker
		if (fclose(tempFileProcess) != 0) { printf("Temp file Error"); return 1; }
		if (fclose(outputFile) != 0) { printf("Output file Error"); return 1; }
		
		//Temp File Remove
		remove("temp.txt"); 
		
		//Task Complete! 
		printf("Task Complete.");
		return 1;
	}
	//Parameter Exception Checker
	else
	{
		printf("유효하지 않은 인수입니다. \n\n >> try 'simpleass [input file] [output file]' ");
		return -1;
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
	if(regi.at(1) == 't') //Temporary Register
	{
		index = regi.at(2) - '0'; //char to int Converter
		return t[index];
	}	
	else if(regi.at(1) == 's') //Saved Register
	{
		index = regi.at(2) - '0'; //char to int Converter
		return s[index];  
	}
}

void wordTokenizer(string s)
{
	char *tPtr = strtok((char *)s.c_str(), "()"); //Tokenize into Parenthesis
	while (tPtr != NULL)
	{
		tempToken.push_back(tPtr);
	    tPtr = strtok(NULL, "()");
	}
}

string constantConverter(string c)
{
	char binary[17] = "0000000000000000"; //16bit Binary Init 
	int temp[16];
	
	int binaryIndex;
	int arrayIndex = 16;
	int binaryInt = atoi((char *)c.c_str()); 
	
	//Decimal to Binary, Positive 
	if(binaryInt >= 0)
	{
		for(int i = 0; i < 16; i++)
		{
			temp[i] = binaryInt % 2;
	    	binaryInt /= 2;
	    }
	    for(int i = arrayIndex; i >= 0; i--)
	    {
	    	binary[i - 1] = temp[16 - i] + '0';
		}
	}
	//Decimal to Binary, Negative
	else if(binaryInt < 0)
	{
		int absolute = -binaryInt-1;
		for(int i = 0; i < 16; i++)
		{
			temp[i] = absolute % 2;
	    	absolute /= 2;
	    }
	    for(int i = arrayIndex; i >= 0; i--)
	    {
	    	if (temp[16 - i] == 0) binary[i - 1] = '1';
	    	if (temp[16 - i] == 1) binary[i - 1] = '0';
		}
	}
	
	string temp_s = binary;
	return temp_s;
}
