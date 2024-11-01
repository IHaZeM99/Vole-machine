
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
    }
    else if (opcode == "2") { // Opcode 2: Load with immediate value
        cu->load2(reg_pos, operand, new_register);
    }
    else if (opcode == "B") { // Opcode B: Jump to immediate value
        cu->jump1(reg_pos, operand, new_register,program_cnt);
    }
    else {
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


int hexStringToInt(const std::string& hexStr) {
    int intValue;
    std::stringstream ss;
    ss << std::hex << hexStr;
    ss >> intValue;
    return intValue;
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


void CU::jump1(string idxReg, string RX, Register &register1, int &pc) {
    if (register1.getCell(idxReg) == register1.getCell("0")){
        int new_address = hexStringToInt(RX) - pc;
        pc += new_address;
    }
}

void CU::jump2(std::string idxReg, std::string RX, Register &register1, int &pc) {
    if (register1.getCell(idxReg) > register1.getCell("0")){
        int new_address = hexStringToInt(RX) - pc;
        pc += new_address;
    }
}


void CU::halt() {
    //i will do it with GUI
}
bool ALU::isValid(string statment) {
    regex valid ("[0-9A-F]{4}");
    if (regex_match(statment, valid)){
        return true;
    }else return false;
}

string ALU::decimalToHex(string decimal_num){
    int dec_num = stoi(decimal_num);
    if (dec_num < 0)
        dec_num += 256;
    stringstream ss;
    ss << hex << uppercase << setw(2) << setfill('0') << dec_num;
    return ss.str();
}


string ALU::hexToDecimal(string hexa_num) {
    int decValue = 0;
    int length = hexa_num.length();
    decValue = stoi(hexa_num, nullptr, 16);
    if (hexa_num[0] >= '8')
        decValue -= pow(2, length * 4);

    return to_string(decValue);
}

void ALU::add(string idx1, string idx2, Register &register1, string address) {
    string dec1 = hexToDecimal(idx1), dec2 = hexToDecimal(idx2);
    int result = stoi(dec1) + stoi(dec2);
    register1.setCell(address, decimalToHex(to_string(result)));
}
double ALU::floatextract(string hexa){
    stringstream converter;
    char signchar = hexa[0];
    int exponent, sign = (signchar >= '8') ? -1 : 1, leftside;
    double total, rightside = 0.0;
    converter << hex << signchar;
    converter >> exponent;
    exponent -= (signchar >='8') ? 12 : 4;
    string mantissa = X4B[toupper(hexa[1])], right;
    if (exponent > 0){
        leftside = stoi(mantissa.substr(0, exponent), nullptr, 2);
        right = mantissa.substr(exponent);
        for (int i = 0; i < right.size(); ++i) {
            if (right[i] == '1'){
                rightside += pow(2, -(i + 1));
            }
        }
    }else{
        string filling(abs(exponent), '0');
        right = filling + mantissa;
        for (int i = 0; i < right.size(); ++i) {
            if (right[i] == '1'){
                rightside += pow(2, -(i + 1));
            }
        }
    }

    total = sign * (leftside + rightside);
    return total;
}
string  ALU::floattohex(double floating){
    int left = floating;
    string sign = (floating >= 0) ? "0" : "1";
    double right = abs(floating - left);
    string leftside = X3B[(abs(left))], rightside;
    for (int i = 0; i < 4; ++i){
        right *= 2;
        rightside += (right >= 1) ? "1" : "0";
        right -= (right >= 1) ? 1: 0;
    }
    int exponent = 3, radix = 0;
    while(exponent > 0){
        if (leftside[abs(exponent - 3)] == '1'){
            break;
        }else{
            exponent--;
            radix++;
        }
    };
    int counter = 0;
    while(exponent <= 0 && counter < 3){
        if (rightside[counter] == '1'){
            break;
        }else{
            counter++;
            exponent--;
            radix++;
        }
    };
    exponent += (floating == 0.0) ? 3 : 4;
    string expo = X3B[exponent];
    string both = leftside + rightside, mantissa = both.substr(radix, 4);
    string Final_bin = sign + expo + mantissa;
    string Hexa = FourBX[Final_bin.substr(0, 4)] + FourBX[Final_bin.substr(4,4)];
    return Hexa;
}
void ALU::addF(string idx1, string idx2, Register &register1, string address){
    double sum = floatextract(idx1) + floatextract(idx2);
    string sum_hex = floattohex(sum);
    register1.setCell(address, sum_hex);
}
