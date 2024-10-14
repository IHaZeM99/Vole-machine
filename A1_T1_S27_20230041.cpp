/*

 File: A1_T1_S27_20230041.cpp.
 Purpose: Assignment
 Author: Adam Mohamed Gamil Abdel latif
 Section: S28,S27
 ID: 20230041
 Date: 10 Oct 2024
 Explanation of the program:

 First program: Reads a sentence of up to 100 characters and outputs the sentence with spacing
 corrected and with letters corrected for capitalization. make sure the first character is capital and the rest
 of characters make sure it's small and end the program if you find a period or the number of characters exceeds 100 characters

 Second program: Print prime numbers in sieve way, user enters a number then program displays all prime numbers from
 2 to this number and the number can't exceed 1e7 to make sure program can't crash

 Third program: Reads some blocks of domino and check if it can make a correct chain or not, calling FormsDominoChain(dominoSet) would return true because it is
 possible to form the chain or returns false because there is no way to form a domino chain

 Fourth program: programs that takes a file in Arabic with some message or post. Then, it changes words that could be
 censored by the platform due to the view they represent with other alternatives.


*/
#include <bits/stdc++.h>
#include <codecvt>
#include <locale>
using namespace std;



string TakeAndCheckSentence(){

    string sentence;
    char ch;
    int char_count = 0; // To keep track of the number of characters

    cout << "\nPlease enter the sentence you want to correct (Note: you can't enter more than 100 characters or a period.)\n";
    cout << "Enter here:\n";

    // Continue reading characters until one of the conditions is met
    while (char_count < 100) {
        cin.get(ch); // Get input character by character
        if (ch == '\n') {
            sentence += ' '; // Add a space instead of a line break
            char_count++;
        }
        // Break the loop if the user enters a period
        else if (ch == '.') {
            sentence += ch; // Add the period to the sentence
            break;
        }
        else {
            sentence += ch;  // Add the character to the sentence
            char_count++;
        }

        // If the number of characters reaches 100, stop reading
        if (char_count >= 100) {
            break;
        }
    }

    return sentence;

}

string FindSentenceMistakes(){

    string sentence = TakeAndCheckSentence(); // take the sentence
    string correctedSentence = ""; // make an empty string that will contain the corrected sentence
    bool foundFirstLetter = false; // make found first letter equal false in case user starts the sentence with spaces
    for (int i = 0; i < sentence.size(); ++i) {
        if(!foundFirstLetter && isspace(sentence[i])){
            continue;
        }
        else if(isalpha(sentence[i]) && !foundFirstLetter){ // if first letter found make sure it's capital then add it to the corrected sentence
            char correctedChar = toupper(sentence[i]);      // and make found first letter equal to true
            correctedSentence += correctedChar;
            foundFirstLetter = true;
        }
        else{
            if(isalpha(sentence[i])){ // if found letter make sure to make it small then add it to the corrected sentence
                char correctedChar = tolower(sentence[i]);
                correctedSentence += correctedChar;
            }
            else if(ispunct(sentence[i])){ // if a punctuation found make sure it sticks with the word behind it
                if(correctedSentence.back() == ' '){
                    correctedSentence.pop_back();
                    correctedSentence += sentence[i];
                }
                else{
                    correctedSentence += sentence[i];
                }
            }
            else if(isspace(sentence[i])){ // if space is found just add it once until you find another char or punct then add it
                if(correctedSentence.back() == ' '){
                    continue;
                }
                else{
                    correctedSentence += sentence[i];
                }
            }
            else{
                correctedSentence += sentence[i];
            }
        }
    }


    // this two conditions just make sure to put the period in the correct way


    if(correctedSentence.back() == '.' && correctedSentence[correctedSentence.size()-2] == ' '){
        correctedSentence.pop_back();
        correctedSentence.pop_back();
        correctedSentence += '.';
    }
    else if(correctedSentence.back() != '.' ){
        correctedSentence += '.';
    }

    return correctedSentence;

}

