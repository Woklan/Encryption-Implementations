#include "RSA.h"

#include <iostream>
#include <cmath>

using namespace std;

/* Implements Square & Multiply Algorithm */
int RSA::squareAndMultiply(int a, int b, int n){
    int c = 0, d = 1;
    int k = floor(log(b) / log(2))+1;

    for(int i = k; i > 0; i--){
        c = 2 * c;
        d = (d * d) % n;

       if((b >> (i - 1) & 1U) == 1){
           c = c + 1;
           d = (d * a) % n;
       }
    }

    return d;
}

/* Finds Greatest Common Divisor */
int RSA::greatestCommonDivisior(int x, int y){
    if(x == 0){ return y;}
    if(y == 0 || x == y){ return x;}
    if(x >y){ return greatestCommonDivisior(x-y, x);}

    return (x > y ? greatestCommonDivisior(x-y, x) : greatestCommonDivisior(x, y-x));
}

/* Checks if Number is prime */
bool RSA::checkPrime(int num){
    // 0 & 1 are not primes
    if(num < 2){
       cout << "This Number is not Prime!" << endl;
       return false;
    }
    else {
        for (int i = 2; i <= num / 2; ++i) {
            if (squareAndMultiply(num, 1, i) == 0) {
                cout << "This Number is not Prime!" << endl;
                return false;
            }
        }
    }
    return true;
}

void RSA::execute(){
    string userInputStr;
    bool error = false;
    int q, p, e, m, n;

    /* Grabs P & error checking */
    do{
        cout << "Please input P:" << endl;
        cin >> userInputStr;

        try{
            p = stoi(userInputStr);
            error = false;
        }catch(exception e){
            cout << "You did not input a correct number!" << endl;
            error = true;
        }

    }while(error || !checkPrime(p));


    userInputStr = "";

    /* Grabs Q & error checking */
    do{
        cout << "Please input Q:" << endl;
        cin >> userInputStr;

        try{
            q = stoi(userInputStr);
            error = false;
        }catch(exception e){
            cout << "You did not input a correct number!" << endl;
            error = true;
        }

        if(p == q){
            cout << "Please do not enter the same prime as p for q" << endl;
        }

    }while(error || !checkPrime(q) || p == q);

    /* Generates N */
    n = p*q;

    /* Grabs E & error checking */
    do{
        userInputStr = "";

        cout << "Please input E:" << endl;
        cin >> userInputStr;

        try{
            e = stoi(userInputStr);
            error = false;
        }catch(exception e) {
            cout << "You did not input a correct number!" << endl;
            error = true;
        }

        if(greatestCommonDivisior((p-1) * (q-1), e) != 1 || e == 1){
            cout << "E is not relatively prime with Totient(n) & more than one" << endl;
            error = true;
        }

    }while(error);

    userInputStr = "";

    /* Grabs M & error checking */
    do{
        cout << "Please input M:" << endl;
        cin >> userInputStr;

        try{
            m = stoi(userInputStr);

            // Checks if M is less than N
            error = !(m < n);
            if(!error){
                cout << "Please enter a number lower than N!" << endl;
            }
        }catch(exception e) {
            cout << "You did not input a correct number!" << endl;
            error = true;
        }

    }while(error);

    cout << "P: " << p << endl;
    cout << "Q: " << q << endl;
    cout << "E: " << e << endl;
    cout << "M: " << m << endl;
    cout << "C: " << squareAndMultiply(m, e, n) << endl;
}