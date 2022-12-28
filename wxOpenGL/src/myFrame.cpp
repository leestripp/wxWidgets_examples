#include <wx/wx.h>

// App icon
#include "icon/sample.xpm"

#include "myApp.h"
#include "myFrame.h"
#include "myGLcanvas.h"

// so we can call wxGetApp
DECLARE_APP( myApp )

wxBEGIN_EVENT_TABLE( myFrame, wxFrame )
    EVT_MENU( wxID_CLOSE, myFrame::OnClose )
wxEND_EVENT_TABLE()

myFrame::myFrame() : wxFrame(NULL, wxID_ANY, "wxWidgets OpenGL")
{
    // sample.xpm
    SetIcon( wxICON(sample) );

    int attribList[] = {
         WX_GL_DOUBLEBUFFER,
         WX_GL_CORE_PROFILE,        // Test to see if it effects OLD GL code.
         WX_GL_DEPTH_SIZE, 24,
         0 };
    new myGLCanvas( this, attribList );

    // Make a menubar
    wxMenu *menu = new wxMenu;
    menu->Append( wxID_CLOSE );
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append( menu, "&Window" );
    SetMenuBar( menuBar );

    CreateStatusBar();

    SetClientSize( 1920, 1080 );
    Show();
    Centre( wxALL );

    // test IsDisplaySupported() function:
    wxLogStatus( "F1: Toggle fullscreen, Spacebar: Animation, Arrow keys: Rotate - Double-buffered display %s supported", wxGLCanvas::IsDisplaySupported( attribList ) ? "is" : "not" );
}

void myFrame::OnClose(wxCommandEvent& WXUNUSED(event))
{
    // true is to force the frame to close
    Close(true);
}
