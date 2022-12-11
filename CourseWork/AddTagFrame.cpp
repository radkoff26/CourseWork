#include "AddTagFrame.h"
#include "MainFrame.h"
#include <vector>
#include <wx/wx.h>
#include <wx/splitter.h>
#include <wx/html/htmlwin.h>
#include "Repository.h"
#include "Utils.h"

AddTagFrame::AddTagFrame(App* app, wxWindow* parent, const wxString& title) : wxFrame(parent, wxID_ANY, title)
{
	this->app = app;
	this->repository = new Repository();
	this->panel = new wxPanel(this, wxID_ANY, wxPoint(0, 0), wxSize(800, 600));
	this->titleInput = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(100, 100), wxSize(100, 100));
	this->submitButton = new wxButton(panel, wxID_ANY, "Add Tag", wxPoint(100, 400), wxSize(90, 50));

	submitButton->Bind(wxEVT_BUTTON, &AddTagFrame::OnSubmit, this);
}

void AddTagFrame::OnSubmit(wxCommandEvent& evt)
{
	std::string title = (std::string)this->titleInput->GetValue();
	title = trim(title);
	if (title.length() > 0) {
		this->repository->addTag(Tag(0, title));
		this->app->switchToFrame(new MainFrame(this->app, "Main Frame"));
	}
}