/*
Program Name: 10 Ciphers program
Author 1: Sohaila Abdelazim Khalifa
Author 2: Mariam Ayman Taha
Author 3: Abdelrhman Mohamed Ezzat
 */
#include <bits/stdc++.h>
using namespace std;

string Affine_decryption(const string& string_d, int m, int n);
string Affine_encryption(const string& string_e, int p, int q);
bool check_key(string key);
void simple_substitution_encryption(string& compare);
void simple_substitution_decryption(string& compare);
void polybius_decryption(string key);
bool is_valid(string msg, string key);
void polybius_encryption(string key);
string key_valid();
string rail_fence_cipher(string s);
string rail_fence_decipher(string s);
void XOR_decipher(string textToDecrypt,char secretLetter,int operation);
void XOR_cipher(string textToEncrypt,char secretLetter);
int hex_to_dec(string hexaText);
map<char,string> cipher = {
        {'a',".-"},  {'b',"-..."}, {'c',"-.-."}, {'d',"-.."}, {'e',"."}, {'f',"..-."}, {'g',"--."},
        {'h',"...."}, {'i',".."}, {'j',".---"}, {'k',"-.-"}, {'l',".-.."}, {'m',"--"}, {'n',"-."},
        {'o',"---"}, {'p',".--."}, {'q',"--.-"}, {'r',".-."}, {'s',"..."}, {'t',"-"},
        {'u',"..-"}, {'v',"...-"}, {'w',".--"}, {'x',"-..-"}, {'y',"-.--"}, {'z',"--.."}
};
void morse_cipher(string s);
void morse_decipher(string s);
int main(){
    while (true){
        int operation,oper2;
        cout << "Hello user, Please enter which cipher do you want to use:\n";
        cout << "1.Affine Cipher.\n" << "2.Caesar Cipher.\n"
                << "3.Atbash Cipher.\n" << "4.Vignere Cipher.\n" << "5.Baconian Cipher\n" <<
                "6.Simple Substitution Cipher.\n" << "7.Polybius Cipher.\n" << "8.Morse Code.\n" <<
                "9.XOR Cipher.\n" << "10.Rail fence Cipher.\n" << "11.End\n";
        cin >> operation;
        if (operation == 11){
            cout << "Thank you for using this program.\n";
            break;
        }
        cout << "Do you want to:\n" << "1.Encrypt.\n" << "2.Decrypt.\n";
        cin >> oper2;

        string text;
        if (operation == 1){
            int a,b,c;
            // Get three integers that will be used to build encryption and decryption function
            cout << "Please enter 3 integers 'a' 'b' 'c' to be used in cipher and decipher:" << endl;
            // Show the condition that should be satisfied before getting the input
            cout << "Check that the integers will satisfy this 'a*c % 26 = 1'" << endl;
            // Get the three integer inputs
            cout << "Integer a:";
            cin >> a;
            cout << "Integer b:";
            cin >> b;
            cout << "Integer c:";
            cin >> c;
            if (oper2 == 1){
                cout << "Enter the message you want to encrypt: ";
                cin.ignore();
                getline(cin,text);
                cout << "Message after encryption: " << Affine_encryption(text,a,b) << endl;
            }
            else if (oper2 == 2){
                cout << "Enter the message you want to decrypt: ";
                cin.ignore();
                getline(cin,text);
                cout << "Message after decryption: " << Affine_decryption(text,c,b) << endl;
            }
        }
        else if (operation == 2){
            int shifts;
            cout << "Please enter the shifts number : " << endl ;
            cin >> shifts ;
            while (shifts < 0){
                shifts += 26;
            }
            if (oper2 == 1){
                string message ;
                cout << "- Please enter the message you want to Cipher: " << endl;
                cin.ignore();
                getline(cin, message);

                //defensive to make all letters uppercase
                for (int i = 0; i < message.length(); ++i) {
                    message[i] = toupper(message[i]);
                }

                char letters[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
                                  'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
                                  'W', 'X', 'Y', 'Z'};
                string chiper = "";
                for (int i = 0; i < message.length(); i++) {
                    for (int j = 0; j < 26; ++j) {
                        if (message[i] == letters[j]) {
                            int index = (j + shifts) % 26;
                            chiper += letters[index];
                        }
                    }
                }
                cout << " Your  Ciphered message:" << chiper << endl;
            }
            else if(oper2 == 2){
                string message;
                int check ;
                cout << "- Please enter the message you want to Decipher: " << endl;
                cin.ignore();
                getline(cin, message);
                //defensive to make all letters uppercase
                for (int i = 0; i < message.length(); ++i) {
                    message[i] = toupper(message[i]);
                }
                char letters[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
                                  'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
                                  'W', 'X', 'Y', 'Z'};
                string Dechiper = "";
                int index;
                for (int i = 0; i < message.length(); i++) {
                    for (int j = 0; j < 26; ++j) {
                        if (message[i] == letters[j]) {
                            if (j < shifts ) {
                                index = ( 26 - ( shifts - j) )  ;
                            }
                            else {
                                index = (j - shifts) % 26;
                            }
                            Dechiper += letters[index];

                        }
                    }
                }

                cout << " Your Deciphered message :" << Dechiper << endl ;
            }
        }
        else if (operation == 3){
            if (oper2 == 1){
                string message ;
                int check ;
                cout << "- Please enter the message you want to Cipher: " << endl;
                cin.ignore();
                getline(cin, message,'\n');

                // defensive if enterd message not letters.
                bool test  = true ; // created boolen to break when user enters non - alphabetical message.
                for (int i = 0; i < message.length(); ++i) {
                    // check if string is an alphabet
                    check = isalpha(message[i]); // isalpha return 0 if its not an alphabet therefore used 0 as a condition.
                    if ( check == 0 && message [i] != char(32) ) {
                        cout << " Please enter only letters in your message . " << endl ;
                        test  = false ;
                        break;
                    }
                }
                if ( test == false ) {
                    break;
                }

                //defensive to make all letters uppercase
                for (int i = 0; i < message.length(); ++i) {
                    message[i] = toupper(message[i]);
                }

                char letters[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
                                  'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
                                  'W', 'X', 'Y', 'Z'};
                string chiper = "";
                for (int i = 0; i < message.length(); i++) {
                    // loops on the string and if the string equal the letter array it adds it to a new empty variable.
                    // at the same time it reverse the letter by using the len of teh array and the iritator
                    for (int j = 0; j < 26; ++j) {
                        if (message[i] == letters[j])
                            chiper += letters[25 - j];
                    }
                }
                cout << " Your  Ciphered message:" << chiper << endl;
            }
            else if (oper2 == 2){
                string message;
                int check ;
                cout << "- Please enter the message you want to Decipher: " << endl;
                cin.ignore();
                getline(cin, message,'\n');
                //defensive to make all letters uppercase
                for (int i = 0; i < message.length(); ++i) {
                    message[i] = toupper(message[i]);
                }

                // defensive if enterd message not letters.
                bool test  = true ;
                for (int i = 0; i < message.length(); ++i) {
                    // check if str[i] is an alphabet
                    check = isalpha(message[i]);
                    if ( check == 0 && message [i] != char(32) ) {
                        cout << " Please enter only letters in your message . " << endl ;
                        test  = false ;
                        break;
                    }
                }
                if ( test == false ) {
                    break;
                }
                //defensive to make all letters uppercase
                for (int i = 0; i < message.length(); ++i) {
                    message[i] = toupper(message[i]);
                }
                char letters[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
                                  'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
                                  'W', 'X', 'Y', 'Z'};
                string Dechiper = "";
                for (int i = 0; i < message.length(); i++) {
                    for (int j = 0; j < 26; ++j) {
                        if (message[i] == letters[j])
                            Dechiper += letters[ abs (25 - j) ];
                        // same idea of chiper except used abs to make sur it doesn't give a negative number.
                    }
                }
                cout << " Your Deciphered message :" << Dechiper << endl ;
            }
        }
        else if (operation == 4){
            if (oper2 == 1){
                int check;
                string message, keyword, cipher_text;
                cout << "- Please enter the keyword:  " << endl;
                cin >> keyword;
                if (keyword.length() > 8) {
                    cout << "!! Please enter keyword that doesnt exceed 8 letters :  " << endl;
                    cin >> keyword;
                }
                //defensive to make all letters uppercase
                for (int i = 0; i < keyword.length(); ++i) {
                    keyword[i] = toupper(keyword[i]);
                }
                // defensive if entered keyword not letters.
                for (int i = 0; i < keyword.length(); ++i) {
                    // check if keyword[i] is an alphabet
                    check = isalpha(keyword[i]);
                    if (check == 0) {
                        cout << " Please enter only letters in your keyword : " << endl;
                        cin >> keyword;
                    }
                }

                cout << "- Please enter the message you want to Cipher: " << endl;
                cin.ignore();
                getline(cin, message , '\n');
                if (message.length() > 80) {
                    cout << "!! Please enter message that doesnt exceed 80 letters :  " << endl;
                    cin >> message;
                }
                //defensive to make all letters uppercase
                for (int i = 0; i < message.length(); ++i) {
                    message[i] = toupper(message[i]);
                }
                // to make keyword as along as the entered message.
                for (int i = 0; i < message.length(); ++i) {
                    keyword+= keyword ;
                }

                for (int i = 0; i < message.length(); i++) {
                    if (message[i] == ' ') {
                        cipher_text += ' ';
                    }
                    else if ( message[i] >= 65 && message[i]<=90){
                        int chiper = ((message[i] + keyword[i]) % 26) + 'A';
                        cipher_text += char(chiper);
                    }
                    else {
                        cipher_text += message[i];
                    }
                }
                cout << " Your  Ciphered message:" << cipher_text << endl;
            }
            else if(oper2 == 2){
                string message, keyword, decipher_text;
                int check ;
                cout << "- Please enter the keyword:  " << endl;
                cin >> keyword;
                if (keyword.length() > 8) {
                    cout << "!! Please enter keyword that doesnt exceed 8 letters :  " << endl;
                    cin >> keyword;
                }
                //defensive to make all letters uppercase
                for (int i = 0; i < keyword.length(); ++i) {
                    keyword[i] = toupper(keyword[i]);
                }
                // defensive if entered keyword not letters.
                for (int i = 0; i < keyword.length(); ++i) {
                    // check if keyword[i] is an alphabet
                    check = isalpha(keyword[i]);
                    if (check == 0) {
                        cout << " Please enter only letters in your keyword : " << endl;
                        cin >> keyword;
                    }
                }

                cout << "- Please enter the message you want to decipher: " << endl;
                cin.ignore();
                getline(cin, message , '\n');
                if (message.length() > 80) {
                    cout << "!! Please enter message that doesnt exceed 80 letters :  " << endl;
                    cin >> message;
                }
                //defensive to make all letters uppercase
                for (int i = 0; i < message.length(); ++i) {
                    message[i] = toupper(message[i]);
                }
                // to make keyword as along as the entered message.
                for (int i = 0; i < message.length(); ++i) {
                    keyword+= keyword ;
                }

                for (int i = 0; i < message.length(); i++) {
                    if (message[i] == ' ') {
                        decipher_text += ' ';
                    }
                    else if ( message[i] >= 65 && message[i]<=90){
                        int dchiper = ( (message[i] - keyword[i] + 26) %26 ) + 'A';
                        decipher_text += char(dchiper);
                    }
                    else {
                        decipher_text += message[i];
                    }
                }
                cout << " Your  Deciphered message:" << decipher_text << endl;
            }
        }
        else if (operation == 5){
            char letters[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
                              'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
                              'W', 'X', 'Y', 'Z'};
            string code[] = {"aaaaa", "aaaab", "aaaba", "aaabb", "aabaa", "aabab", "aabba", "aabbb", "abaaa", "abaab", "ababa", "ababb",
                             "abbaa", "abbab", "abbba", "abbbb", "baaaa", "baaab", "baaba", "baabb", "babaa", "babab",
                             "babba", "babbb", "bbaaa", "bbaab"};
            if (oper2 == 1){
                string message ;
                int check ;
                cout << "- Please enter the message you want to Cipher: " << endl;
                getline(cin, message);
                cin >> message;

                // defensive if entered message not letters.
                bool test  = true ; // created boolen to break when user enters non - alphabetical message.
                for (int i = 0; i < message.length(); ++i) {
                    // check if string is an alphabet
                    check = isalpha(message[i]); // isalpha return 0 if its not an alphabet therefore used 0 as a condition.
                    if ( check == 0 ) {
                        cout << " Please enter only letters in your message . " << endl ;
                        test  = false ;
                        break;
                    }
                }
                if ( test == false ) {
                    break;
                }

                //defensive to make all letters uppercase
                for (int i = 0; i < message.length(); ++i) {
                    message[i] = toupper(message[i]);
                }

                string chiper = "";
                for (int i = 0; i < message.length(); i++) {
                    for (int j = 0; j < 26; ++j) {
                        if (message[i] == letters[j])
                            chiper = chiper + code[j] + " " ;
                    }
                }
                cout << " Your Ciphered message:" << chiper << endl;
            }
            else if(oper2 == 2){
                string message;
                cout << "- Please enter the message you want to Decipher: " << endl;
                cin.ignore() ;
                getline(cin, message);
                //defensive to make all letters uppercase
                for (int i = 0; i < message.length(); ++i) {
                    message[i] = tolower(message[i]);
                }
                string Dechiper = "";
                message.erase(remove(message.begin(), message.end(), ' '), message.end());
                for (int i = 0; i < message.length(); i += 5) {
                    string s = message.substr(i, 5);
                    for (int j = 0; j < 26; ++j) {
                        if (s == code[j])
                            Dechiper += letters[ j ];
                    }
                }
                cout << " Your Deciphered message :" << Dechiper << endl ;
            }
        }
        else if (operation == 6){
            string key,compare;
            cout << "Please enter the key that will be used in ciphering and deciphering: ";
            cin >> key;
            while (cin.fail() || key.length() > 5 || key.length() < 5 || !check_key(key)) {
                cout << "Please enter the key that will be used in ciphering and deciphering: " << endl;
                cin >> key;
            }
            compare = key;
            for (int i = 97; i <= 122; i++) {
                if (char(i) == key[0] || char(i) == key[1] || char(i) == key[2] || char(i) == key[3] || char(i) == key[4]) {
                    continue;
                } else {
                    compare += char(i);
                }
            }
            if (oper2 == 1){
                simple_substitution_encryption(compare);
            }
            else if(oper2 == 2){
                simple_substitution_decryption(compare);
            }
        }
        else if (operation == 7){
            string key = key_valid();
            if (oper2 == 1){
                polybius_encryption(key);
                cout << endl;
            }
            else if (oper2 == 2){
                polybius_decryption(key);
                cout << endl;
            }
        }
        else if (operation == 8){
            if (oper2 == 1){
                cout << "Enter the message you want to encrypt: ";
                cin.ignore();
                getline(cin,text);
                morse_cipher(text);
            }
            else if (oper2 == 2){
                cout << "Enter the message you want to decrypt: ";
                cin.ignore();
                getline(cin,text);
                morse_decipher(text);
            }
        }
        else if (operation == 9){
            char secretletter;
            cout << "Enter the secret letter: ";
            cin >> secretletter;
            if (oper2 == 1){
                cout << "\nEnter the message you want to encrypt:";
                cin.ignore();
                getline(cin,text,'\n');
                cout  << "\n";
                XOR_cipher(text,secretletter);
            }
            else if (oper2 == 2){
                int w;
                cout << "1: Decipher message using text\n";
                cout << "2: Decipher message using hexa\n";
                cin >> w;
                cout << "\nEnter the message you want to decrypt:";
                cin.ignore();
                getline(cin,text,'\n');
                XOR_decipher(text,secretletter,w);
            }
        }
        else if (operation == 10){
            if (oper2 == 1){
                cout << "Please enter the message you want to cipher: \n";
                cin.ignore();
                getline(cin,text);
                cout << rail_fence_cipher(text);
            }
            else if(oper2 == 2){
                cout << "Please enter the message you want to decipher: \n";
                cin.ignore();
                getline(cin,text);
                cout << rail_fence_decipher(text);
            }
        }
    }
    return 0;
}
string Affine_encryption(const string& string_e, int p, int q){
    string string2;
    int x;
    // Loop on each character in the message
    for(char i : string_e){
        // If the current character is a whitespace
        if(i == char(32)){
            // Add whitespace to string2
            string2 += char(32);
        }

            // If the current character is an integer
        else if(isdigit(i) == true){
            // Add this integer to string2
            string2  += i;
        }
        else{
            // Check if the letter is uppercase
            if (65 <= i && i <= 90) {
                // Calculate the variable x because(A=0, B=1, C=2,....)
                // if the letter is "C" --> x = 67(ascii of "C") - 65 --> x = 2
                x = i - 65;
                // Apply the function of encryption 'E(x) = (p*x + q) mod 26'
                // Then add 65 to get the ascii value
                // Add the new character to string2
                string2 += char((((p * x) + q) % 26) + 65);
            }
                // Check if the letter is lowercase
            else if(97 <= i && i <= 122){
                // Calculate the variable x because(a=0, b=1, c=2,....)
                // if the letter is "d" --> x = 100(ascii of "d") - 97 --> x = 3
                x = i - 97;
                // Apply the function of encryption 'E(x) = (p*x + q) mod 26'
                // Then add 97 to get the ascii value
                // Add the new character to string2
                string2 += char((((p * x) + q) % 26) + 97);
            }
            else{
                // This mean that the character is '-', '.', '{', etc...
                // Add this character to string2
                string2 += i;
            }
        }
    }
    return string2;
}

