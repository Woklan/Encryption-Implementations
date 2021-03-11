#ifndef ISASSIGNMENT_SDES_H
#define ISASSIGNMENT_SDES_H

#include <vector>
#include <bitset>

using namespace std;


class sDes {

public:

    void execute();
    bitset<10> permutation_ten(bitset<10> key);
    bitset<8> permutation_eight(bitset<10> key);
    bitset<4> permutation_four(bitset<2> first_key, bitset<2> second_key);
    bitset<5> left_shift(bitset<5> key, int amount);
    vector<bitset<8>> key_generation(bitset<10> key);
    bitset<8> initial_permutation(bitset<8> key);
    bitset<8> encryption(string plaintext, string key, bool encryption);
    bitset<8> ep(bitset<4> key);
    bitset<2> s_zero(bitset<4> key);
    bitset<2> s_one(bitset<4> key);
    vector<bitset<4>> processing(bitset<4> input_one, bitset<4> input_two, bitset<8> key);
    bitset<8> initial_permutation_inverse(bitset<8> key);
    bool binary_validation(string key, int size);
};


#endif //ISASSIGNMENT_SDES_H
