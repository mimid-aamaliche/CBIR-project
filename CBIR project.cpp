//// CBIR project.cpp : This file contains the 'main' function. Program execution begins and ends there.
////
////
//
//#include <cmath>
//#include <fftw3.h>
//#include <iostream>
//#include <fstream>
//#include<string>
//#include"MyStringLib.h"
//#include <filesystem>
//
//#include <tuple>
//#include<vector>
//
//#include"cld.h"
//
//namespace fs = std::filesystem;
//
//
//struct imageRecord {
//
//    imageRecord(std::string path, double _distance) {
//        imagepath = path;
//        distance = _distance;
//    }
//    std::string imagepath;
//    double distance;
//};
//
//
//double* splitStringIntoDoubleArray(std::string cldVectorPart) {
//
//
//    std::vector<std::string> cldComponents = clsString::SplitString(cldVectorPart, " ");
//    int vectorlength = cldComponents.size();
//    double* cldVector = (double*)malloc(sizeof(double) * vectorlength);
//
//    
//
//    for (int i = 0; i < vectorlength; i++) {
//
//        cldVector[i] = std::stod(cldComponents[i]);
//
//    }
//    return cldVector;
//
//
//}
//
//
//static void WriteToStarge(std::string imagepath,const double * cld ,int cldLength ,const char* seperator="#//#") {
//
//
//    std::ofstream dbFile("projectDb.txt",std::ios::app);
//
//    if (dbFile.is_open()) {
//
//        dbFile << imagepath << seperator;
//        for (int i = 0; i < cldLength; i++)
//            dbFile << cld[i] << " ";
//       
//        dbFile << "\n";
//
//
//        dbFile.close();
//
//
//    }
//    else {
//
//        std::cerr << "Error: Unable to open db file." << std::endl;
//        exit(1);
//
//    }
//
//
//
//
//
//}
//
//
//double calculateDistance(double * cld1, double* cld2, int length = 768) {
//
//
//    double sum = 0.0;
//    for (int i = 0; i < length; i++) {
//        double diff = cld1[i] - cld2[i];
//        sum += diff * diff;
//    }
//    return sum; // <- squared Euclidean distance
//
//}
//
//
//
//static void Train(std::string training_images_Dir) {
//    //here we go throght the images folder
//    //and for each image we calculate the cld vector and store in the db file
//
//
//
//    for (const auto& entry : fs::directory_iterator(training_images_Dir)) {
//        std::cout << entry.path() << std::endl;
//
//        std::string ext = entry.path().extension().string();
//
//        if (ext == ".png" || ext == ".jpg" || ext == ".bmp" || ext == ".jpeg") {
//
//            double* CLDVector = cld::find(entry.path().string().c_str());
//            //store in db file with the image path 
//            //in this format image path Seperator CLDvector 
//
//            WriteToStarge(entry.path().string(), CLDVector, 768);
//
//
//            free(CLDVector);
//        }
//
//
//
//
//
//    }
//        
//
//
//
//
//}
//
//
//
//static vector<imageRecord> QueryNearestImages(std::string imagepath) {
//
//    //we compute the cld file for the image 
//    //we compare it with the cldVectors in our db file 
//    //comparing using distance or angle ....
//
//    vector<imageRecord> NearestImages;
//
//    //we get the nearest image and copy its content in the project/Result folder
//
//
//    double* CLDVector_queryimage = cld::find(imagepath.c_str());
//
//    if (!CLDVector_queryimage) {
//        return{};
//    }
//
//    //read from db file 
//
//    std::ifstream file("projectDb.txt");
//
//    if (!file.is_open()) {
//        cout << "failed to open db file " << endl;
//        return{};
//    }
//
//    std::string line;
//    while (std::getline(file, line)) {
//
//        //here we do our comparison works
//        //we fetch --> find distance between tow images --> compare it to the last 4 we stored
//        //--> if its less store it and drop the last one
//
//
//        vector<std::string> imageRecordElements = clsString::SplitString(line, "#//#");
//
//        double* currentimagecld = splitStringIntoDoubleArray(imageRecordElements[1]);
//        double distance = calculateDistance(CLDVector_queryimage, currentimagecld);
//
//        NearestImages.push_back(imageRecord(imageRecordElements[0], distance));
//
//
//        free(currentimagecld);
//
//    }
//
//
//    free(CLDVector_queryimage);
//
//    
//    
//
//
//
//    return NearestImages;
//
//}
//
//
//int main() {
//
//
//
//
//    //-------------------------------------------Training workflow  
//
//    //first access the folder of the training images 
//
//
//    //and send each image path to the Calculate cldVectorOfImage
//
//
//    //inside the cldVectorOfImage we *load the image
//    //                               *image partionning into an 8*8 pixel blocks 
//    //                               *convert from rpg to YCbCr color space
//    //                               *calculate DST For each color channel in each block
//    //                               *Quentization :  bisacly take the dc value of each block of the dct coefficients
//    //                               *return the vector of those DCs
//
//
//    //then we store the vector of the image with the image path in a db file
//    
//    //-------------------------------------------query workflow
//    
//
//    //load the query image 
//    //compute the cld vector of the image 
//    //compare it to the cldVectors in our db file 
//    //find the closest ones and return there paths
//    //then we take those path and copy the images into our result folder in our project 
//    //naming the nearest math M1
//
//
//
//    string trainingImagesPath = "A:\\MyUploads\\dataset\\";
//    const char* queryFilename = "A:\\MyUploads\\dataset\\628.jpg";
//
//    ////clean training directory
//    //if (fs::exists("projectDb.txt"))
//    //    fs::remove_all("projectDb.txt");
//
//
//    //cout << "=== Training phase started ===" << endl;
//
//    //Train(trainingImagesPath);
//
//    //cout << "=== Training phase completed ===" << endl;
//    //cout << "Database saved to projectDb.txt" << endl;
//
//    //-------------------------------------------
//    // Query workflow
//    //-------------------------------------------
//    // Now we take a query image, compute its CLD vector,
//    // and compare it with all stored vectors in the database.
//
//    cout << "\n=== Query phase started ===" << endl;
//    cout << "Query image: " << queryFilename << endl;
//
//    vector<imageRecord> nearestList = QueryNearestImages(queryFilename);
//
//    if (nearestList.empty()) {
//        cerr << "No similar images found or database empty." << endl;
//        return 1;
//    }
//
//    // Sort by ascending distance (smallest = most similar)
//    sort(nearestList.begin(), nearestList.end(),
//        [](const imageRecord& a, const imageRecord& b) { return a.distance < b.distance; });
//
//    // Display top results
//    cout << "\n=== Nearest Images ===" << endl;
//    for (size_t i = 0; i < nearestList.size(); ++i) {
//        cout << "Match " << (i + 1) << ": " << nearestList[i].imagepath
//            << " | Distance: " << nearestList[i].distance << endl;
//    }
//
//    cout << "\n=== Query completed successfully ===" << endl;
//
//    //-------------------------------------------
//    // Optionally copy results to a folder
//    //-------------------------------------------
//    // You can create a Result/ directory in your project folder and copy images there.
//   
//    if (fs::exists("Results"))
//        fs::remove_all("Results");
//
//    fs::create_directories("Results");
//    for (size_t i = 0; i < 5; ++i) {
//        fs::path src = nearestList[i].imagepath;
//        fs::path dst = fs::path("Results") / ("M" + to_string(i+1) + src.extension().string());
//        try {
//            fs::copy_file(src, dst, fs::copy_options::overwrite_existing);
//        } catch (const fs::filesystem_error& e) {
//            cerr << "Failed to copy " << src << ": " << e.what() << endl;
//        }
//    }
//    
//
//    return 0;
//}
//
//












































