#pragma once

#include <cmath>
#include <fftw3.h>
#include <iostream>
#include <fstream>
#include<string>
#include"MyStringLib.h"
#include <filesystem>

#include <tuple>
#include<vector>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif



class cld
{


	static std::tuple<double, double, double> ConvertToYCbCrColorSpace(double r, double g, double b);
	static double* getDCTOfBlock(double* matrix, int width, int height);
	static std::tuple<double*, double*, double*> GetDctOfImage(unsigned char* const imagedata, int width, int height, int channels, const int NumberOfRowsInBlock, const int NumberOfColumnsInBlock);

public: 
	static double* find(std::string imagepath);



};

