#include "sDes.h"

#include <vector>
#include <iostream>
#include <bitset>
using namespace std;

/* Permutates ten bits with 1 ten bit key*/
bitset<10> sDes::permutation_ten(bitset<10> key) {
    int permutation_array[] = {3, 5, 2, 7, 4, 10, 1, 9, 8, 6};
    bitset<10> return_key;

    /* Permutates each bit, little-endian */
   for(int i = 0; i < 10; i++){
       return_key[9 - i] = key[9 - (permutation_array[i] - 1)];
   }

    return return_key;
}

/* Permutates eight bits with 1 ten bit key*/
bitset<8> sDes::permutation_eight(bitset<10> key){
    int permutation_array[] = {6, 3, 7, 4, 8, 5, 10, 9};

    bitset<8> return_key;

    /* Permutates each bit, little-endian */
    for(int i = 0; i < 8; i++){
        return_key[7 - i] = key[9 - (permutation_array[i] - 1)];
    }

    return return_key;
}

/* Permutates four bits  with 2 two bit keys*/
bitset<4> sDes::permutation_four(bitset<2> first_key, bitset<2> second_key){
    bitset<4> transition, result;
    int permutation_array[4] = {2, 4, 3, 1};

    /* Combines the two keys into one */
    transition[3] = first_key[1];
    transition[2] = first_key[0];
    transition[1] = second_key[1];
    transition[0] = second_key[0];

    /* Permutates each bit, little-endian */
    for(int i = 0; i < 4; i++){
        result[3-i] = transition[3 - (permutation_array[i] - 1)];
    }

    return result;
}

/* Handles Circular Shifting */
bitset<5> sDes::left_shift(bitset<5> key, int amount){
    int temp_bit;
    for(int i = 0; i < amount; i++){
        temp_bit = key.test(4);
        key = key << 1;
        key.set(0,  temp_bit);
    }

    return key;
}

/* Permutates eight bits with 1 eight bit keys */
bitset<8> sDes::initial_permutation(bitset<8> key){
    int permutation_array[] = {2, 6, 3, 1, 4, 8, 5, 7};

    bitset<8> return_key;

    /* Permutates each bit, little-endian */
    for(int i = 0; i < 8; i++){
        return_key[7 - i] = key[9 - permutation_array[i] - 1];
    }

    return return_key;
}

/* Permutates eight bits with 1 eight bit keys */
bitset<8> sDes::initial_permutation_inverse(bitset<8> key){
    int permutation_array[] = {4, 1, 3, 5, 7, 2, 8, 6};

    bitset<8> return_key;

    /* Permutates each bit, little-endian */
    for(int i = 0; i < 8; i++){
        return_key[7 - i] = key[9 - permutation_array[i] - 1];
    }

    return return_key;
}

/* Permutates each bit twice, little-endian */
bitset<8> sDes::ep(bitset<4> key){
    int permutation_array[] = {4, 1, 2, 3, 2, 3, 4, 1};
    bitset<8> result;
    /* Permutates each bit twice, little-endian */
    for(int i = 0; i < 8; i++){
        result[i] = key[permutation_array[i] - 1];
    }

    return result;
}

/* Permutates with two dimensional array */
bitset<2> sDes::s_zero(bitset<4> key){
    bitset<2> q1, q2, result;
    int permutation_array[4][4] = {{1, 0, 3, 2}, {3, 2, 1, 0}, {0, 2, 1, 3}, {3, 1, 3, 2}};

    q1.set(1, key[3]);
    q1.set(0, key[0]);

    q2.set(1, key[2]);
    q2.set(0, key[1]);

    result = permutation_array[q1.to_ulong()][q2.to_ulong()];

    return result;
}

/* Permutates with two dimensional array */
bitset<2> sDes::s_one(bitset<4> key){
    bitset<2> q1, q2, result;
    int permutation_array[4][4] = {{0, 1, 2, 3}, {2, 0, 1, 3}, {3, 0, 1, 0}, {2, 1, 0, 3}};

    q1.set(1, key[3]);
    q1.set(0, key[0]);

    q2.set(1, key[2]);
    q2.set(0, key[1]);

    result = permutation_array[q1.to_ulong()][q2.to_ulong()];

    return result;
}

vector<bitset<8>> sDes::key_generation(bitset<10> key){
    vector<bitset<8>> key_container;
    bitset<10> result_key;
    bitset<5> sub_key_one;
    bitset<5> sub_key_two;

    // Permutates Key
    key = permutation_ten(key);

    // Splits key into two sub keys
    for(int i = 0; i < 5; i++){
        sub_key_one.set(i, key.test(i + 5));
        sub_key_two.set(i, key.test(i));
    }

    // Circular Left-shifts both sub keys once
    sub_key_one = left_shift(sub_key_one, 1);
    sub_key_two = left_shift(sub_key_two, 1);

    // Combines both sub keys back into a key
    for(int i = 0; i < 5; i++){
        result_key.set(i + 5, sub_key_one.test(i));
        result_key.set(i, sub_key_two.test(i));
    }

    // Permutates by eight and pushes into container
    key_container.push_back(permutation_eight(result_key));

    result_key.reset();

    // Circular Left-shifts both sub-keys by two
    sub_key_one = left_shift(sub_key_one, 2);
    sub_key_two = left_shift(sub_key_two, 2);

    // Combines both sub keys back into a key
    for(int i = 0; i < 5; i++){
        result_key.set(i + 5, sub_key_one.test(i));
        result_key.set(i, sub_key_two.test(i));
    }

    // Permutates by eight and pushes into container
    key_container.push_back(permutation_eight(result_key));

    // Returns container
    return key_container;
};