//static std::tuple<double*, double*, double*> AvgYCbCrMap(unsigned char* const imagedata,int width ,int height , int channels) {
//
//
//        
//    int NewNumberOfRows = ceil((double)height / 8);
//    int NewNumberOfColumns = ceil((double)width / 8);
//
//    //allocate data for the image
//    size_t output_size = (size_t)NewNumberOfColumns * 8 * NewNumberOfRows * 8 * channels;
//    unsigned char* data = (unsigned char* )malloc(sizeof(unsigned char) * output_size);
//
//    if (!data) {
//        fprintf(stderr, "Failed to allocate memory for resized image\n");
//        exit(1);
//    }
//
//    //resize the image to the size (NewNumberOfRows*8,NewNumberOfColumns*8)
//
//    stbir_resize_uint8_srgb(imagedata, width, height, 0,
//        data, NewNumberOfColumns * 8, NewNumberOfRows * 8, 0, (stbir_pixel_layout)channels);
//
//
//    //now we need a way to calculate the avg for each block and store it on the array 
//
//
//    int CurrentBlockICords = 0, CurrentBlockJCords = 0, sumR = 0, sumG = 0, sumB = 0;
//    double avgR = 0.0f, avgG = 0.0f, avgB = 0.0f;
//
//    //each block will have one average value per channel
//    //and we have 64 block 
//    size_t Averages_size = (size_t)64;
//    double * Y_Averages= (double*)malloc(sizeof(double) * Averages_size);
//    double * Cb_Averages = (double*)malloc(sizeof(double) * Averages_size);
//    double * Cr_Averages = (double*)malloc(sizeof(double) * Averages_size);
//
//
//    for (CurrentBlockICords=0; CurrentBlockICords < 8; CurrentBlockICords++) {
//        for (CurrentBlockJCords=0; CurrentBlockJCords < 8; CurrentBlockJCords++) {
//
//            sumR = 0;
//            sumG = 0;
//            sumB = 0;
//
//            for (int i = CurrentBlockICords * NewNumberOfRows; i < (CurrentBlockICords + 1) * NewNumberOfRows; i++) {
//
//                for (int j = CurrentBlockJCords * NewNumberOfColumns; j < (CurrentBlockJCords + 1) * NewNumberOfColumns; j++) {
//
//                    int index = (i * NewNumberOfColumns * 8 + j) * channels;
//                    sumR += (int)data[index + 0];//R channel
//                    sumG += (int)data[index + 1];//G channel
//                    sumB += (int)data[index + 2];//B channel
//
//                }
//
//            }
//
//
//            //I might convert to the YCbCr color space here and now 
//
//            avgR = (double)sumR / 64;
//            avgG = (double)sumG / 64;
//            avgB = (double)sumB / 64;
//
//            //Conversion
//
//
//            std::tuple<double, double, double> Converted = ConvertToYCbCrColorSpace(avgR, avgG, avgB);
//
//
//            int avgInde = (CurrentBlockICords * 8 + CurrentBlockJCords);
//
//            //Store Averages 
//            Y_Averages[avgInde] = std::get<0>(Converted);
//            Cb_Averages[avgInde] = std::get<1>(Converted);
//            Cr_Averages[avgInde] = std::get<2>(Converted);
//
//
//
//
//
//        }
//
//
//    }
//
//
//
//    free(data);
//
//
//    return std::make_tuple(Y_Averages, Cb_Averages, Cr_Averages);
//
//
//
//
//
//
//
//
//}









