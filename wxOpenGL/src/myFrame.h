#ifndef MYFRAME_H
#define MYFRAME_H

#include <wx/wx.h>


class myFrame : public wxFrame
{
public:
    myFrame();

private:
    void OnClose( wxCommandEvent& event );
    void OnNewWindow( wxCommandEvent& event );

    wxDECLARE_EVENT_TABLE();
};

#endif // MYFRAME_H
