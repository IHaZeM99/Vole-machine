
#include "Vole.h"

std::vector<std::string> SCR_Vect ;
std::string LASTHEX = "";
//###################################################//
//################### Machine #######################//
//###################################################//


Machine::Machine() {

    cpu = new CPU();
    memory = new Memory();
    //Ui::MainWindow* ui = new Ui::MainWindow ui;

}

Machine::~Machine(){
    delete cpu;
    delete memory;
}
void Machine::loadProgramFile(const string& file_path) {


    ifstream file(file_path);

    if (!file) {
        wcerr << "Error: Unable to open the file for reading: " << file_path.c_str() << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        istringstream stream(line);
        string instruction;
        bool valid_line = true;
        size_t initial_size = instructions.size();

        while (stream >> instruction) {
            if (verifyInputs(instruction)) {
                instructions.push_back(instruction);
            } else {
                valid_line = false;
                break;
            }
        }

        if (!valid_line) {
            instructions.erase(instructions.begin() + initial_size, instructions.end());
        }
    }

    file.close();

}

void Machine::loadProgramNormalWay(string &instruction) {

    memory->takeValuesOneByOneAndAssignIt(instruction);
}

void Machine::outPutState() {

    memory->printMemory();
    cout << "\n\n";
    cpu->printRegister();



}

void Machine::sendInstructionsToMemory() {
    memory->takeValuesFromFileAndAssignIt(instructions,starting_address);
}

// void Machine::sendInstructionsToCPU() {

//     cpu->runNextStep(*memory);
//     cpu->runTillHalt(*memory);
// }

void Machine::setPC( std::string address = "0A") {

    cpu->setPC(address);
    memory->setStart(address);
    starting_address = address;
}

bool Machine::verifyInputs(const string& instructon){
    return cpu->verifyInputs(instructon);
}

CPU* Machine::getcpu() {
    return cpu;
}

Memory* Machine::getmem() {
    return memory;
}


void Machine::runTillHalt(Ui::MainWindow* ui) {
    cpu->runTillHalt(*memory,ui);
}

void Machine::runNextStep() {
    cpu->runNextStep(*memory);
}

void Machine::clearInstructions() {
    instructions.clear();
}

void Machine::resetExecutionState() {

    cpu->setPC("0A");
    cpu->setend();
}



//##################################################//
//################### Memory #######################//
//##################################################//

void Memory::setCell(const string &address,const string &value) {

    memory[address] = value;
}

string Memory::getCell(const string& address) {

    return memory[address];
}




