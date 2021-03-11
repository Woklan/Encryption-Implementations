#include <iostream>
#include "sDes.h"
#include "RSA.h"

using namespace std;

int main() {
    sDes sdes;
    RSA rsa;
    int userInput;
    string userInputStr;
    bool exit = false;
    bool error = false;

    while(!exit) {
        do{
            cout << "Please Choose from the following: " << endl;
            cout << "1. S-Des" << endl << "2. RSA" << endl << "3. Exit" << endl;
            cin >> userInputStr;

            try{
                userInput = stoi(userInputStr);
                error = false;
            }catch(exception e){
                cout << "You did not input a valid number" << endl;
                error = true;
            }
        }while(error);

        switch (userInput) {
            case 1:
                sdes.execute();
                break;

            case 2:
                rsa.execute();
                break;
            case 3:
                exit = true;
                break;

            default:
                cout << "You input a wrong number!" << endl;
                break;
        }
    }

    return 0;
}
