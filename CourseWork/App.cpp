#include "App.h"
#include "MainFrame.h"
#include <wx/wx.h>
#include <wx/xrc/xmlres.h>

wxIMPLEMENT_APP(App);

bool App::OnInit()
{
    switchToFrame(new MainFrame(this, {}, nullptr));
    return true;
}

void App::switchToFrame(wxFrame* frame)
{
    if (currentFrame != nullptr) {
        if (currentFrame->IsActive()) {
            currentFrame->Destroy();
        }
        delete[] currentFrame;
    }
    this->currentFrame = frame;
    this->currentFrame->SetClientSize(800, 600);
    this->currentFrame->Center();
    this->currentFrame->Show();
}
