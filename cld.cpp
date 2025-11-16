

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION

#include "stb_image.h"
#include"stb_image_resize2.h"

#include "cld.h"





std::tuple<double, double, double> cld::ConvertToYCbCrColorSpace(double r, double g, double b) {

    double Y = 0.299 * r + 0.587 * g + 0.114 * b;
    double Cb = -0.168736 * r - 0.331264 * g + 0.5 * b + 128;
    double Cr = 0.5 * r - 0.418688 * g - 0.081312 * b + 128;
    return std::make_tuple(Y, Cb, Cr);
}

double* cld::getDCTOfBlock(double* matrix, int width, int height) {



    double* out = (double*)malloc(sizeof(double) * height * width);

    //this calculate the dct of the input using the fft approch 
    //wiche has a compleity of O(N^2log(n))
    //while the naive implimentation of the DCT is O(N^4) way slower for large matrices
    fftw_plan plan = fftw_plan_r2r_2d(height, width, matrix, out, FFTW_REDFT10, FFTW_REDFT10, FFTW_ESTIMATE);


    fftw_execute(plan);


    //deallocate data 
    fftw_destroy_plan(plan);

    return out;


}

std::tuple<double*, double*, double*> cld::GetDctOfImage(unsigned char* const imagedata, int width, int height, int channels, const int NumberOfRowsInBlock, const int NumberOfColumnsInBlock) {


    int Block_i = 0, Block_j = 0, CurrentIndexInsideTheBlock = 0, IndexOfCurrentDCTGenerated = 0;
    double NormFactor = 4.0 * NumberOfRowsInBlock * NumberOfColumnsInBlock;



    // in this function instead of deviding the image into 64 blocks 
    //we will devide it into multiple blocks of 8*8 pixel

    //first lets calculate how many block i will have 
    int NumberOfHorizantalBlocks = ceil((double)width / NumberOfColumnsInBlock);
    int NumberOfVerticalBlocks = ceil((double)height / NumberOfRowsInBlock);




    //we will devide the image into multiple 16*16 blocks 
    //and calculate the dct of each block 
    //_________________________________________________________________________________________________

    size_t DCTsize = (size_t)NumberOfHorizantalBlocks * NumberOfVerticalBlocks;
    double* Y_DCTs = (double*)malloc(sizeof(double) * DCTsize);
    double* Cb_DCTs = (double*)malloc(sizeof(double) * DCTsize);
    double* Cr_DCTs = (double*)malloc(sizeof(double) * DCTsize);

    if (!Y_DCTs || !Cb_DCTs || !Cr_DCTs) {
        // Handle allocation failure
        free(Y_DCTs);
        free(Cb_DCTs);
        free(Cr_DCTs);
        return std::make_tuple(nullptr, nullptr, nullptr);
    }


    //we gonna calculate the dct for each block for each channel 
    //so we need a way to store the block info
    size_t BlockSize = (size_t)NumberOfRowsInBlock * NumberOfColumnsInBlock;

    double* YchannelOfBlock = (double*)malloc(sizeof(double) * BlockSize);
    double* CbchannelOfBlock = (double*)malloc(sizeof(double) * BlockSize);
    double* CrchannelOfBlock = (double*)malloc(sizeof(double) * BlockSize);

    //handle the case where the allocation failed
    if (!YchannelOfBlock || !CbchannelOfBlock || !CrchannelOfBlock) {
        free(YchannelOfBlock);
        free(CbchannelOfBlock);
        free(CrchannelOfBlock);
        free(Y_DCTs);
        free(Cb_DCTs);
        free(Cr_DCTs);
        return std::make_tuple(nullptr, nullptr, nullptr);
    }




    for (Block_i = 0; Block_i < NumberOfVerticalBlocks; Block_i++) {
        for (Block_j = 0; Block_j < NumberOfHorizantalBlocks; Block_j++) {

            CurrentIndexInsideTheBlock = 0;

            for (int i = Block_i * NumberOfRowsInBlock; i < (Block_i + 1) * NumberOfRowsInBlock; i++) {

                for (int j = Block_j * NumberOfColumnsInBlock; j < (Block_j + 1) * NumberOfColumnsInBlock; j++) {

                    int index = (i * width + j) * channels;


                    std::tuple<double, double, double> ColorInYCbCrSpace = ConvertToYCbCrColorSpace(imagedata[index], imagedata[index + 1], imagedata[index + 2]);

                    YchannelOfBlock[CurrentIndexInsideTheBlock] = std::get<0>(ColorInYCbCrSpace);
                    CbchannelOfBlock[CurrentIndexInsideTheBlock] = std::get<1>(ColorInYCbCrSpace);
                    CrchannelOfBlock[CurrentIndexInsideTheBlock] = std::get<2>(ColorInYCbCrSpace);


                    //incriment 
                    CurrentIndexInsideTheBlock++;
                }

            }

            //one we have the colors of one block 
            //we calculate the dct of that block and store it 
            //and go for the next block


            double* temp = getDCTOfBlock(YchannelOfBlock, NumberOfColumnsInBlock, NumberOfRowsInBlock);
            Y_DCTs[IndexOfCurrentDCTGenerated] = temp[0] / NormFactor;
            free(temp);

            temp = getDCTOfBlock(CbchannelOfBlock, NumberOfColumnsInBlock, NumberOfRowsInBlock);
            Cb_DCTs[IndexOfCurrentDCTGenerated] = temp[0] / NormFactor;
            free(temp);


            temp = getDCTOfBlock(CrchannelOfBlock, NumberOfColumnsInBlock, NumberOfRowsInBlock);
            Cr_DCTs[IndexOfCurrentDCTGenerated] = temp[0] / NormFactor;
            free(temp);

            IndexOfCurrentDCTGenerated++;




        }


    }



    free(YchannelOfBlock);
    free(CbchannelOfBlock);
    free(CrchannelOfBlock);


    return std::make_tuple(Y_DCTs, Cb_DCTs, Cr_DCTs);








}






