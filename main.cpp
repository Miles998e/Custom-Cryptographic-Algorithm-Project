#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <array>
#include <algorithm>
#include <cctype>

std::string Encrypt(std::string line) { //encrypt function using in this order transposition, shifting, and then substitution
    std::string encrypted_line = line;
    for (size_t i = 0; i + 3 < encrypted_line.size(); i += 4) { // TRANSPOSITION-shifts group of characters every 4 indices starting from index 0 to last index of line   
        std::swap(encrypted_line[i], encrypted_line[i + 3]);
        std::swap(encrypted_line[i + 1], encrypted_line[i + 2]);
    }
    for (size_t i = 0; i < encrypted_line.size(); ++i) { // SHIFTING-shifts letters by (5* i + 2)
        char character = encrypted_line[i];
        int change_character_by_number = (5 * static_cast<int>(i) + 2) % 26;
        if (character >= 'A' && character <= 'Z') {
            int character_index = character - 'A';
            encrypted_line[i] = 'A' + (character_index + change_character_by_number) % 26;
        } else if (character >= 'a' && character <= 'z') {
            int character_index = character - 'a';
            encrypted_line[i] = 'a' + (character_index + change_character_by_number) % 26;
        }
    }
    std::vector<char> My_Alphabet_Mixed{'x', 'l', 'r', 'w', 'q', 'c', 'j', 'n', 'm', 'i', 'k', 'h', 'o', 'f', 'v', 'e', 'p', 'y', 's', 'd', 'z', 'b', 'a', 't', 'g', 'u'};
    for (size_t i = 0; i < encrypted_line.size(); ++i) { // SUBSTITUTION-substitutes letters with letters from my mixed alphabet of letters
        char character = encrypted_line[i];
        if (character >= 'A' && character <= 'Z') {
            int character_index = character - 'A';
            encrypted_line[i] = static_cast<char>(std::toupper(My_Alphabet_Mixed[character_index]));
        } else if (character >= 'a' && character <= 'z') {
            int character_index = character - 'a';
            encrypted_line[i] = My_Alphabet_Mixed[character_index];
        }
    }
    return encrypted_line;
}

std::string Decrypt(std::string line) { //decrypt function going opposite way of encrypting function
    std::string decrypted_line = line;
    std::vector<char> My_Alphabet_Mixed{'x','l','r','w','q','c','j','n','m','i','k','h','o','f','v','e','p','y','s','d','z','b','a','t','g','u'};
    for (size_t i = 0; i < decrypted_line.size(); ++i) { // UNDOES SUBSTITUTION
        char character = decrypted_line[i];
        if (character >= 'A' && character <= 'Z') {
            char lower = static_cast<char>(std::tolower(character));
            std::vector<char>::const_iterator iterator = std::find(My_Alphabet_Mixed.begin(), My_Alphabet_Mixed.end(), lower);
            if (iterator != My_Alphabet_Mixed.end()) {
                int character_index = static_cast<int>(iterator - My_Alphabet_Mixed.begin());
                decrypted_line[i] = 'A' + character_index;
            }
        } else if (character >= 'a' && character <= 'z') {
            std::vector<char>::const_iterator iterator = std::find(My_Alphabet_Mixed.begin(), My_Alphabet_Mixed.end(), character);
            if (iterator != My_Alphabet_Mixed.end()) {
                int character_index = static_cast<int>(iterator - My_Alphabet_Mixed.begin());
                decrypted_line[i] = 'a' + character_index;
            }
        }
    }
    for (size_t i = 0; i < decrypted_line.size(); ++i) { // UNDOES SHIFTING
        char character = decrypted_line[i];
        int change_character_by_number = static_cast<int>(((5 * i) + 2) % 26);

        if (character >= 'A' && character <= 'Z') {
            int character_index = character - 'A';
            decrypted_line[i] = 'A' + ((character_index - change_character_by_number + 26) % 26);
        } else if (character >= 'a' && character <= 'z') {
            int character_index = character - 'a';
            decrypted_line[i] = 'a' + ((character_index - change_character_by_number + 26) % 26);
        }
    }
    for (size_t i = 0; i + 3 < decrypted_line.size(); i += 4) { // UNDOES TRANSPOSITION
        std::swap(decrypted_line[i], decrypted_line[i + 3]);
        std::swap(decrypted_line[i + 1], decrypted_line[i + 2]);
    }
    return decrypted_line;
}

int main(){
    while (true) {
        std::cout << "Choose Your Option For Your Text File-\r\n";
        std::cout << "Type 1 To Encrypt\r\n";
        std::cout << "Type 2 To Decrypt\r\n";
        std::cout << "Type 3 To End Program\r\n";
        std::cout << "I Choose: ";
        int choice{0};
        std::cin >> choice;
        if (choice == 1) { //for encryption
            std::cout << "Enter Your Text File: \r\n";
            std::string unencrypted_file_name{""};
            std::cin >> unencrypted_file_name;
            if (unencrypted_file_name.size() < 4 || unencrypted_file_name.substr(unencrypted_file_name.size() - 4) != ".txt") { //checks if file is .txt
                std::cout << "Only Use Text Files. Retry.\r\n";
                continue;
            }
            std::ifstream file_text(unencrypted_file_name);
            if (!file_text) { //checks if file opens
                std::cout << "File Not Working. Retry.\r\n";
                continue;
            }
            std::string line{""};
            std::string encrypted_file_name{""};
            std::cout << "Enter name for the encrypted file: ";
            std::cin >> encrypted_file_name;
            std::ofstream encrypted_file(encrypted_file_name);
            if (!encrypted_file) { //checks if output file opens
                std::cout << "error\r\n";
                continue;
            }
            while (std::getline(file_text, line)) { 
                std::string encrypted_line = Encrypt(line);
                encrypted_file << encrypted_line << '\n';
            }
            std::cout << "Encrypted File Made " << encrypted_file_name << "\r\n";
        } else if (choice ==2) { //for decryption
            std::cout << "Enter Your Text File: \r\n";
            std::string encrypted_file_name{""};
            std::cin >> encrypted_file_name;
            if (encrypted_file_name.size() < 4 || encrypted_file_name.substr(encrypted_file_name.size() - 4) != ".txt") { //checks if file is .txt
                std::cout << "Only Use Text Files. Retry.\r\n";
                continue;
            }
            std::ifstream file_text(encrypted_file_name);
            if (!file_text) { //checks if file opens
                std::cout << "File Not Working. Retry.\r\n";
                continue;
            }
            std::string line{""};
            std::string decrypted_file_name{""};
            std::cout << "Enter name for the decrypted file: ";
            std::cin >> decrypted_file_name;
            std::ofstream decrypted_file(decrypted_file_name);
            if (!decrypted_file) { //checks if output file opens
                std::cout << "error.\r\n";
                continue;
            }
            while (std::getline(file_text, line)) { 
                std::string decrypted_line = Decrypt(line);
                decrypted_file << decrypted_line << '\n';
            }
            std::cout << "Decrypted File Made " << decrypted_file_name << "\r\n";
        } else if (choice ==3) { //for ending program
            std::cout << "Ending Program.\r\n";
            break;
        } 
        else { //for invalid input
            std::cout << "Pick 1, 2, or 3. Retry.\r\n";
        }    
    }
    return 0;
}