string Affine_decryption(const string& string_d, int m, int n){
    string string2;
    int y;
    // Loop on each character in the message
    for(char i : string_d){
        // If the current character is a whitespace
        if(i == char(32)){
            // Add whitespace to string2
            string2 += char(32);
        }
            // If the current character is an integer
        else if(isdigit(i) == true){
            // Add this integer to string2
            string2  += i;
        }

        else{
            // Check if the letter is uppercase
            if(65 <= i && i <= 90) {
                // Calculate the variable x because(A=0, B=1, C=2,....)
                // if the letter is "C" --> y = 67(ascii of "C") - 65 --> y = 2
                y = i - 65;
                // Apply the function of encryption 'D(x) = ((m(y - n) mod 26) + 26) mod 26'
                // Then add 65 to get the ascii value
                // Add the new character to string2
                string2 += char(((((m * (y - n)) % 26)+26)%26) + 65);
            }
                // Check if the letter is lowercase
            else if(97 <= i && i <= 122){
                // Calculate the variable x because(a=0, b=1, c=2,....)
                // if the letter is "d" --> y = 100(ascii of "d") - 97 --> y = 3
                y = i - 97;
                // Apply the function of encryption 'D(x) = ((m(y - n) mod 26) + 26) mod 26'
                // Then add 97 to get the ascii value
                // Add the new character to string2
                string2 += char(((((m * (y - n)) % 26)+26)%26) + 97);
            }
            else{
                // This mean that the character is '-', '.', '{', etc...
                // Add this character to string2
                string2 += i;
            }
        }
    }
    return string2;
}
bool check_key(string key){ // Simple Substitution Cipher
    if(key[0] == key[1] || key[0] == key[2] || key[0] == key[3] || key[0] == key[4] || key[1] == key[2] || key[1] == key[3]
       || key[1] == key[4] || key[2] == key[3] || key[2] == key[4] || key[3] == key[4]) {
        return false;
    }
    return true;
}

