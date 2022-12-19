#pragma once
#include <wx/wx.h>

class App : public wxApp {
public:
	~App() {
		if (currentFrame != nullptr) {
			if (currentFrame->IsActive()) {
				currentFrame->Close();
			}
		}
		delete[] currentFrame;
	}
	bool OnInit();
	void switchToFrame(wxFrame* frame);
private:
	wxFrame* currentFrame;
};
