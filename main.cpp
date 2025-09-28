#include <iostream>
#include <string>


int main(){
    while (true) {
    std::cout << "Choose Your Option For Your Text File-\n";
    std::cout << "Type 1 To Encrypt\n";
    std::cout << "Type 2 To Decrypt\n";
    std::cout << "Type 3 To End Program\n";
    std::cout << "I Choose: ";
    int choice{0};
    std::cin >> choice;
        if (choice == 1) { //for encryption
            ;
        } else if (choice ==2) { //for decryption
            ;
        } else if (choice ==3) { //for ending program
            std::cout << "I'll miss you...\n";
            break;
        } 
        else { //for invalid input
            std::cout << "Pick 1, 2, or 3 dummy!\n";
        }    
    }

    return 0;
}
