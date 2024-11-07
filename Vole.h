#ifndef A1_T4_VOLE_H
#define A1_T4_VOLE_H

#include <bits/stdc++.h>
#include <QMessageBox>
#include <QCoreApplication>
#include "ui_mainwindow.h"
#include <QDebug>



using namespace std;



class Register{

private:
    map<string ,string> register1;

public:
    string getHexadecimalRange(int num);
    Register();
    string getCell(const string &address);
    void setCell(const string &address,const  string &value);
    void printRegister();
    string hexatoBinary(const string &hexa);
    void clearRegister();
};




class Memory{

private:
    map<string ,string> memory;
    int start = 10;
public:

    static string intToHex(int num) ;
    Memory();
    string getCell(const string &address);
    void setCell(const string &address,const string &value);
    void takeValuesFromFileAndAssignIt(vector<string>& instructions,string pc);
    void takeValuesOneByOneAndAssignIt(string &instruction);
    void setStart(string PC);
    void printMemory();
    string hexatoBinary(const string &hexa);
    void clearMemory();


};



class ALU{
private:

    unordered_map<char, string> X4B = {
        {'0', "0000"}, {'1', "0001"}, {'2', "0010"}, {'3', "0011"},
        {'4', "0100"}, {'5', "0101"}, {'6', "0110"}, {'7', "0111"},
        {'8', "1000"}, {'9', "1001"}, {'A', "1010"}, {'B', "1011"},
        {'C', "1100"}, {'D', "1101"}, {'E', "1110"}, {'F', "1111"}
    };
    unordered_map<string, string> FourBX = {
        {"0000", "0"}, {"0001", "1"}, {"0010", "2"}, {"0011", "3"},
        {"0100", "4"}, {"0101", "5"}, {"0110", "6"}, {"0111", "7"},
        {"1000", "8"}, {"1001", "9"}, {"1010", "A"}, {"1011", "B"},
        {"1100", "C"}, {"1101", "D"}, {"1110", "E"}, {"1111", "F"}
    };
    unordered_map<int, string> X3B = {
        {0, "000"}, {1, "001"}, {2, "010"}, {3, "011"},
        {4, "100"}, {5, "101"}, {6, "110"}, {7, "111"},
        };
    string floattohex(double floating);

    string hexAnd(const string &hex1, const string &hex2);

public:

    string hexToDecimal(string hexa_num);
    string decimalToHex(string decimal_num);
    bool isValid(string statment);
    void add(string idx1, string idx2, Register &register1, string address);
    void addF(string idx1, string idx2, Register &register1, string address);
    void andOperator(const string &register_position1, const string &register_position2, const string &register_store_position, Register &register1);
    string XOR(string hexa1, string hexa2);
    string OR(string hexa1, string hexa2);
    double floatextract(string hexa);
};

class CU{
private:

    int rightCyclicRotate(int value, int steps, int register_size);
    friend string Memory::intToHex(int num);

public :
    void load1(const string &register_position,const string &address,Register &register1, Memory &memory);
    void load2(const string &register_position,const string& value,Register &register1);
    void store(string idxReg, string strMem, Register &register1, Memory &memory);
    void move(string idxReg_1, string idxReg_2, Register &register1);
    void jump(string idxReg, string RX, Register &register1, int &pc);
    void jump2(string idxReg, string RX, Register &register1, int &pc);
    void rotate(const string &register_position,const string& num_of_steps, Register &register1);
    void halt();
};

class CPU{

private:

    bool END;
    int program_cnt;
    string instruction_register;
    Register* register1;
    ALU* alu;
    CU* cu;
    friend string Memory::intToHex(int num);
    string fetch(Memory& memory);
    vector<string> decode(string& instruction);
    void execute(Register& new_register, Memory& memory, vector<string>& decoded);



public:

    CPU();
    ~CPU();
    void runNextStep(Memory& memory);
    void runTillHalt(Memory& memory,Ui::MainWindow* ui);
    void setPC(const string &address);
    bool getend();
    void setend();
    string getPC();
    void printRegister();
    Register* getreg();
    CU* getcu();
    ALU* getAlu();
    bool verifyInputs(const string& instruction);
    int hexStringToInt(string hexStr);
    void display_screen(Ui::MainWindow* ui);
    void clear_screen();
    void fetch_from_user(string fetch);
};

class Machine{

private:

    CPU* cpu{};
    Memory* memory{};
    vector<string> instructions;
    //Ui::MainWindow* ui;
    string starting_address;

public:

    Machine();
    ~Machine();
    bool verifyInputs(const string& instruction);
    void loadProgramFile(const string& file_path);
    void loadProgramNormalWay(string& instruction);
    void setPC(string address);
    void sendInstructionsToMemory();
    void sendInstructionsToCPU();
    void outPutState();
    CPU* getcpu();
    Memory* getmem();
    void runTillHalt(Ui::MainWindow* ui);
    void runNextStep();
    void clearInstructions();
    void resetExecutionState();
};








#endif //A1_T4_VOLE_H
