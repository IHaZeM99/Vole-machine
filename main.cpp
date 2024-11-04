#include <bits/stdc++.h>
#include "Vole.h"
using namespace std;
int main() {
  Machine adam ;
 /* adam.loadProgramFile("input.txt");
  adam.sendInstructionsToMemory();
  adam.sendInstructionsToCPU();
  adam.outPutState();
*/

  while(true){

      cout << "Do you want to start storing the instructions from the default address or do you want to enter the address you want to store in ? ";
      string address, option;
      cin >> option;
      if(option == "default"){
          address = "01";
          adam.setPC(address);
          break;
      }
      else if(option == "enter"){
          cout << "Enter the address you want to store in : ";
          cin >> address;
          // check if the address is valid in hexa form or not and if not make the user write it again

            if(address.size() != 2){
                cout << "Please enter a valid address\n";
                continue;
            }
            else if(address[0] < '0' || address[0] > '9' && address[0] < 'A' || address[0] > 'F'){
                cout << "Please enter a valid address\n";
                continue;
            }
            else if(address[1] < '0' || address[1] > '9' && address[1] < 'A' || address[1] > 'F'){
                cout << "Please enter a valid address\n";
                continue;
            }
          adam.setPC(address);
          break;
      }
      else{
          cout << "Please enter a valid option\n";

      }



  }

  while(true){

      cout << "1- Store an instruction in memory\n";
      cout << "2- Run the program\n";
      cout << "3- Print the memory and the register\n";

        string option;
        cin >> option;
        if(option == "1"){
            cout << "Enter the instruction you want to store in memory : ";
            string instruction;
            cin >> instruction;
            adam.loadProgramNormalWay(instruction);
        }
        else if(option == "2"){
           adam.runProgram();
        }
        else if(option == "3"){
            adam.outPutState();
        }
        else{
            cout << "Please enter a valid option\n";
        }


  }

    return 0;
}
