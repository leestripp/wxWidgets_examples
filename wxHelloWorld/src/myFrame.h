#ifndef MYFRAME_H
#define MYFRAME_H

#include <wx/wx.h>

enum {
    ID_Hello = 1
};


class myFrame : public wxFrame
{
public:
    myFrame( const wxString& title, const wxPoint& pos, const wxSize& size );

private:
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

    wxDECLARE_EVENT_TABLE();
};

#endif // MYFRAME_H
