#include "AddTagFrame.h"
#include "MainFrame.h"
#include <vector>
#include <wx/wx.h>
#include <wx/splitter.h>
#include <wx/html/htmlwin.h>
#include "Repository.h"
#include "Utils.h"

AddTagFrame::AddTagFrame(App* app, Repository* repository) : wxFrame(nullptr, wxID_ANY, "Add Tag")
{
	this->app = app;
	if (repository == nullptr) {
		this->repository = new Repository();
	}
	else {
		this->repository = repository;
	}
	this->panel = new wxPanel(this, wxID_ANY, wxPoint(0, 0), wxSize(800, 600));
	wxStaticText* titleLabel = new wxStaticText(panel, wxID_ANY, "Title:", wxPoint(100, 250), wxSize(50, 50));
	this->titleInput = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(150, 250), wxSize(300, 30));
	this->submitButton = new wxButton(panel, wxID_ANY, "Add Tag", wxPoint(150, 300), wxSize(100, 50));

	submitButton->Bind(wxEVT_BUTTON, &AddTagFrame::OnSubmit, this);
}

void AddTagFrame::OnSubmit(wxCommandEvent& evt)
{
	std::string title = (std::string)this->titleInput->GetValue();
	title = trim(title);
	if (title.length() > 0) {
		this->repository->addTag(Tag(0, title));
		this->app->switchToFrame(new MainFrame(this->app, {}, nullptr));
	}
}