#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <cstdlib>
#include <algorithm>


int k;
std::vector <std::string> kVector;
std::vector <std::string> filteredKVector;
std::vector <std::string> reverseComplementK;

void DnaCheck(std::string dna);
void KStore(std::string dna);
void FilterDna(std::string dna);
void CountDna(std::string dna);
void ReverseComplement();


int main(){
    std::string dna;
    int option;
    bool run1 = true, run2 = true;
    char runInput;

    while(run1){
        kVector.clear();
        filteredKVector.clear();
        reverseComplementK.clear();

        std::cout << "Please input the DNA sequence: ";
        std::cin >> dna;

        for(int i = 0; i < dna.length(); i++){
            dna[i] = std::toupper(dna[i]);
        }

        DnaCheck(dna);

        std::cout << "Please input the k-mers: ";
        std::cin >> k;
        if(std::cin.fail()) {std::cout << "Invalid Input! (ONLY INTEGERS)"; return 0;}

        KStore(dna);
        FilterDna(dna);
        
        run2 = true;
        while (run2){
            std::cout << "\nThe DNA sequence: " << dna << std::endl;
            std::cout << "Options:\n[1] Count each substrings with length k\n[2] Display the reverse complement along with it's original k-mers\nOption: ";
            std::cin >> option;
            std::cout << "\n";

            switch(option){
                case 1: CountDna(dna); break;
                case 2: ReverseComplement(); break;
                default: std::cout << "Invalid Input! (1/2)"; return 0;
            }

            std::cout << "\nOptions:\n[1] Input another dna\n[2] Check the existing DNA again\n[3] End the program\nOption: ";
            std::cin >> option;
            std::cout << "\n";
            switch(option){
                case 1: run2 = false; break;
                case 2: run2 = true; break;
                case 3: run1 = run2 = false; break;
                default: std::cout << "Invalid Input! (1/2/3)"; return 0;
            }
        }
    }

    std::cout << "Program Ended!";

    return 0;
}


void DnaCheck(std::string dna){
    for(int i = 0; i < dna.length(); i++){
        dna[i] = std::toupper(dna[i]);

        if(dna[i] != 'A' && dna[i] != 'T' && dna[i] != 'G' && dna[i] != 'C'){ 
            std::cout << "Invalid Input! (A/T/G/C)"; 
            exit(0);
        }
    }
}

void KStore(std::string dna){
    std::string tempString;
    for(int i = 0; i + k <= dna.length(); i++){
        tempString = dna.substr(i, k);
        kVector.push_back(tempString);

    }

    //for (std::string i : kVector) std::cout << i << std::endl;

}

// if(starting + length > lengthofDna) break;

void FilterDna(std::string dna){
    int tempInt = 0;

    for(int i = 0; i < kVector.size(); i++){
        bool store = true;

        for(int j = i+1; j < kVector.size(); j++){
            if(kVector[i] == kVector[j]){
                store = false;
                tempInt++;
                break;
            }
        }

        if(store) filteredKVector.push_back(kVector[i]);
    }

    std::rotate(filteredKVector.begin(), filteredKVector.end() - tempInt, filteredKVector.end());
}

void CountDna(std::string dna){
    for(int i = 0; i < filteredKVector.size(); i++){
        int tempInt = 0;

        for(int j = 0; j + k <= dna.length(); j++){
            if(filteredKVector[i] == dna.substr(j, k)) tempInt++;
        }

        std::cout << filteredKVector[i] << ": " << tempInt << "\n";
    }
}

void ReverseComplement(){
    reverseComplementK = filteredKVector;
    for(int i = 0; i < reverseComplementK.size(); i++){

        for(int h = k-1, j = 0; h >= 0 && j < k; h--, j++){
            reverseComplementK[i][j] = filteredKVector[i][h];
        }

    }

    for(int i = 0; i < reverseComplementK.size(); i++){
        for(int j = 0; j < k; j++)
            switch(reverseComplementK[i][j]){
                case 'A': reverseComplementK[i][j] = 'T'; break;
                case 'T': reverseComplementK[i][j] = 'A'; break;
                case 'G': reverseComplementK[i][j] = 'C'; break;
                case 'C': reverseComplementK[i][j] = 'G'; break;
            }
    }

    std::cout << "Original k along with it's reverse complement: \n";
    for(int i = 0; i < reverseComplementK.size(); i++){
        std::cout << filteredKVector[i] << " <-> " << reverseComplementK[i] << "\n";
    }
    
}