// menu for the find sentence mistakes
void MenuForFindSentenceMistakes(){

    cout << "Welcome to the Find Sentence Mistake program\n\n";
    while(true){
        cout << "Choose 1 of these 2 options please\n";
        cout << "1- Enter a new sentence \n";
        cout << "2- Exit the program \n";
        cout << "Note: 1 for YES and 2 for NO\n";
        string choice;
        cin >> choice;
        if(choice == "1"){

            string sentence = FindSentenceMistakes();
            cout << "\nYour corrected sentence is: " << sentence << "\n\n";
        }
        else if(choice == "2"){
            break;
        }
        else{
            cout << "Please enter a correct choice\n\n";
        }

    }
}



/*###########################################################################*/
/*###########################################################################*/
/*###########################################################################*/
/*###########################################################################*/


void ListPrimesInSieveWay(int number){


    const int max_num = 1e6; // more than that the pc may crash
    bool primes[max_num];
    for (int i = 1; i < number; ++i) { // assume at first that all numbers are prime numbers
        primes[i] = true;
    }

    for (int i = 2; i*i <= number ; ++i) {
        if(primes[i]){
            for (int j = i*i; j <= number ; j += i) { // check all the multiplies of this prime number and make it false
                primes[j] = false;
            }
        }
    }

    // list prime numbers

    cout << "The prime numbers between 2 and " << number << " are: ";
    for (int i = 2; i <= number; ++i) {
        if(primes[i]){
            cout << i << " ";
        }
    }
    cout << "\n\n";
}


