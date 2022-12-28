#include <iostream>
#include <wx/wx.h>

#include "myGLcanvas.h"
#include "myApp.h"

using namespace std;

enum {
    SpinTimer = wxID_HIGHEST + 1
};

// so we can call wxGetApp
DECLARE_APP( myApp )

wxBEGIN_EVENT_TABLE( myGLCanvas, wxGLCanvas )
    EVT_PAINT( myGLCanvas::OnPaint )
    EVT_KEY_DOWN( myGLCanvas::OnKeyDown )
    EVT_TIMER( SpinTimer, myGLCanvas::OnSpinTimer )
wxEND_EVENT_TABLE()

// With perspective OpenGL graphics, the wxFULL_REPAINT_ON_RESIZE style
// flag should always be set, because even making the canvas smaller should
// be followed by a paint event that updates the entire canvas with new
// viewport settings.
myGLCanvas::myGLCanvas( wxWindow *parent, int *attribList ) : wxGLCanvas( parent, wxID_ANY, attribList, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE )
{
    m_xangle = 30.0;
    m_yangle = 30.0;

    m_spinTimer = new wxTimer( this, SpinTimer );
}

myGLCanvas::~myGLCanvas()
{
    if( m_spinTimer ) delete m_spinTimer;
}

void myGLCanvas::OnPaint( wxPaintEvent& WXUNUSED(event) )
{
    GLdouble w, h;

    // This is required even though dc is not used otherwise.
    wxPaintDC dc(this);

    // Get context and set current
    myGLContext& context = wxGetApp().GetContext( this );

    const wxSize frameSize = GetSize() * GetContentScaleFactor();
    // set viewing projection
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    w = frameSize.x;
    h = frameSize.y;
    GLdouble ratio = w/h;
    glFrustum( -1.0*ratio, 1.0*ratio, -1.0, 1.0, 1, 100.0 );
    glViewport( 0, 0, frameSize.x, frameSize.y );
    wxGetApp().CheckGLError();

    context.DrawRotatedCube( m_xangle, m_yangle );
     wxGetApp().CheckGLError();

    SwapBuffers();
}

void myGLCanvas::Spin( float xSpin, float ySpin )
{
    m_xangle += xSpin;
    m_yangle += ySpin;

    Refresh( false );
}

void myGLCanvas::OnKeyDown(wxKeyEvent& event)
{
    float angle = 5.0;

    switch( event.GetKeyCode() )
    {
        case WXK_RIGHT:
            Spin( 0.0, -angle );
            break;

        case WXK_LEFT:
            Spin( 0.0, angle );
            break;

        case WXK_DOWN:
            Spin( -angle, 0.0 );
            break;

        case WXK_UP:
            Spin( angle, 0.0 );
            break;

        case WXK_SPACE:
            if( m_spinTimer->IsRunning() )
                m_spinTimer->Stop();
            else
                m_spinTimer->Start( 25 );
            break;

        case WXK_ESCAPE:
            wxGetApp().GetTopWindow()->Close();
            break;

        case WXK_F1:
            wxGetApp().ToggleFullScreen();
            break;


        default:
            event.Skip();
            return;
    }
}

void myGLCanvas::OnSpinTimer( wxTimerEvent& WXUNUSED(event) )
{
    Spin( 4.5, 4.2 );
}