void simple_substitution_encryption(string& compare){
    string msg, n_msg;

    cout << "Dear user enter a message to cipher: " << endl;
    cin.ignore();
    getline(cin , msg, '\n');
    transform(msg.begin(), msg.end(), msg.begin(), ::tolower);
    for(char i : msg){
        if(i == char(32)){
            n_msg += char(32);
        }
        else if(isdigit(i)){
            n_msg += i;
        }
        else if(i >= 97 && i <= 112){
            n_msg += compare[i - 97];
        }
        else{
            n_msg += i;
        }
    }
    cout << "Message after ciphering is: " << n_msg << endl;
}

void simple_substitution_decryption(string& compare){
    string msg, n_msg;
    cout << "Dear user enter a message to decipher: " << endl;
    cin.ignore();
    getline(cin , msg, '\n');
    transform(msg.begin(), msg.end(), msg.begin(), ::tolower);
    for(char i : msg){
        if(i == char(32)){
            n_msg += char(32);
        }
        else if(isdigit(i)){
            n_msg += i;
        }
        else if(i >= 97 && i <= 112){
            int ind = compare.find(i);
            n_msg += char(ind + 97);
        }
        else{
            n_msg += i;
        }
    }
    cout << "Message after deciphering is: "<< n_msg << endl;
}

