#include "App.h"
#include"MainFram.h"

wxIMPLEMENT_APP(App);

bool App::OnInit() {
    MainFram* window = new MainFram("CBIR Project ");
    window->Show();
    return true;
}