#include "myApp.h"
#include "myFrame.h"

wxBEGIN_EVENT_TABLE( myFrame, wxFrame )
    EVT_MENU( ID_Hello,   myFrame::OnHello )
    EVT_MENU( wxID_EXIT,  myFrame::OnExit )
    EVT_MENU( wxID_ABOUT, myFrame::OnAbout )
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP( myApp );

myFrame::myFrame( const wxString& title, const wxPoint& pos, const wxSize& size ) : wxFrame(NULL, wxID_ANY, title, pos, size)
{
	wxMenu *menuFile = new wxMenu;
    menuFile->Append( ID_Hello, "&Hello...\tCtrl-H", "Help string shown in status bar for this menu item" );
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append( menuFile, "&File" );
    menuBar->Append( menuHelp, "&Help" );
    SetMenuBar( menuBar );
    CreateStatusBar();
    SetStatusText( "Welcome to wxWidgets!" );
}

void myFrame::OnHello(wxCommandEvent& event)
{
    wxLogMessage( "Hello world from wxWidgets!" );
}

void myFrame::OnExit(wxCommandEvent& event)
{
	Close( true );
}

void myFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox( "This is a wxWidgets' Hello world sample", "About Hello World", wxOK | wxICON_INFORMATION );
}
