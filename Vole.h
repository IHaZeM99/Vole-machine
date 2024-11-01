#ifndef A1_T4_VOLE_H
#define A1_T4_VOLE_H

#include <bits/stdc++.h>
using namespace std;

class Register{

private:
    map<string ,string> register1;
    string getHexadecimalRange(int num);
public:

    Register();
    string getCell(const string &address);
    void setCell(const string &address,const  string &value);
    void printRegister();
};




class Memory{

private:
    map<string ,string> memory;
public:

    static string intToHex(int num) ;
    Memory();
    string getCell(const string &address);
    void setCell(const string &address,const string &value);
    void takeValuesFromFileAndAssignIt(vector<string>& instructions);
    void printMemory();

};



class ALU{

public:

    string hexToDecimal(string hexa_num);
    string decimalToHex(string decimal_num);
    bool isValid(string statment);
    void add(string idx1, string idx2, Register &register1);

};

class CU{
public :
    void load1(const string &register_position,const string &address,Register &register1, Memory &memory);
    void load2(const string &register_position,const string& value,Register &register1);
    void store(string idxReg, string strMem, Register &register1, Memory &memory);
    void move(string idxReg_1, string idxReg_2, Register &register1);
    void jump1(string idxReg, string RX, Register &register1, int &pc);
    void jump2(string idxReg, string RX, Register &register1, int &pc);   //bonus
    void halt();
};

class CPU{

private:

    int program_cnt;
    string instruction_register;
    Register* register1;
    ALU* alu;
    CU* cu;
    friend string Memory::intToHex(int num);
    string fetch(Memory& memory);
    vector<string> decode(string& instruction);
    void execute(Register& new_register, Memory& memory, vector<string>& decoded);
    int hexStringToInt(const std::string& hexStr);

public:

    CPU();
    ~CPU();
    void runNextStep(Memory& memory);
    //void jump(string idxReg, string RX, Register &register1, CPU &cpu1);
    void setpc(const string &address);
    void printRegister();

};

class Machine{

private:

    CPU* cpu{};
    Memory* memory{};
    vector<string> instructions;

public:

    Machine();
    ~Machine();
    bool verifyInputs();
    void loadProgramFile(const string& file_path);
    void sendInstructionsToMemory();
    void sendInstructionsToCPU();
    void outPutState();
};








#endif //A1_T4_VOLE_H