string key_valid(){ // Polybius Cipher
    string key;
    cout << "Please enter a five digit key that will be used to cipher and decipher: ";
    cin >> key;
    cout << '\n';
    while(key.length() > 5){
        cout << "Please enter a five digit key that will be used to cipher and decipher: ";
        cin >> key;
        cout << '\n';
    }
    for(int i=0;i<5;i++){
        while (!isdigit(key[i])){
            cout << "Please enter a five digit key that will be used to cipher and decipher: ";
            cin >> key;
            cout << '\n';
        }
    }
    return key;
}

void polybius_encryption(string key) {
    char table[5][5] = {{'A', 'B', 'C', 'D', 'E'},
                        {'F', 'G', 'H', 'I', 'K'},
                        {'L', 'M', 'N', 'O', 'P'},
                        {'Q', 'R', 'S', 'T', 'U'},
                        {'V', 'W', 'X', 'Y', 'Z'}};
    string msg, n_msg;
    cout << "Please enter a message to encrypt: ";
    cin.ignore();
    getline(cin, msg, '\n');
    cout << '\n';
    msg.erase(std::remove_if(msg.begin(), msg.end(), ::isspace), msg.end());
    transform(msg.begin(), msg.end(), msg.begin(), ::toupper);
    for(char i : msg){
        if(i == 'I'){
            n_msg += key[1];
            n_msg += key[3];
        }
        else{
            for (int j = 0; j < 5; ++j) {
                for (int k = 0; k < 5; ++k) {
                    if (i == table[j][k]) {
                        n_msg += key[j];
                        n_msg += key[k];
                    }
                }
            }
        }
    }
    cout << "Message after ciphering is: " << n_msg;
}

