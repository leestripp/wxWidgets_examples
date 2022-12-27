#ifndef MYAPP_H
#define MYAPP_H

#include <wx/wx.h>

#include "myFrame.h"
#include "myGLcontext.h"


/** \brief Simple wxWidgets app class
 *
 *
 */

class myApp : public wxApp
{
public:
	myApp();

	void ToggleFullScreen();

    // Returns the shared context used by all frames and sets it as current for
    // the given canvas.
    myGLContext& GetContext( wxGLCanvas *canvas );

    // virtual wxApp methods
    virtual bool OnInit() wxOVERRIDE;
    virtual int OnExit() wxOVERRIDE;

    // helper funcs
	wxString    glGetwxString( GLenum name );
	void        CheckGLError();
	wxImage     DrawDice( int size, unsigned num );
	void 		GetGLInfo();
	void 		CheckGLErrors();

private:
    myGLContext *m_glContext;
    myFrame *m_frame;
};

#endif // MYAPP_H

