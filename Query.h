#pragma once
#include<iostream>
#include<vector>




class Query
{

private:


   

    static double calculateDistance(double* cld1, double* cld2, int length = 768);



public:

    struct imageRecord {

        imageRecord(std::string path, double _distance) {
            imagepath = path;
            distance = _distance;
        }
        std::string imagepath;
        double distance;
    };


	static std::vector<imageRecord> QueryNearestImages(std::string imagepath);

};

