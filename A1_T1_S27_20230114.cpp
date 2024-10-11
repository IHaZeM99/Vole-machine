// File: A1_T1_S27_20230114.cpp
// Author: Hazem Ahmed Mohamed Abd-el-Mageed
// Section: 27
// ID:20230114
// Date: 10 Oct 2024

#include <bits/stdc++.h>
using namespace std;

bool valid_bainry(const string &input){
    for (char c : input) {
        if (c != '0' && c != '1') {
            return false;
        }
    }
    return true;
}

bool valid_num(const string &input){
    while (true) {
        bool valid = true;
        for (char c : input) {
            if (!isdigit(c)) {
                valid = false;
                break;
            }
        }
        if (valid) {
            return true;
        } else {
            return false;
        }
    }
}

int phishing(const string &email,const string &line){
    regex word_regex("\\b" + line + "\\b", regex_constants::icase);
    return regex_search(email, word_regex);
}

void main_email(){
    string ans_e,email_path,key_path;
    string email = "" , e_line;
    int ind = 0;
    map<string , int> map;
    int count = 0;
    cout << "\nPlease enter the path of the email text file:";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin , email_path);
    cout << "\nPlease enter the path of the key text file:";
    getline(cin , key_path);
    ifstream input(email_path);
    ifstream key(key_path);
    while (!key.is_open() || !input.is_open()) {
        cout << "Error opening the file!";
        cout << "\nPlease enter the full path of the email text file:";
        getline(cin , email_path);
        cout << "\nPlease enter the full path of the key text file:";
        getline(cin , key_path);
        input.open(email_path);
        key.open(key_path);
    }
    string line;
    while (getline(input, e_line)){
        email.append(e_line);
    }
    while (getline(key, line)) {
        if (ind < 10){
            map[line] = 1;
            ind++;
        }
        else if (ind >= 10 && ind < 20){
            map[line] = 2;
            ind++;
        }
        else if (ind >= 20){
            map[line] = 3;
            ind ++;
        }
    }
    auto it_l = map.begin();
    while (it_l != map.end()) {
        if(phishing(email,it_l->first)){
            count += it_l->second;
            cout << it_l->first << " ,the total points now is:" << count << endl;
        }
        ++it_l;
    }
    if (count >= 10) {
        cout << "This email is highly likely to be phishing." << endl;
    } else if (count > 5) {
        cout << "This email may be phishing. Proceed with caution." << endl;
    } else {
        cout << "This email appears to be safe." << endl;
    }
    cout << "---------------------------";
    key.close();
    input.close();
}

///////////////////////////////////problem 9-done

bool boolean_bears(int n){
    if (n == 42){
        //cout << "wow";
        return true;
    }
    if (n % 10 == 0){
        if ((n - 42 >= 42) && (n / 2 >= 42)){
            //cout << 10 <<endl;
            return boolean_bears(n - 42) || boolean_bears(n / 2);
        }
    }
    if (n % 5 == 0){
        if (n - 42 >= 42) {
            n -= 42;
            //cout << n << "-5" << endl;
            return boolean_bears(n);
        }
    }
    if (n % 2 == 0){
        if (n / 2 >= 42) {
            //cout << n << "-2" << endl;
            if (((n % 4 == 0) || (n % 3 == 0)) && (!boolean_bears(n/2))){
                if (n - ((n % 10) * ((n % 100) / 10)) >= 42){
                    if ((n % 10) * ((n % 100) / 10) == 0){
                        return false;
                    }
                    n -= (n % 10) * ((n % 100) / 10);
                    //cout << n << "-4" << endl;
                    return boolean_bears(n);
                }
            }
            n /= 2;
            return boolean_bears(n);
        }
    }
    if (n % 4 == 0 || n % 3 == 0){
        if (n - ((n % 10) * ((n % 100) / 10)) >= 42){
            if ((n % 10) * ((n % 100) / 10) == 0){
                return false;
            }
            n -= (n % 10) * ((n % 100) / 10);
            //cout << n << "-4" << endl;
            return boolean_bears(n);
        }
    }
    //cout << n << endl;
    return false;
}

