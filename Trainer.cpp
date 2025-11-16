#include "Trainer.h"
#include <filesystem>
#include <stdexcept> 
#include "FileOperation.h"
#include "cld.h"



Trainer::Trainer(std::string DataSetPath) noexcept(false) {

    if (!std::filesystem::exists(DataSetPath))
        throw new exception("Invalid DataSet Path !!!");


    this->_DataSetPath = DataSetPath;

}

bool Trainer::Train() {
    //here we go throght the images folder
    //and for each image we calculate the cld vector and store in the db file

    try {

        for (const auto& entry : std::filesystem::directory_iterator(this->_DataSetPath)) {
            std::cout << entry.path() << std::endl;

            std::string ext = entry.path().extension().string();

            if (ext == ".png" || ext == ".jpg" || ext == ".bmp" || ext == ".jpeg") {

                double* CLDVector = cld::find(entry.path().string().c_str());
                //store in db file with the image path 
                //in this format image path Seperator CLDvector 

                FileOperation::WriteToStarge(entry.path().string(), CLDVector, 768);


                free(CLDVector);
            }


        }


    }
    catch (const exception& ex) {

        return false;
    }

   
    return true;




}