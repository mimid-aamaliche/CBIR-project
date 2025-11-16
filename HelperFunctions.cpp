#include "HelperFunctions.h"
#include <vector>
#include<string>
#include"MyStringLib.h"



double* HelperFunctions::splitStringIntoDoubleArray(std::string cldVectorPart) {


    std::vector<std::string> cldComponents = clsString::SplitString(cldVectorPart, " ");
    int vectorlength = cldComponents.size();
    double* cldVector = (double*)malloc(sizeof(double) * vectorlength);



    for (int i = 0; i < vectorlength; i++) {

        cldVector[i] = std::stod(cldComponents[i]);

    }
    return cldVector;


}

