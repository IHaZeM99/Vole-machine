#ifndef A1_T4_VOLE_H
#define A1_T4_VOLE_H

#include <bits/stdc++.h>
using namespace std;

class Register{

private:
    map<string ,string> register1[16];
public:

    string getCell(string address);
    void setCell(string address, string value);
};




class Memory{

private:
    map<string ,string> memory[256];
public:

    string getCell(string address);
    void setCell(string address, string value);
};


class ALU{

public:

    string hexToDecimal(string hexa_num);
    string decimalToHex(string decimal_num);
    bool isValid(string statment);
    void add(string idx1, string idx2, Register &register1);

};

class CU {
public :
    void load1(int idxReg, int intMem, Register &register1, Memory &memory);
    void load2(int idxReg, int val, Register &register1);
    void store(int idxReg, int intMem, Register &register1, Memory &memory);
    void move(int idxReg_1, int idxReg_2, Register &register1);
    void load1(int idxReg, int intMem, Register &register1, int& Pc);
    void halt();
};
class CPU{

private:

    int program_cnt;
    string instruction_register;
    Register register1;
    ALU alu;
    CU cu;

    void fetch(Memory& memory);
    vector<int> decode();
    void execute(Register &new_register, Memory& memory, vector<int> vec);

public:

    void runNextSteo(Memory& memory);
};








class Machine{

private:

    CPU cpu;
    Memory memory;

public:

    void loadProgramFile();

    void outPutState();
};








#endif //A1_T4_VOLE_H