// menu for listing prime numbers in sieve way
void MenuForListPrimesInSieveWay(){

    cout << "Welcome to the List Primes program\n\n";
    while(true){
        cout << "Choose one of the two options please:\n";
        cout << "1- To proceed in the program\n";
        cout << "2- Exit the program\n";
        cout << "Note: 1 for YES and 2 for NO\n";
        string choice;
        cin >> choice;
        if(choice == "1"){

            int number;
            while(true){
                cout << "Type a number that you want to list all the prime numbers between this number and 2:\n";
                cin >> number;
                if (cin.fail() || cin.peek() != '\n') {
                    cout << "Invalid input! Expected an integer.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                }
                else{
                    if(number > 1e6){
                        cout << "Number is too big your pc may crash try a smaller number\n\n";
                    }
                    else if(number < 2){
                        cout << "You can't enter a number that is less than 2\n\n";
                    }
                    else {
                        ListPrimesInSieveWay(number);
                        break;
                    }
                }
            }

        }
        else if(choice == "2"){
            break;
        }
        else{
            cout << "Please enter a correct choice\n\n";
        }
    }
}


/*###########################################################################*/
/*###########################################################################*/
/*###########################################################################*/
/*###########################################################################*/






struct dominoT {
    int leftDots;
    int rightDots;

    // Overload the == operator to compare two structs
    bool operator==(const dominoT& other) const {
        return leftDots == other.leftDots && rightDots == other.rightDots;
    }
};

bool left_dots = true; // just to display the correct message for the user to enter the number in which side
int InsertAndCheckLeftAndRightNumbers(){

    int number;
    // just enter number and make sure it is correct
    while(true){
        if(left_dots){
            cout << "Type the number you want on the left spot of the domino\n";
        }
        else{
            cout << "Type the number you want on the right spot of the domino\n";
        }
        cin >> number;
        if (cin.fail() || cin.peek() != '\n') {
            cout << "Invalid input! Expected an integer.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
        }
        else{
            if(number < 0 || number > 6){
                cout << "The number you enter must be bigger than or equal to zero and smaller than or equal to six\n\n";
            }
            else {
                left_dots = !left_dots;
                return number;
            }
        }
    }

}


void InsertingDominos(vector<dominoT>& vecOfDominos){


    int size;
    // enter size of domino and make sure it doesn't exceed the 28 blocks of domino or smaller than or equal to 0
    while(true){
        cout << "Type the number of dominos you will enter\n";
        cin >> size;
        if (cin.fail() || cin.peek() != '\n') {
            cout << "Invalid input! Expected an integer.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
        }
        else{
            if(size <= 0 || size > 28){
                cout << "Number of blocks of domino must be bigger than zero and smaller than or equal to 28\n\n";
            }
            else {
                break;
            }
        }
    }

    int leftSideValue, rightSideValue;
    for (int i = 0; i < size; ++i) {
        leftSideValue = InsertAndCheckLeftAndRightNumbers();
        rightSideValue = InsertAndCheckLeftAndRightNumbers();


        dominoT target1 = {leftSideValue, rightSideValue}; // take the left side value and right side value and put it in block of domino
        dominoT target2 = {rightSideValue, leftSideValue}; // take the same domino and rotate it 180 degree to make sure the user doesn't enter the same block of domino twice but reverse it

        // use find to check if target exists in the vector
        auto it1 = find(vecOfDominos.begin(), vecOfDominos.end(), target1);
        auto it2 = find(vecOfDominos.begin(), vecOfDominos.end(), target2);

        // if any of both 2 block of domino found don't put it in the vector of domino
        if (it1 != vecOfDominos.end() || it2 != vecOfDominos.end()) {
            cout << "You can't enter the same domino block twice or it's reciprocal\n\n";
            i--; // return a step back
        }
        else {
            vecOfDominos.push_back({leftSideValue,rightSideValue}); // else push the block of domino in the vector
        }
    }

}

int index = 0; // this global value is used to check in the base case if we reached the final block of domino then we have succeeded to sort the chain correctly
bool FormsDominoChain(vector<dominoT>& dominos) {

    if(dominos.size() == 1){
        return true;
    }
    // base case: If we have arranged all dominos, return true
    if (index == dominos.size()) {
        return true;
    }


    for (int i = index; i < dominos.size(); ++i) {

        if (index == 0 || dominos[index - 1].rightDots == dominos[i].leftDots) {

            // swap the current domino to the current index position
            swap(dominos[index], dominos[i]);

            // try to complete the chain by moving to the next domino block
            index++;
            if (FormsDominoChain(dominos)) {
                return true; // if a valid chain is found, return true
            }

            // undo the swap and try another domino
            swap(dominos[index], dominos[i]);
        }
    }

    index--;
    return false; // if no valid chain is possible, return false
}



// menu for game of domino

void MenuForGameOfDominos(){

    cout << "Welcome to the Game Of Dominos program\n\n";
    while(true){
        cout << "Choose one of the two options please:\n";
        cout << "1- To proceed in the program\n";
        cout << "2- Exit the program\n";
        cout << "Note: 1 for YES and 2 for NO\n";
        string choice;
        cin >> choice;
        if(choice == "1"){

            vector<dominoT> vecOfDominos;
            InsertingDominos(vecOfDominos);

            if(FormsDominoChain(vecOfDominos)) {
                cout << "The arranged blocks of domino: ";
                for (int i = 0; i < vecOfDominos.size(); ++i) {
                    if (i != vecOfDominos.size() - 1) {
                        cout << vecOfDominos[i].leftDots << "|" << vecOfDominos[i].rightDots << " - ";
                    } else {
                        cout << vecOfDominos[i].leftDots << "|" << vecOfDominos[i].rightDots;
                    }
                }
            }
            else{
                cout << "There is no way to form a domino chain with current domino blocks, try again";
            }
            cout <<"\n\n";

        }
        else if(choice == "2"){
            break;
        }
        else{
            cout << "Please enter a correct choice\n\n";
        }
    }

}

/*###########################################################################*/
/*###########################################################################*/
/*###########################################################################*/
/*###########################################################################*/



// Function to load the replacement words from a file
map<wstring, wstring> LoadReplacements(const string &filename) {
    map<wstring, wstring> replacements;
    wifstream file(filename);
    file.imbue(locale(locale::classic(), new codecvt_utf8<wchar_t>)); // Ensure reading UTF-8 as wstring
    if (!file) {
        wcerr << L"Unable to open the replacements file!" << endl;
        return replacements;
    }

    wstring original, replacement;
    while (file >> original >> replacement) {
        replacements[original] = replacement;
    }
    file.close();
    return replacements;
}


// function to read UTF-8 encoded file (supports Arabic)

wstring ReadUnicodeFile(const string& file_path) {
    wifstream file(file_path);
    file.imbue(locale(locale::classic(), new codecvt_utf8<wchar_t>)); // Ensure reading UTF-8 as wstring

    if (!file.is_open()) {
        wcerr << L"Error: Unable to open the file for reading: " << file_path.c_str() << endl;
        return L"";
    }

    wstring content;
    wstring line;

    while (getline(file, line)) {
        content += line + L"\n"; // Store each line in wstring (wide string)
    }

    file.close();
    return content;
}

// function to write to a UTF-8 encoded file (to handle Arabic correctly)
void WriteUnicodeFile(const string& file_path, const wstring& content) {
    wofstream file(file_path);
    file.imbue(locale(locale::classic(), new codecvt_utf8<wchar_t>)); // Ensure writing UTF-8 as wstring

    if (!file.is_open()) {
        wcerr << L"Error: Unable to open the file for writing: " << file_path.c_str() << endl;
        return;
    }

    file << content;
    file.close();
}

// function to replace all occurrences of words based on the map
wstring ReplaceWords(const wstring &text, const map<wstring, wstring> &replacements) {
    wstringstream result;
    wstringstream stream(text);  // Break the text into lines
    wstring line;

    // Process each line separately
    while (getline(stream, line)) {
        wstringstream lineStream(line);
        wstring word;

        while (lineStream >> word) {
            bool found_al = false;

            // Check if the word starts with "ال" and handle it accordingly
            if(word.size() >= 2 && word.substr(0, 2) == L"ال") {
                found_al = true;
                word = word.substr(2); // Remove "ال" to search in the replacements map
            }

            // Check if the current word is in the replacements map
            if (replacements.find(word) != replacements.end()) {
                if(!found_al) {
                    result << replacements.at(word) << L" ";  // Replace the word
                } else {
                    result << L"ال" + replacements.at(word) << L" ";  // add "ال" at first of the word
                }
            } else {
                if(!found_al) {
                    result << word << L" ";  // Keep the word unchanged
                } else {
                    result << L"ال" + word << L" ";  // Keep the word with "ال"
                }
            }
        }

        result << L"\n";  // Ensure we add a line break after processing each line
    }

    wstring modified_text = result.str();

    // Remove trailing space or newline if any
    if (!modified_text.empty() && modified_text.back() == L'\n') {
        modified_text.pop_back();
    }

    return modified_text;
}

// check file name if it's correct or not
bool CheckFileName(string file_name){
    if(file_name.size() <= 4){ // the file name must be at least consist of 5 chars like "a.txt"
        return false;
    }
    else if(file_name[file_name.size()-1] == 't' && file_name[file_name.size()-2] == 'x' && file_name[file_name.size()-3] == 't' && file_name[file_name.size()-4] == '.'){
        return true;
    }
    else{
        return false;
    }
}

string GetOutputFileName(){

    string file_name = "arabic_output.txt"; // default file name
    while(true){
        cout << "Do you want to save the modified file in the default output file or in a new file\n";
        cout << "1- default file\n";
        cout << "2- new file\n";
        string option;
        getline(cin,option);
        if(option == "1"){
            break;
        }
        else if(option == "2"){
            cout << "Enter the new file name including it's extension (name.txt):\n";
            while(true) {
                getline(cin, file_name);
                if(CheckFileName(file_name)){
                    break;
                }
                else{
                    cout << "Incorrect file name please enter a correct one\n\n";
                }
            }
            break;
        }
        else{
            cout << "Please enter a correct choice\n\n";
        }

    }

    return file_name;
}

// menu for message altering to avoid censorship
void MenuForMessageAlteringToAvoidCensorship(){

    cout << "Welcome to the Message Altering To Avoid Censorship program\n\n";
    while(true){
        cout << "Choose one of the two options please:\n";
        cout << "1- To proceed in the program\n";
        cout << "2- Exit the program\n";
        cout << "Note: 1 for YES and 2 for NO\n";
        string choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear input buffer
        if(choice == "1"){

            cout << "Please enter the file name correctly with it's extension (.txt) to perform message altering on it\n";
            cout << "Note: you can't enter an empty file\n\n";
            string file_input_name;
            wstring content_of_input_file;
            while(true){
                cout << "Enter file name: ";
                getline(cin, file_input_name);
                content_of_input_file = ReadUnicodeFile(file_input_name);
                if(!content_of_input_file.empty()){
                    break;
                }
                else {
                    cout << "Error reading the file. Please try again.\n";
                }
            }

            // this commented map have the same lists of words in replacements txt incase you couldn't use the text file
           // map<wstring, wstring> replacements = {{L"حرب", L"اشتباك"},{L"قصف", L"استهداف"},{L"قتل", L"تصفية"},{L"مجزرة", L"حادثة"},{L"عدوان", L"هجوم"},{L"مقاومة", L"دفاع"},{L"سلاح", L"أداة"},{L"تهديد", L"تحذير"},{L"تدمير", L"انهيار"},{L"معركة", L"مواجهة"},{L"ارهاب", L"تخويف"},{L"انفجار", L"انبعاث"},{L"اعتداء", L"تجاوز"},{L"انتقام", L"رد"},{L"دمار", L"ضرر"},{L"الحصار", L"الإغلاق"},{L"اعتقال", L"احتجاز"},{L"هجوم", L"عملية"},{L"خيانة", L"خلاف"},{L"سفك", L"إراقة"},{L"استهداف", L"تركيز"},{L"اسرائيل", L"دولة الاحتلال"}};

            map<wstring, wstring> replacements = LoadReplacements("Replacements.txt");
            string output_file_name = GetOutputFileName(); // get the output file name

            wstring modified_text = ReplaceWords(content_of_input_file,replacements); // modify and replace the words you want to change

            WriteUnicodeFile(output_file_name,modified_text); // write the new code in the output file and save it

            cout << "A new modified text saved successfully\n\n";

        }
        else if(choice == "2"){
            break;
        }
        else{
            cout << "Please enter a correct choice\n\n";
        }
    }


}




/*###########################################################################*/
/*###########################################################################*/
/*###########################################################################*/
/*###########################################################################*/



// main menu for all 4 programs
void MainMenuForAllFourPrograms(){

    cout << "Welcome to the program\n\n";
    while(true){
        cout << "Choose one of the four options please:\n";
        cout << "1- Check sentence correctness\n";
        cout << "2- Print prime numbers in sieve way\n";
        cout << "3- Game of domino\n";
        cout << "4- Altering Arabic messages to avoid censorship\n";
        cout << "5- Exit the program\n";
        string choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if(choice == "1"){
            MenuForFindSentenceMistakes();
        }
        else if(choice == "2"){
            MenuForListPrimesInSieveWay();
        }
        else if(choice == "3"){
            MenuForGameOfDominos();
        }
        else if(choice == "4"){
            MenuForMessageAlteringToAvoidCensorship();
        }
        else if(choice == "5"){
            break;
        }
        else{
            cout << "Please enter a correct choice\n\n";
        }
    }
}

int main() {

    MainMenuForAllFourPrograms(); // start the main menu


    return 0;
}
