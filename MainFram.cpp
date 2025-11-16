#include "MainFram.h"
#include <vector>
#include"Query.h"
#include"Trainer.h"



MainFram::MainFram(std::string Title) :wxFrame(NULL, wxID_ANY,Title, wxDefaultPosition, wxSize(600, 400)) 
{
	//Here we add our buttons and layots

    wxBoxSizer* MainSizer = new wxBoxSizer(wxVERTICAL);
   



    //set in up the layouts   



    //the training section
    wxBoxSizer * TrainingSectionSizer= new wxBoxSizer(wxHORIZONTAL);

    //inside the traing part will have a browse for dataset btn and train btn + textbox if the user want to type the path


    wxBoxSizer* TrainingbtnSizer = new wxBoxSizer(wxVERTICAL);
    wxTextCtrl* txtcDataSetPath = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(300, wxDefaultSize.y), 0, wxDefaultValidator, "Path");
    wxButton* btnBrowse = new wxButton(this, wxID_ANY, "Browse for DataSet path");
    wxButton* btnTrain = new wxButton(this, wxID_ANY, "Train");

    TrainingbtnSizer->Add(btnBrowse, 1,wxALL,5);
    TrainingbtnSizer->Add(btnTrain, 1,wxALL,5);

    TrainingSectionSizer->Add(TrainingbtnSizer,5, wxALL,5);
    TrainingSectionSizer->Add(txtcDataSetPath, 3, wxALIGN_CENTER | wxALL,10);



    //the training section
    wxBoxSizer* QuerySectionSizer = new wxBoxSizer(wxHORIZONTAL);

    //inside the traing part will have a browse for dataset btn and train btn + textbox if the user want to type the path


    wxBoxSizer* QuerybtnSizer = new wxBoxSizer(wxVERTICAL);
    wxTextCtrl* txtcImagePath = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(300, wxDefaultSize.y), 0, wxDefaultValidator, "Path");
    wxButton* btnBrowseForImage = new wxButton(this, wxID_ANY, "Browse for Query image path");
    wxButton* btnSearch = new wxButton(this, wxID_ANY, "Find Similare Images");

    QuerybtnSizer->Add(btnBrowseForImage, 1, wxALL, 5);
    QuerybtnSizer->Add(btnSearch, 1, wxALL, 5);

    QuerySectionSizer->Add(QuerybtnSizer, 5, wxALL, 5);
    QuerySectionSizer->Add(txtcImagePath, 3, wxALIGN_CENTER | wxALL, 10);





    //panel to display similare images

    wxPanel* plSimilareImages = new wxPanel(this);








    MainSizer->Add(TrainingSectionSizer,1);
    MainSizer->Add(QuerySectionSizer,1);

    MainSizer->Add(plSimilareImages,4,wxEXPAND|wxALL,10);














    ////test code
    //std::string trainingImagesPath = "A:\\MyUploads\\dataset\\";
    //const char* queryFilename = "A:\\MyUploads\\dataset\\628.jpg";


    //std::vector<Query::imageRecord> nearestList = Query::QueryNearestImages(queryFilename);

    //if (nearestList.empty()) {
    //    std::cerr << "No similar images found or database empty." << std::endl;
    //    exit(1);
    //}

    //// Sort by ascending distance (smallest = most similar)
    //sort(nearestList.begin(), nearestList.end(),
    //    [](const Query::imageRecord& a, const Query::imageRecord& b) { return a.distance < b.distance; });

    //// Display top results
    //for (size_t i = 0; i < 3; ++i) {

    //    

    //}






    this->SetSizer(MainSizer);


}