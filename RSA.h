//
// Created by User on 28/09/2020.
//

#ifndef ISASSIGNMENT_RSA_H
#define ISASSIGNMENT_RSA_H


class RSA {

public:
    void execute();                                 // Handles main functionality of RSA
    int squareAndMultiply(int a, int b, int n);     // Implements Square & Multiply Algorithm
    int greatestCommonDivisior(int x, int y);       // Finds Greatest Common Divisor
    bool checkPrime(int num);                       // Checks if Number is prime
};


#endif //ISASSIGNMENT_RSA_H
