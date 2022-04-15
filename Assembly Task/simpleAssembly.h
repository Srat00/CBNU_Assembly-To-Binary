/*
[simpleAssembly.h]
Assembly Instruction�� Machine Code�� ��ȯ�ϴµ� �ʿ��� �����͸� �����ϴ� ��� 

�������� : 2022-04-02
������������ : 2022-04-15
�ۼ��� : 2020039091 ����� 
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <sstream>

using namespace std;
using std::string;
using std::vector;

//Instruction set Init
struct INST
{
	string op;
	string funct;
};
INST add, addi, sub, lw, sw;

//Register Number Init
const string t[10] = {"01000", "01001", "01010", "01011", "01100", "01101", "01110", "01111", "11000", "11001"};
const string s[8]  = {"10000", "10001", "10010", "10011", "10100", "10101", "10110", "10111"};
const string shamt = "00000";

//Vector, Array Init
vector<string> instruction; //Instruction Vector
vector<string> machineCode; //Machine Code Vector
vector<string> tempToken; //lw, sw Tokenize Vector
char tempBirany[17];

//Function Init
void instructionInit(); //Instruction Set Number Init 
string registerSelector(string regi); //Resigster Select
void wordTokenizer(string s); //lw, sw Tokenizer 
string constantConverter(string c); //Constant to 16bit binary