//
//int findCLD(std::string imagepath) {
//
//    int width, height, channels;
//
//    // Load image
//    unsigned char* data = stbi_load(imagepath.c_str(), &width, &height, &channels, 0);
//    if (!data) {
//        std::cerr << "Failed to load image: " << imagepath << std::endl;
//        return 1;
//    }
//
//    std::cout << "Image loaded: " << imagepath << "\n";
//    std::cout << "Width: " << width << ", Height: " << height << ", Channels: " << channels << "\n";
//
//
//
//    //Partionning the image into 8*8 blocks and finding the evg color for each block
//    //this will return a tuble of three pointers to 3 matrices
//    //first one for the Y channel matric
//    //second one for Cb channel and third one for Cr channel
//
//
//    std::tuple<double*, double*, double*> AvregesInNewColorSpace = AvgYCbCrMap(data, width, height, channels);
//
//
//    //now we calculate the DCT of the Avgs using fft(fast fourier transform) approch using the fftw library
//    //note we need to calculate it for each channel Y Cb Cr 
//
//    double* YchannelDCT = getDCT(std::get<0>(AvregesInNewColorSpace), 8, 8);
//    double* CbchannelDCT = getDCT(std::get<1>(AvregesInNewColorSpace), 8, 8);
//    double* CrchannelDCT = getDCT(std::get<2>(AvregesInNewColorSpace), 8, 8);
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//}
//


//flow of the program 
//while there is more images in the

