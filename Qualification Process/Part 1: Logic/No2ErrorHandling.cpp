#include <iostream>
#include <string>
#include <bitset>


void ErrorReader(std::string binaryStr, int decimalInput);

int main(){
    int decimalInput;
    std::string binaryString;

    std::cout << "Input a decimal number: ";
    std::cin >> decimalInput;

    if(std::cin.fail()){std::cout << "Invalid Input! (Only integers)"; return 0;}

    binaryString = std::bitset<5>(decimalInput).to_string();
    ErrorReader(binaryString, decimalInput);

    return 0;
}


void ErrorReader(std::string binaryStr, int decimalInput){
    std::string outputString = "";
    
    std::string errorArray[5] = {"Container descent rate failure", "Science Payload descent rate failure", "Container position failure", 
        "Science Payload position failure", "Release failure"};

    for(int i = 0; i < binaryStr.size(); i++){
        if(binaryStr[i] == '1'){
            outputString = outputString + ", " + errorArray[i];
        }
    }

    std::cout << "Error code: <" << binaryStr << ">\n";

    if(decimalInput == 0){
        std::cout << "No error";
    } else if(decimalInput <= 31){
        outputString = outputString + ".";
        outputString.erase(0, 2);
        std::cout << outputString;
    } else if(decimalInput > 31){
        outputString = outputString + ".";
        outputString.erase(0, 2);
        std::cout << outputString; 
        std::cout << "\nWoah... there are some unknown warnings!";
    }

}

//For reference (This is to convert decimal to binary): https://www.geeksforgeeks.org/cpp/cpp-program-for-decimal-to-binary-conversion/