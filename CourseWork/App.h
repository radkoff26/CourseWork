#pragma once
#include <wx/wx.h>

class App : public wxApp {
private:
	wxFrame* currentFrame;
public:
	bool OnInit();
	void switchToFrame(wxFrame* frame);
};
