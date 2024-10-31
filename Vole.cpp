//
// Created by Hazem Ahmed on 10/25/2024.
//
#include "Vole.h"
Machine::Machine() {

    cpu = new CPU();
    memory = new Memory();

}

Machine::~Machine(){
    delete cpu;
    delete memory;
}
void Machine::loadProgramFile(const string& file_path) {


    ifstream file(file_path);

    if (!file) {
        wcerr << "Error: Unable to open the file for reading: " << file_path.c_str() << endl;
    }

    string line;

    while (file >> line) {

        instructions.push_back(line);
    }

    file.close();

}

void Machine::outPutState() {

    memory->printMemory();
    cout << "\n\n";
    cpu->printRegister();



}

void Machine::sendInstructionsToMemory() {
    memory->takeValuesFromFileAndAssignIt(instructions);
}

void Machine::sendInstructionsToCPU() {

    cpu->runNextStep(*memory);
}


void Memory::setCell(const string &address,const string &value) {

    memory[address] = value;
}

string Memory::getCell(const string& address) {

    return memory[address];
}

void Memory::takeValuesFromFileAndAssignIt(vector<string> &instructions) {

    string address1,address2, value1, value2;
    int start = 0;
    for (size_t i = 0; i < instructions.size(); ++i) {
        address1 = intToHex(start);
        start++;
        address2 = intToHex(start);
        start++;
        value1 = instructions[i].substr(0, 2); // First 2 characters
        value2 = instructions[i].substr(2, 2); // Next 2 characters
        setCell(address1,value1);
        setCell(address2,value2);
    }

}

string Memory::intToHex(int num) {
    stringstream ss;
    ss << uppercase << setw(2) << setfill('0') << hex << num;
    return ss.str();

}

Memory::Memory() {

    for (int i = 0; i <= 255; i++) {
        string hexAddress = intToHex(i);
        memory[hexAddress] = "00";
    }
}

void Memory::printMemory(){

    cout<< "Address" << "     " << "Value\n\n";
    for (auto &item: memory) {
        cout << item.first << "          " << item.second << '\n';
    }
}

string Register::getHexadecimalRange(int num) {

    stringstream ss;

    ss << hex << uppercase << num;

    return ss.str();
}

Register::Register() {

    for (int i = 0; i <= 15; i++) {
        string hexAddress = getHexadecimalRange(i);
        register1[hexAddress] = "00";
    }
}

void Register::setCell(const string &address,const  string &value) {

    register1[address] = value;
}

string Register::getCell(const string &address) {

    return register1[address];
}

void Register::printRegister(){

    cout<< "Register" << "     " << "Value\n\n";
    for (auto &item: register1) {
        cout << item.first << "          " << item.second << '\n';
    }

}



CPU::CPU():program_cnt(0){

    register1 = new Register();
    cu = new CU();
    alu = new ALU();
}
CPU::~CPU(){

    delete register1;
    delete cu;
    delete alu;
}


void CU::load1(const string &register_position,const string& address,Register &register1, Memory &memory){

    register1.setCell(register_position,memory.getCell(address)) ;
}

void CU::load2(const string &register_position,const string& value,Register &register1){

    register1.setCell(register_position,value) ;
}



string CPU::fetch(Memory& memory) {
    instruction_register = "";
    string part1_memory = Memory::intToHex(program_cnt++);
    string part2_memory = Memory::intToHex(program_cnt++);
    instruction_register += memory.getCell(part1_memory);
    instruction_register += memory.getCell(part2_memory);
    return instruction_register;
}


vector<string> CPU::decode(string& instruction) {
    vector<string> decoded;
    decoded.push_back(string(1, instruction[0]));         // Opcode as string
    decoded.push_back(string(1, instruction[1]));         // Register position as string
    decoded.push_back(instruction.substr(2, 2));          // Operand as string
    return decoded;
}


void CPU::execute(Register &new_register, Memory &memory, vector<string> &decoded) {
    string opcode = decoded[0];
    string reg_pos = decoded[1];
    string operand = decoded[2];

    if (opcode == "1") {        // Opcode 1: Load from memory
        cu->load1(reg_pos, operand, new_register, memory);
    } else if (opcode == "2") { // Opcode 2: Load with immediate value
        cu->load2(reg_pos, operand, new_register);
    } else {
        // Add cases for other opcodes (e.g., store, move, jump, halt)
    }
}


void CPU::runNextStep(Memory &memory) {
    while (true) {
        string instruction = fetch(memory);           // Fetch next instruction
        if (instruction.empty() || instruction[0] == '0') break; // Halt on empty or specific opcode

        vector<string> decoded = decode(instruction); // Decode instruction
        execute(*register1, memory, decoded);         // Execute based on decoded data
    }
}



void CPU::printRegister(){

    register1->printRegister();
}

void CPU::setpc(const std::string &address) {
    //program_cnt = address;                                  
}

void CU::store(string idxReg, string strMem, Register &register1, Memory &memory) {
    string reg_data = register1.getCell(idxReg);
    memory.setCell(strMem,reg_data);
    if (strMem == "00"){                                                            // if store on that form R00"print to screen"
        cout << reg_data << endl;
    }
}

void CU::move(string idxReg_1, string idxReg_2, Register &register1) {
    string reg_data = register1.getCell(idxReg_1);
    register1.setCell(idxReg_2,reg_data);
}

void CPU::jump(string idxReg, string RX, Register &register1, CPU &pc) {
    if (register1.getCell(idxReg) == register1.getCell("0")){
        pc.setpc(RX);                                                             //Didn't test it yet
    }
}

void CU::halt() {
                                                                                            //i will do it with GUI
}
