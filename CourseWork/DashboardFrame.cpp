#include "DashboardFrame.h"
#include "MainFrame.h"

DashboardFrame::DashboardFrame(App* app, Repository* repository): wxFrame(nullptr, wxID_ANY, "Dashboard")
{
	this->app = app;
	this->repository = repository;

	wxPanel* panel = new wxPanel(this, wxID_ANY, wxPoint(0, 0), wxSize(800, 600));
	wxListBox* tagStats = new wxListBox(panel, wxID_ANY, wxPoint(200, 50), wxSize(400, 225));
	wxListBox* authorStats = new wxListBox(panel, wxID_ANY, wxPoint(200, 325), wxSize(400, 225));
	wxButton* buttonBack = new wxButton(panel, wxID_ANY, "OK", wxPoint(350, 555), wxSize(100, 35));

	std::vector<Tag> tags = repository->findAllTags();

	for (int i = 0; i < tags.size(); i++)
	{
		int count = repository->countTagRelationsByTagId(tags[i].getId());
		tagStats->Insert(tags[i].getTitle() + ": " + std::to_string(count) + " note(s)", i);
	}

	std::map<std::string, int> authorsMap = repository->countAuthorsNotesGrouped();

	std::for_each(authorsMap.begin(), authorsMap.end(), [authorStats](std::pair<std::string, int> pair) {
		authorStats->Insert(pair.first + ": " + std::to_string(pair.second) + " note(s)", authorStats->GetCount());
		});

	buttonBack->Bind(wxEVT_BUTTON, &DashboardFrame::OnBack, this);
}

void DashboardFrame::OnBack(wxCommandEvent& evt)
{
	app->switchToFrame(new MainFrame(app, "Main Frame", {}, repository));
}
