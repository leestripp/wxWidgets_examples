#ifndef MYGLCANVAS_H
#define MYGLCANVAS_H

#include <wx/wx.h>
#include <wx/glcanvas.h>


class myGLCanvas : public wxGLCanvas
{
public:
    myGLCanvas( wxWindow *parent, int *attribList = NULL );
	~myGLCanvas();

private:
    void OnPaint(wxPaintEvent& event);
    void Spin( float xSpin, float ySpin );
    void OnKeyDown( wxKeyEvent& event );
    void OnSpinTimer( wxTimerEvent& WXUNUSED(event) );

    // angles of rotation around x- and y- axis
    float m_xangle, m_yangle;
    wxTimer *m_spinTimer;

    wxDECLARE_EVENT_TABLE();
};

#endif // MYGLCANVAS_H