void Memory::takeValuesFromFileAndAssignIt(vector<string> &instructions,string pc) {

    string address1,address2, value1, value2;
    setStart(pc);
    if(pc == ""){
        pc = "0A";
    }
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


void Memory::takeValuesOneByOneAndAssignIt(std::string &instruction) {


    string address1,address2, value1, value2;
    address1 = intToHex(start);
    start++;
    address2 = intToHex(start);
    start++;
    value1 = instruction.substr(0, 2); // First 2 characters
    value2 = instruction.substr(2, 2); // Next 2 characters
    setCell(address1,value1);
    setCell(address2,value2);
}




string Memory::intToHex(int num) {
    stringstream ss;
    ss << uppercase << setw(2) << setfill('0') << hex << num;
    return ss.str();

}


void Memory::clearMemory() {

    for (int i = 0; i <= 255; i++) {
        string hexAddress = intToHex(i);
        memory[hexAddress] = "00";
    }

}

Memory::Memory() {
    start = 10;
    clearMemory();
}

void Memory::printMemory(){

    cout<< "Address" << "     " << "Value\n\n";
    for (auto &item: memory) {
        cout << item.first << "          " << item.second << '\n';
    }
}

void Memory::setStart( std::string PC = "0A") {

    start = stoi(PC, nullptr, 16);
}

string Memory::hexatoBinary(const string &hexa) {
    string binary;
    for (char i : hexa) {
        switch (i) {
        case '0':
            binary += "0000";
            break;
        case '1':
            binary += "0001";
            break;
        case '2':
            binary += "0010";
            break;
        case '3':
            binary += "0011";
            break;
        case '4':
            binary += "0100";
            break;
        case '5':
            binary += "0101";
            break;
        case '6':
            binary += "0110";
            break;
        case '7':
            binary += "0111";
            break;
        case '8':
            binary += "1000";
            break;
        case '9':
            binary += "1001";
            break;
        case 'A':
            binary += "1010";
            break;
        case 'B':
            binary += "1011";
            break;
        case 'C':
            binary += "1100";
            break;
        case 'D':
            binary += "1101";
            break;
        case 'E':
            binary += "1110";
            break;
        case 'F':
            binary += "1111";
            break;
        default:
            cout << "Invalid hexadecimal digit " << i << endl;
        }
    }
    return binary;


}

//####################################################//
//################### Register #######################//
//####################################################//

string Register::getHexadecimalRange(int num) {

    stringstream ss;

    ss << hex << uppercase << num;

    return ss.str();
}


void Register::clearRegister() {

    for (int i = 0; i <= 15; i++) {
        string hexAddress = getHexadecimalRange(i);
        register1[hexAddress] = "00";
    }

}

Register::Register() {

    clearRegister();
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

string Register::hexatoBinary(const string &hexa) {
    string binary;
    for (char i : hexa) {
        switch (i) {
        case '0':
            binary += "0000";
            break;
        case '1':
            binary += "0001";
            break;
        case '2':
            binary += "0010";
            break;
        case '3':
            binary += "0011";
            break;
        case '4':
            binary += "0100";
            break;
        case '5':
            binary += "0101";
            break;
        case '6':
            binary += "0110";
            break;
        case '7':
            binary += "0111";
            break;
        case '8':
            binary += "1000";
            break;
        case '9':
            binary += "1001";
            break;
        case 'A':
            binary += "1010";
            break;
        case 'B':
            binary += "1011";
            break;
        case 'C':
            binary += "1100";
            break;
        case 'D':
            binary += "1101";
            break;
        case 'E':
            binary += "1110";
            break;
        case 'F':
            binary += "1111";
            break;
        default:
            cout << "Invalid hexadecimal digit " << i << endl;
        }
    }
    return binary;


}

//##############################################//
//################### CU #######################//
//##############################################//



void CU::load1(const string &register_position,const string& address,Register &register1, Memory &memory){

    register1.setCell(register_position,memory.getCell(address)) ;
}

void CU::load2(const string &register_position,const string& value,Register &register1){

    register1.setCell(register_position,value) ;
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

    }
}

void CU::move(string idxReg_1, string idxReg_2, Register &register1) {
    string reg_data = register1.getCell(idxReg_1);
    register1.setCell(idxReg_2,reg_data);
}


void CU::jump(string idxReg, string RX, Register &register1, int &pc) {
    if (register1.getCell(idxReg) == register1.getCell("0")){
        int new_address = hexStringToInt(RX) - pc;
        pc += new_address;                                                             //Didn't test it yet
    }
}

void CU::jump2(std::string idxReg, std::string RX, Register &register1, int &pc) {
    if (register1.getCell(idxReg) > register1.getCell("0")){
        int new_address = hexStringToInt(RX) - pc;
        pc += new_address;
    }
}

int CU::rightCyclicRotate(int value, int steps, int register_size = 8) {
    int rotated = (value >> steps) | (value << (register_size - steps));
    return rotated & 0xFF;
}

void CU::rotate(const string &register_position,const string& num_of_steps, Register &register1) {

    int content_in_int = stoi(register1.getCell(register_position), nullptr,16);

    int steps_in_int = stoi(num_of_steps);

    int after_rotation = rightCyclicRotate(content_in_int,steps_in_int);

    string after_rotation_in_str = Memory::intToHex(after_rotation);

    register1.setCell(register_position,after_rotation_in_str);

}


void CU::halt() {
    //i will do it with GUI
}






//###############################################//
//################### ALU #######################//
//###############################################//

bool ALU::isValid(string statment) {
    regex valid ("[1-9A-C][0-9A-F]{3}");
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
    string dec1 = hexToDecimal(register1.getCell(idx1));
    string dec2 = hexToDecimal(register1.getCell(idx2));
    int result = stoi(dec1) + stoi(dec2);
    result &= 0xFF; // Ensure result is within 8-bit limit
    string resultHex = decimalToHex(to_string(result));
    register1.setCell(address, resultHex);
}
double ALU::floatextract(string hexa){
    stringstream converter;
    char signchar = hexa[0];
    int exponent, sign = (signchar >= '8') ? -1 : 1, leftside = 0;
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
    for (int i = 0; i < 7; ++i){
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
    mantissa += (mantissa.length() < 4) ? string(4 - mantissa.length(), '0') : "";
    string Final_bin = sign + expo + mantissa;
    string Hexa = FourBX[Final_bin.substr(0, 4)] + FourBX[Final_bin.substr(4,4)];
    return Hexa;
}
void ALU::addF(string idx1, string idx2, Register &register1, string address){

    double value1 = floatextract(register1.getCell(idx1));
    double value2 = floatextract(register1.getCell(idx2));
    double sum = value1 + value2;
    if (sum < -7.5) sum = -7.5;
    if (sum > 7.5) sum = 7.5;
    string sum_hex = floattohex(sum);
    register1.setCell(address, sum_hex);
}


string ALU::hexAnd(const string &hex1, const string &hex2) {

    // Convert hex strings to integers
    int num1 = stoi(hex1, nullptr, 16);
    int num2 = stoi(hex2, nullptr, 16);

    // Perform bitwise AND operation
    int result = num1 & num2;

    // Convert the result back to a hexadecimal string
    stringstream ss;
    ss << uppercase << hex << result;
    return ss.str();
}

void ALU::andOperator(const string &register_position1, const string &register_position2,const string &register_store_position, Register &register1) {

    string result_of_AND = hexAnd(register1.getCell(register_position1), register1.getCell(register_position2));

    register1.setCell(register_store_position,result_of_AND);


}

string ALU::OR(string hexa1, string hexa2){
    string bin1 = X4B[hexa1[0]] + X4B[hexa1[1]];
    string bin2 = X4B[hexa2[0]] + X4B[hexa2[1]];
    string final_bin;
    for (int i = 0; i < 8; ++i) {
        if (bin1[i] == '0'){
            if (bin2[i] == '0') final_bin += "0";
            else final_bin += "1";
        }else{
            final_bin += "1";
        }
    }
    string fin_hex = FourBX[final_bin.substr(0, 4)] + FourBX[final_bin.substr(3, 4)];
    return fin_hex;

}
string ALU::XOR(string hexa1, string hexa2){
    string bin1 = X4B[hexa1[0]] + X4B[hexa1[1]];
    string bin2 = X4B[hexa2[0]] + X4B[hexa2[1]];
    string final_bin;
    for (int i = 0; i < 8; ++i) {
        if (bin1[i] == '0'){
            if (bin2[i] == '0') final_bin += "0";
            else final_bin += "1";
        }else{
            if (bin2[i] == '0') final_bin += "1";
            else final_bin += "0";
        }
    }
    string fin_hex = FourBX[final_bin.substr(0, 4)] + FourBX[final_bin.substr(3, 4)];
    return fin_hex;
}


//###############################################//
//################### CPU #######################//
//###############################################//

CPU::CPU():program_cnt(10),END(false){

    register1 = new Register();
    cu = new CU();
    alu = new ALU();
}

CPU::~CPU(){

    delete register1;
    delete cu;
    delete alu;
}

bool CPU::verifyInputs(const string& instructon){
    return alu->isValid(instructon);
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
    else if (opcode == "3") { // Opcode 3: store

        cu->store(reg_pos, operand, new_register,memory);
    }
    else if (opcode == "4") {
        string register_pos1, register_pos2 ;
        register_pos1 += operand.front();
        register_pos2 += operand.back();
        cu->move(register_pos1, register_pos2, new_register);
    }
    else if (opcode == "5") {
        string register_pos1, register_pos2 ;
        register_pos1 += operand.front();
        register_pos2 += operand.back();
        alu->add(register_pos1, register_pos2, new_register, reg_pos);
    }
    else if (opcode == "6") {
        string register_pos1, register_pos2 ;
        register_pos1 += operand.front();
        register_pos2 += operand.back();

        alu->addF(register_pos1, register_pos2, new_register, reg_pos);
    }
    else if (opcode == "7") {
        string register_pos1, register_pos2 ;
        register_pos1 += operand.front();
        register_pos2 += operand.back();

        string value1 = new_register.getCell(register_pos1);
        string value2 = new_register.getCell(register_pos2);
        string answer = alu->OR(value1,value2);
        new_register.setCell(reg_pos,answer);
    }
    else if (opcode == "8") {
        string register_pos1, register_pos2 ;
        register_pos1 += operand.front();
        register_pos2 += operand.back();
        alu->andOperator(register_pos1, register_pos2, reg_pos, new_register);
    }
    else if (opcode == "9") {
        string register_pos1, register_pos2 ;
        register_pos1 += operand.front();
        register_pos2 += operand.back();

        string value1 = new_register.getCell(register_pos1);
        string value2 = new_register.getCell(register_pos2);
        string answer = alu->XOR(value1,value2);
        new_register.setCell(reg_pos,answer);
    }

    else if (opcode == "A") {
        cu->rotate(reg_pos,operand,new_register);
    }
    else if (opcode == "B") {
        cu->jump(reg_pos, operand, new_register,program_cnt);
    }
    else if (opcode == "D") {
        cu->jump2(reg_pos, operand, new_register,program_cnt);
    }

}


void CPU::runNextStep(Memory &memory) {
    string instruction = fetch(memory);
    if (instruction_register != "C000" && !END) {  // Assuming "HALT" is the halt condition

        vector<string> decoded = decode(instruction);
        execute(*register1, memory, decoded);

        SCR_Vect.push_back(memory.getCell("00"));
    }else{
        END = true;
    }

}

void CPU::runTillHalt(Memory &memory,Ui::MainWindow* ui) {
    // //string instruction = fetch(memory);
    // while (instruction_register != "C000") {
    //     runNextStep(memory);
    // }
    END = false;
    instruction_register = memory.getCell(Memory::intToHex(program_cnt));  // Set to starting address if needed

    // Run instructions until HALT
    while (instruction_register != "C000") {
        runNextStep(memory);

        QCoreApplication::processEvents();
    }
    display_screen(ui);


    END = true;  // Set END after HALT is reached
}

void CPU::setPC(const string &address) {
    program_cnt = stoi(address, nullptr, 16);
}

bool CPU::getend(){
    return END;
}

void CPU::setend(){
    END = false;
}

string CPU::getPC() {
    return Memory::intToHex(program_cnt);
}

Register* CPU::getreg(){
    return register1;
}
CU* CPU::getcu(){
    return cu;
}
ALU* CPU::getAlu(){
    return alu;
}

void CPU::printRegister(){

    register1->printRegister();
}

int CPU::hexStringToInt(string hexStr){
    // Convert hex string to integer
    int result = 0;
    for (char c : hexStr) {
        result *= 16; // Shift left in base 16
        if (c >= '0' && c <= '9') {
            result += c - '0'; // Convert character to corresponding integer value
        } else if (c >= 'A' && c <= 'F') {
            result += c - 'A' + 10; // Convert character to corresponding integer value
        }
    }
    if (result >= 128) { // If the value is greater than or equal to 128
        result -= 256; // Convert to negative value
    }

    return result;
}


void CPU::display_screen(Ui::MainWindow *ui){
    string print = "";
    for (string& hex : SCR_Vect){
        if(hex == "00" || hex == LASTHEX){
            continue ;
        }
        LASTHEX = hex;
        string ascii = "";
        for (size_t i = 0; i < hex.length(); i += 2) {
            string part = hex.substr(i, 2);
            char ch = stoul(part, nullptr, 16);
            ascii += ch;
        }
        print += "ascii = "+ascii + ", hex = " + hex + "\n";

        qDebug() << "Memory content at address '00': " << QString::fromStdString(hex); // Debugging line
    }
    ui->textEdit->setText(QString::fromStdString(print));
}

void CPU::clear_screen(){
    SCR_Vect.clear();
    LASTHEX = "";
}