void main_bears(){
    string n;
    int num;
    cout << "\nPlease enter the number of bears:";
    while (true) {
        cin >> n;
        if (valid_num(n)) {
            num = stoi(n);
            break;
        } else {
            cout << "\n Please enter a valid number:";
        }
    }
    if(boolean_bears(num)){
        cout << "\ntrue";
    }else{
        cout << "\nfalse";
    }
    cout << "\n---------------------------";
}

//////////////////////problem 6

void binaryPrint(int n){
    if(n == 0){                                                         //solve the only-zero problem
        return;
    }if (n != 0){
        binaryPrint(n/2);
        cout << n % 2;
    }
    //cout << "----------" << n << endl;
}

void numbers(string prefix, int k){
    if (k == 0){
        cout << prefix << endl;                                           //numbers done
    }
    if (k != 0){
        numbers(prefix+"0",k-1);
        numbers(prefix+"1",k-1);
    }
}

void main_numbers(){
    while(true) {
        string ans_num;
        cout << "\nPlease choose which operation do you want \n1-One Binary Number.\n2-Printing Many Numbers:";
        cin >> ans_num;
        string n, k;
        int num, k_n;
        if (ans_num == "1") {
            cout << "\nPlease enter the number:";
            while (true) {
                cin >> n;
                if (valid_num(n)) {
                    num = stoi(n);
                    break;
                } else {
                    cout << "\n Please enter a valid number:";
                }
            }
            if (num == 0) {
                cout << 0;
            } else {
                binaryPrint(num);
            }
            break;
        } else if (ans_num == "2") {
            //////numbers
            string prefix;
            cout << "\nPlease enter the prefix:";
            while (true) {
                cin >> prefix;
                if (valid_bainry(prefix)) {
                    break;
                } else {
                    cout << "\n Please enter a valid number of 0 and 1:";
                }
            }
            cout << "\nPlease enter K:";
            while (true) {
                cin >> k;
                if (valid_num(k)) {
                    k_n = stoi(k);
                    break;
                } else {
                    cout << "\n Please enter a valid number:";
                }
            }
            numbers(prefix, k_n);
            break;
        } else {
            cout << "\nWrong choice" << endl;
        }
    }
    cout << "\n---------------------------";
}





/////////////////////////////////////////////////////////////////////////////////////
//problem 3
vector<string> split(const string &target,const string &delimiter){
    string temp = "";
    vector <string> res;
    for (char ch : target) {
        if (ch == delimiter[0]){
            res.push_back(temp);
            temp = "";
        }else{
            temp += ch;
        }
    }
    if(target.back() != delimiter[0]){
        res.push_back(temp);
    }
    return res;
}
void main_split() {
    string target, delimiter;
    cout << "please enter the target:" << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin,target);
    cout << "please enter the delimiter:" << endl;
    //cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, delimiter);
    vector <string> res;
    res = split(target,delimiter);
    for (int i = 0; i < res.size(); ++i) {
        if(i == 0){
            cout << "{";
        }
        cout << '"' << res[i] << '"' << " ";
        if (i == res.size() - 1){
            cout << "}";
        }
    }
    cout << "\n---------------------------";
}

//////////////////////////////////////////////
//main

int main(){
    while (true) {
        cout << "\nPlease choose \n3-Split\n6-printing numbers\n9-Teddy Bear Picnic.\n12-Phishing Scanner\n0-exit: ";
        string ans;
        cin >> ans;
        if (ans == "3") {
            main_split();
        } else if (ans == "6") {
            main_numbers();
        } else if (ans == "9") {
            main_bears();
        } else if (ans == "12") {
            main_email();
        } else if (ans == "0") {
            cout << "Exit";
            return 0;
        } else {
            cout << "\nWrong choice, please choose between 3 6 9 12 or 0." << endl;
        }
    }
}