bool is_valid(string msg, string key){ // Polybius Cipher
    for(char i : msg){
        if(i != key[0] && i != key[1] && i != key[2] && i != key[3] && i != key[4]){
            return false;
        }
    }
    return true;
}


void polybius_decryption(string key){
    char table[5][5] = {{'A', 'B', 'C', 'D', 'E'},
                        {'F', 'G', 'H', 'I', 'K'},
                        {'L', 'M', 'N', 'O', 'P'},
                        {'Q', 'R', 'S', 'T', 'U'},
                        {'V', 'W', 'X', 'Y', 'Z'}};
    string msg, n_msg;
    int r, c;
    cout << "Please enter a message to decrypt: ";
    cin.ignore();
    getline(cin, msg, '\n');
    cout << '\n';
    while(msg.length() % 2 != 0 || !is_valid(msg, key)){
        cout << "Please enter a valid message to decrypt: ";
        cin.ignore();
        getline(cin, msg, '\n');
        cout << '\n';
    }
    cout << '\n';
    for(int i = 0;i < msg.length();i += 2){
        for(int j = 0;j < 5;++j){
            if(key[j] == msg[i]){
                r = j;
            }
            if(key[j] == msg[i+1]){
                c = j;
            }
        }
        n_msg += table[r][c];
    }
    cout << "Message after decryption is: " << n_msg;
}