double * cld::find(std::string imagepath) {

    int width, height, channels;

    // Load image
    unsigned char* OriginalImage = stbi_load(imagepath.c_str(), &width, &height, &channels, 0);
    if (!OriginalImage) {
        std::cerr << "Failed to load image: " << imagepath << std::endl;
        return nullptr;
    }

    std::cout << "Image loaded: " << imagepath << "\n";
    std::cout << "Width: " << width << ", Height: " << height << ", Channels: " << channels << "\n";



    //__________________________resise image to 512*512____________________________________________________

    //allocate data for the image
    size_t output_size = (size_t)512 * 512 * channels;
    unsigned char* data = (unsigned char*)malloc(sizeof(unsigned char) * output_size);

    if (!data) {
        fprintf(stderr, "Failed to allocate memory for resized image\n");
        free(OriginalImage);
        exit(1);
    }
    stbir_resize_uint8_srgb(OriginalImage, width, height, 0,
        data, 512, 512, 0,
        (stbir_pixel_layout)channels);



    //___________________________________________________________________________________________________

    //its best to use this instead of the normal free
    stbi_image_free(OriginalImage);

    int NumberOfRowsInBlock = 32;
    int NumberOfColumnsInBlock = 32;


    std::tuple<double*, double*, double*> DCTOfChannels = GetDctOfImage(data, 512, 512, channels, NumberOfRowsInBlock, NumberOfColumnsInBlock);
    //free resized image
    free(data);



    //now we need to map the 3 matrices into one vector

    int channelDCTLength = 256;
    double* Y_DCTs = std::get<0>(DCTOfChannels);
    double* Cb_DCTs = std::get<1>(DCTOfChannels);
    double* Cr_DCTs = std::get<2>(DCTOfChannels);


    // Check if DCT extraction failed
    if (!Y_DCTs || !Cb_DCTs || !Cr_DCTs) {
        free(Y_DCTs);
        free(Cb_DCTs);
        free(Cr_DCTs);

        return nullptr;
    }




    //the vector length will be the number of block * 3
    //numberof blocks is (512/NumberOfRowsInBlock)*(512/NumberOfColumnsInBlock) in our case is 768

    double* cldVector = (double*)malloc(sizeof(double) * 768);


    if (!cldVector) {
        free(Y_DCTs);
        free(Cb_DCTs);
        free(Cr_DCTs);

        return nullptr;



    }



    for (int i = 0; i < channelDCTLength; i++) {

        cldVector[i] = Y_DCTs[i];
    }

    for (int i = 0; i < channelDCTLength; i++) {

        cldVector[channelDCTLength + i] = Cb_DCTs[i];
    }

    for (int i = 0; i < channelDCTLength; i++) {

        cldVector[2 * channelDCTLength + i] = Cr_DCTs[i];
    }


    free(Y_DCTs);
    free(Cb_DCTs);
    free(Cr_DCTs);


    return cldVector;







}
