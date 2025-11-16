#include "Query.h"
#include "cld.h"
#include"HelperFunctions.h"




double Query::calculateDistance(double* cld1, double* cld2, int length) {


    double sum = 0.0;
    for (int i = 0; i < length; i++) {
        double diff = cld1[i] - cld2[i];
        sum += diff * diff;
    }
    return sum; // <- squared Euclidean distance

}




std::vector<Query::imageRecord> Query::QueryNearestImages(std::string imagepath) {

    //we compute the cld file for the image 
    //we compare it with the cldVectors in our db file 
    //comparing using distance or angle ....

    vector<imageRecord> NearestImages;

    //we get the nearest image and copy its content in the project/Result folder


    double* CLDVector_queryimage = cld::find(imagepath.c_str());

    if (!CLDVector_queryimage) {
        return{};
    }

    //read from db file 

    std::ifstream file("projectDb.txt");

    if (!file.is_open()) {
        cout << "failed to open db file " << endl;
        return{};
    }

    std::string line;
    while (std::getline(file, line)) {

        //here we do our comparison works
        //we fetch --> find distance between tow images --> compare it to the last 4 we stored
        //--> if its less store it and drop the last one


        vector<std::string> imageRecordElements = clsString::SplitString(line, "#//#");

        double* currentimagecld = HelperFunctions::splitStringIntoDoubleArray(imageRecordElements[1]);
        double distance = calculateDistance(CLDVector_queryimage, currentimagecld);

        NearestImages.push_back(imageRecord(imageRecordElements[0], distance));


        free(currentimagecld);

    }


    free(CLDVector_queryimage);






    return NearestImages;

}