void morse_cipher(string s){
    string ciphered = "";
    for (char letter:s){
        if (letter == ' '){
            ciphered += "  ";
            continue;
        }
        ciphered += cipher[tolower(letter)];
        ciphered += ' ';
    }
    cout << ciphered << endl;
}
void morse_decipher(string s){
    string deciphered = "",token;
    istringstream input("");
    input.str(s);
    input >> token;
    while(input){
        for(char i = 97;i < 124;i++) {
            if (cipher[i] == token){
                cout << i;
            }
        }
        input >> token;
    }
    cout << endl;
}
string rail_fence_cipher(string s){
    string s1="",s2="",s3="",s4="";
    for (int i = 0;i < s.size();i++){
        if (s[i] != ' '){
            s1 += s[i];
        }
    }
    for (int i = 0;i < s1.size();i++){
        if (i % 4 == 0){
            s2 += s1[i];
            continue;
        }
        else if (i % 2 == 1){
            s3 += s1[i];
        }
        else if(i % 2 == 0){
            s4 += s1[i];
        }
    }
    return s2+s3+s4;
}
string rail_fence_decipher(string s){
    string decrypted = "";
    char rail[s.size()][3];
    memset(rail,'_',s.size() * 3);
    int i = 0;
    for (int j = 0;j < s.size();j+=4){
        rail[j][0] = s[i];
        i++;
    }
    for (int j = 1;j < s.size();j+=2){
        rail[j][1] = s[i];
        i++;
    }
    for (int j = 2;j < s.size();j+=4){
        rail[j][2] = s[i];
        i++;
    }
    for (int i = 0;i < s.size();i++){
        for (int j = 0;j < 3;j++){
            if(rail[i][j] != '_'){
                decrypted += rail[i][j];
            }
        }
    }

    return decrypted;
}
int hex_to_dec(string hexaText){ // Function to convert hexadecimal to decimal
    int base = 1;
    int dec = 0;
    for (int i = 1;i >= 0;i--){
        // loop over m and check value of each character and add it to its decimal equivalent
        if(hexaText[i] >= '0' && hexaText[i] <= '9'){
            dec += (hexaText[i] - 48) * base;
            base *= 16;
        }
        else if (hexaText[i] >= 'a' && hexaText[i] <= 'f'){
            dec += (hexaText[i] - 87) * base;
            base *= 16;
        }
    }
    return dec;
}
void XOR_cipher(string textToEncrypt,char secretLetter){
    // Function to encrypt the message,m is the string which the user entered and p is the secret letter
    string encryptedText = "";
    for (int i = 0;i < textToEncrypt.size();i++){
        char add = textToEncrypt[i] ^ secretLetter;
        encryptedText += add; // XOR each character with the secret letter
    }

    cout << "Ciphered text: " << encryptedText << endl;
    cout << "Ciphered in hexa: ";
    for (int i = 0;i < encryptedText.size();i++){
        if (int(encryptedText[i]) <= 15){
            cout << 0 << hex << int(encryptedText[i]);
            // If the number is less than or equal 15 then it will take one number only in hexa
            // So, I added zero at the beginning
        }
        else{
            cout << hex << int(encryptedText[i]);// Print the hexadecimal equivalent to the ciphered text
        }
    }
    cout << "\n";
}
void XOR_decipher(string textToDecrypt,char secretLetter,int operation){
    /*
     Function to decrypt the message,m is either in hexa or text, p is the secret letter
     and w to choose either you want to enter a hexadecimal value or text
     */
    string decryptedText = "";
    if (operation == 1){
        for (int i = 0;i < textToDecrypt.size();i++){
            decryptedText += (textToDecrypt[i] ^ secretLetter);
            // XOR each letter of the encrypted text to get the decrypted text
        }
    }
    else if (operation == 2){
        for (int i = 0;i < textToDecrypt.size();i += 2){
            string part = textToDecrypt.substr(i,2);
            // slice the string so that you can take each two hexadecimal characters as one number
            int dec = hex_to_dec(part);
            decryptedText += (char)(secretLetter ^ dec);
            // XOR the decimal(ASCII) value of encrypted text to get decrypted text
        }
    }
    cout << decryptedText << endl;
}