/* Handles the sub loop within sdes */
vector<bitset<4>> sDes::processing(bitset<4> input_one, bitset<4> input_two, bitset<8> key){
    vector<bitset<4>> result;
    bitset<8> ep_result;
    bitset<2> s_result_one, s_result_two;
    bitset<4> process_result;
    bitset<4> sub_four_result_one, sub_four_result_two;

    // PlainText Second Half is pushed back immediately
    result.push_back(input_two);

    // EP's PlainText Second Half
    ep_result = ep(input_two);

    // XOR's PlainText Second Half against First Key
    ep_result = ep_result ^ key;

    // Splits the PlainText Second Half into two sub keys
    for(int i = 0; i < 4; i++){
        sub_four_result_one.set(i, ep_result.test(i + 4));
        sub_four_result_two.set(i, ep_result.test(i));
    }

    // S-Boxes both Sub Keys
    s_result_one = s_zero(sub_four_result_one);
    s_result_two = s_one(sub_four_result_two);

    // Combines & Permutates both Sub Keys
    process_result = permutation_four(s_result_one, s_result_two);

    // XOR's PlainText Second Half with Plaintext First Half
    process_result = process_result ^ input_one;

    // Modified Plaintext Second Half is pushed back
    result.push_back(process_result);

    return result;
}

/* Handles both sub loops, IP, IP inverse */
bitset<8> sDes::encryption(string plaintext, string key, bool encryption){
    bitset<8> trans_plaintext(plaintext);
    bitset<10> trans_key(key);
    bitset<8> ip_result;
    bitset<4> sub_key_one;
    bitset<4> sub_key_two;
    vector<bitset<8>> key_container;
    vector<bitset<4>> processing_result;
    bitset<8> ip_input;

    // Generates both keys
    key_container = key_generation(trans_key);

    cout << "K1: " << key_container[0] << endl;
    cout << "K2: " << key_container[1] << endl;

    // Runs inital permutation on plaintext
    ip_result = initial_permutation(trans_plaintext);

    // Splits plaintext into two sub keys
    for(int i = 0; i < 4; i++) {
        sub_key_one.set(i, ip_result.test(4 + i));
        sub_key_two.set(i, ip_result.test(i));
    }

    // Handles Encryption
    if(encryption){
        // First Sub Loop
        processing_result = processing(sub_key_one, sub_key_two, key_container[0]);

        // Second Sub Loop
        processing_result = processing(processing_result[0], processing_result[1], key_container[1]);
    }
    else{
        // First Sub Loop
        processing_result = processing(sub_key_one, sub_key_two, key_container[1]);

        // Second Sub Loop
        processing_result = processing(processing_result[0], processing_result[1], key_container[0]);
    }

    // Combines both Sub Keys
    for(int i = 0; i < 4; i++){
        ip_input.set(i + 4, processing_result[1].test(i));
        ip_input.set(i, processing_result[0].test(i));
    }

    // Handles final permutation
    ip_input = initial_permutation_inverse(ip_input);

    // Returns Encrypted/Decrypted data
    return ip_input;
}

/* Checks if strings are valid binary && if are correct length */
bool sDes::binary_validation(string key, int size){
    if(key.size() != size){
        cout << "Binary is incorrect length!" << endl;
        return false;
    }

    for(int i = 0; i < key.size(); i++){
        if(key[i] != '0' && key[i] != '1'){
            cout << "Binary is invalid!" << endl;
            return false;
        }
    }

    return true;
}

/* Handles main functionality of S-Des */
void sDes::execute(){
    string userInputStr, plaintext, key;
    bool encryption = false;

    cout << "Please Choose from the following: (Defaults to encryption)" << endl << "1. Encryption"
         << endl << "2. Decryption" << endl;
    cin >> userInputStr;

    if(userInputStr == "1"){
        encryption = true;
    }else{
        encryption = false;
    }

    userInputStr = "";

    do{
        cout << "Please enter a 10 bit key (e.g. 1100110010)" << endl;
        cin >> userInputStr;

        key = userInputStr;
    }while(!binary_validation(userInputStr, 10));

    userInputStr = "";

    do{
        if(encryption){
            cout << "Please enter a 8 bit plaintext binary (e.g. 10101010)" << endl;
        }else{
            cout << "Please enter a 8 bit ciphertext binary (e.g. 10101010)" << endl;
        }

        userInputStr = "";

        cin >> userInputStr;

        plaintext = userInputStr;
    }while(!binary_validation(userInputStr, 8));

    cout << "Key: " << key << endl;
    cout << "P: " << plaintext << endl;

    cout << "C: " << sDes::encryption(plaintext, key, encryption) << endl << endl;
}