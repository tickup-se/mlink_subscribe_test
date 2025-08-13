//
// Created by Anders Cedronius on 2025-08-13.
//

#include <iostream>
#include <map>
#include <fstream>


int main(int argc, char *argv[]) {

    //Get the program arguments
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <FILE_NAME_1> <FILE_NAME_2>" << std::endl;
        return EXIT_FAILURE;
    }

    //get first filename
    std::string lFileName1 = argv[1];
    //get the second filename
    std::string lFileName2 = argv[2];

    //read first file data. Each line contains a string. The string is put in a std::map key. the second value is a bool placeholder
    std::map<std::string, bool> lFile1Data;
    std::ifstream lFile1(lFileName1);
    if (lFile1.is_open()) {
        std::string lLine;
        while (std::getline(lFile1, lLine)) {
            lFile1Data[lLine] = false;
        }
    } else {
        std::cout << "error opening file: " << lFileName1 << std::endl;
        return EXIT_FAILURE;
    }
    lFile1.close();

    //read second file data. Each line contains a string. The string is put in a std::map key. the second value is a bool placeholder
    std::map<std::string, bool> lFile2Data;
    std::ifstream lFile2(lFileName2);
    if (lFile2.is_open()) {
        std::string lLine;
        while (std::getline(lFile2, lLine)) {
            lFile2Data[lLine] = false;
        }
    } else {
        std::cout << "error opening file: " << lFileName2 << std::endl;
        return EXIT_FAILURE;
    }
    lFile2.close();

    std::cout << "file 1: " << lFile1Data.size() << " lines" << std::endl;
    std::cout << "file 2: " << lFile2Data.size() << " lines" << std::endl;

    //compare the data lFile1Data compared to lFile2Data. create new maps containing
    //the data that's missing in lFile2Data but also if something in lFile2Data is not existing in lFile1Data
    std::map<std::string, bool> lFile1DataMissingInFile2;
    std::map<std::string, bool> lFile2DataMissingInFile1;
    for (auto &rFile1Data : lFile1Data) {
        if (lFile2Data.find(rFile1Data.first) == lFile2Data.end()) {
            lFile1DataMissingInFile2[rFile1Data.first] = true;
        }
    }
    for (auto &rFile2Data : lFile2Data) {
        if (lFile1Data.find(rFile2Data.first) == lFile1Data.end()) {
            lFile2DataMissingInFile1[rFile2Data.first] = true;
        }
    }

    std::cout << lFile1DataMissingInFile2.size() << " missing in file 2" << std::endl;
    std::cout << lFile2DataMissingInFile1.size() << " missing in file 1" << std::endl;

    //output the data for the missing entrys
    std::cout << "missing in file 2:" << std::endl;
    for (auto &rFile1DataMissingInFile2 : lFile1DataMissingInFile2) {
        std::cout << rFile1DataMissingInFile2.first << std::endl;
    }
    std::cout << std::endl << "missing in file 1:" << std::endl;
    for (auto &rFile2DataMissingInFile1 : lFile2DataMissingInFile1) {
        std::cout << rFile2DataMissingInFile1.first << std::endl;
    }

    return 0;
}
