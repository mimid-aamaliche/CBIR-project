#include "FileOperation.h"
#include <fstream>



void FileOperation::WriteToStarge(std::string imagepath, const double* cld, int cldLength, const char* seperator) {


    std::ofstream dbFile("projectDb.txt", std::ios::app);

    if (dbFile.is_open()) {

        dbFile << imagepath << seperator;
        for (int i = 0; i < cldLength; i++)
            dbFile << cld[i] << " ";

        dbFile << "\n";


        dbFile.close();


    }
    else {

        std::cerr << "Error: Unable to open db file." << std::endl;
        exit(1);

    }





}

