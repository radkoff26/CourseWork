#include "FilterFrame.h"
#include "MainFrame.h"

const int THREE_DAYS = 60 * 60 * 24 * 3;

FilterFrame::FilterFrame(
	App* app,
	wxWindow* parent,
	Repository* repository
) : wxFrame(parent, wxID_ANY, "Filter Frame")
{
	this->app = app;

	this->repository = repository;

	this->tags = repository->findAllTags();

	this->panel = new wxPanel(this, wxID_ANY, wxPoint(0, 0), wxSize(800, 600));

	this->authorInput = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(100, 50), wxSize(200, 20));
	this->tagsList = new wxListBox(panel, wxID_ANY, wxPoint(100, 75), wxSize(-1, 300), {}, wxLB_MULTIPLE);
	this->lastThreeDaysCreationCheckbox = new wxCheckBox(panel, wxID_ANY, "Created within last three days?", wxPoint(100, 400), wxSize(-1, 25));
	this->lastThreeDaysModificationCheckbox = new wxCheckBox(panel, wxID_ANY, "Modified within last three days?", wxPoint(100, 450), wxSize(-1, 25));
	this->applyFiltersButton = new wxButton(panel, wxID_ANY, "Apply", wxPoint(100, 500), wxSize(-1, 50));

	int i = 0;
	for (auto it = tags.begin(); it < tags.end(); it++, i++)
	{
		tagsList->Insert((*it).getTitle(), i);
	}

	applyFiltersButton->Bind(wxEVT_BUTTON, &FilterFrame::OnApply, this);
}

void FilterFrame::OnApply(wxCommandEvent& evt)
{
	std::vector<std::function<bool(Note)>> filters;
	std::string author = (std::string)authorInput->GetValue();
	if (author.length() > 0) {
		filters.push_back([author](Note note) {
			if (note.getAuthor().length() < author.length()) {
				return false;
			}
			return note.getAuthor().find_first_of(author) < note.getAuthor().length();
			});
	}
	std::vector<Tag> selectedTags;
	for (int i = 0; i < tags.size(); i++)
	{
		if (tagsList->IsSelected(i)) {
			selectedTags.push_back(tags.at(i));
		}
	}
	if (selectedTags.size() > 0) {
		filters.push_back([selectedTags](Note note) {
			std::vector<Tag> tags = note.getTags();
			for (int i = 0; i < tags.size(); i++)
			{
				Tag tag = tags[i];

				for (int j = 0; j < selectedTags.size(); j++)
				{
					Tag temp = selectedTags.at(j);
					if (temp.getId() == tag.getId() && temp.getTitle() == tag.getTitle()) {
						return true;
					}
				}
			}
			return false;
			});
	}
	if (lastThreeDaysCreationCheckbox->GetValue()) {
		filters.push_back([](Note note) {
			return time(NULL) - THREE_DAYS < note.getCreationTime();
			});
	}
	if (lastThreeDaysModificationCheckbox->GetValue()) {
		filters.push_back([](Note note) {
			return time(NULL) - THREE_DAYS < note.getModificationTime();
			});
	}
	app->switchToFrame(new MainFrame(app, "Main Frame", filters, repository));
}
