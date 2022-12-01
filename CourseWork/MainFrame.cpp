#include "MainFrame.h"
#include <wx/wx.h>

MainFrame::MainFrame(const wxString& title): wxFrame(nullptr, wxID_ANY, title)
{
	wxPanel* panel = new wxPanel(this);

	wxButton* button = new wxButton(panel, wxID_ANY, "Button", wxPoint(150, 50), wxSize(100, 35));

	wxCheckBox* checkbox = new wxCheckBox(panel, wxID_ANY, "Checkbox", wxPoint(550, 55));

	wxStaticText* text = new wxStaticText(panel, wxID_ANY, "Static Text", wxPoint(120, 150));

	wxTextCtrl* textInput = new wxTextCtrl(panel, wxID_ANY, "Text", wxPoint(500, 145), wxSize(200, -1));
}
