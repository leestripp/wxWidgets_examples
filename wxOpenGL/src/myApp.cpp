#include <iostream>

#include "myApp.h"
#include "myFrame.h"

#include <wx/wx.h>

#if !wxUSE_GLCANVAS
    #error "OpenGL required: set wxUSE_GLCANVAS to 1 and rebuild the wxWidgets library"
#endif

wxIMPLEMENT_APP( myApp );

using namespace std;

myApp::myApp()
{
	m_glContext = NULL;
	m_frame = NULL;
}

void myApp::ToggleFullScreen()
{
    m_frame->ShowFullScreen(! m_frame->IsFullScreen() );
}

bool myApp::OnInit()
{
    if ( !wxApp::OnInit() )
        return false;

    m_frame = new myFrame();

    return true;
}

int myApp::OnExit()
{
    delete m_glContext;

    return wxApp::OnExit();
}

myGLContext& myApp::GetContext( wxGLCanvas *canvas )
{
    if( !m_glContext )
    {
        // Create the OpenGL context for the first mono window which needs it:
        // subsequently created windows will all share the same context.
        m_glContext = new myGLContext( canvas );
    }
    m_glContext->SetCurrent( *canvas );

    return *m_glContext;
}

// ----------------------------------------------------------------------------
// helper functions
// ----------------------------------------------------------------------------

wxString myApp::glGetwxString( GLenum name )
{
    const GLubyte *v = glGetString( name );
    if ( v == 0 )
    {
        // The error is not important. It is GL_INVALID_ENUM.
        // We just want to clear the error stack.
        glGetError();

        return wxString();
    }

    return wxString( (const char*)v );
}

void myApp::CheckGLError()
{
    GLenum errLast = GL_NO_ERROR;
    for ( ;; )
    {
        GLenum err = glGetError();
        if ( err == GL_NO_ERROR )
            return;

        // normally the error is reset by the call to glGetError() but if
        // glGetError() itself returns an error, we risk looping forever here
        // so check that we get a different error than the last time
        if ( err == errLast )
        {
            wxLogError( "OpenGL error state couldn't be reset." );
            return;
        }

        errLast = err;
        wxLogError( "OpenGL error %d", err );
    }
}

// function to draw the texture for cube faces
wxImage myApp::DrawDice( int size, unsigned num )
{
    wxASSERT_MSG( num >= 1 && num <= 6, "DrawDice( int size, unsigned num ) : invalid dice num" );

    const int dot = size/16;        // radius of a single dot
    const int gap = 5*size/32;      // gap between dots

    wxBitmap bmp(size, size);
    wxMemoryDC dc;
    dc.SelectObject( bmp );
    dc.SetBackground( *wxWHITE_BRUSH );
    dc.Clear();
    dc.SetBrush( *wxBLACK_BRUSH );

    // the upper left and lower right points
    if ( num != 1 )
    {
        dc.DrawCircle( gap + dot, gap + dot, dot );
        dc.DrawCircle( size - gap - dot, size - gap - dot, dot );
    }

    // draw the central point for odd dices
    if ( num % 2 )
    {
        dc.DrawCircle( size/2, size/2, dot );
    }

    // the upper right and lower left points
    if ( num > 3 )
    {
        dc.DrawCircle( size - gap - dot, gap + dot, dot );
        dc.DrawCircle( gap + dot, size - gap - dot, dot );
    }

    // finally those 2 are only for the last dice
    if ( num == 6 )
    {
        dc.DrawCircle(gap + dot, size/2, dot);
        dc.DrawCircle(size - gap - dot, size/2, dot);
    }

    dc.SelectObject( wxNullBitmap );

    return bmp.ConvertToImage();
}

void myApp::GetGLInfo()
{
    const wxString vendor = glGetwxString( GL_VENDOR );
    const wxString renderer = glGetwxString( GL_RENDERER );
    const wxString version = glGetwxString( GL_VERSION );
    const wxString shaders = glGetwxString( GL_SHADING_LANGUAGE_VERSION );

    cout << "OpenGL info" << endl;
    cout << "Vender   : " << vendor << endl;
    cout << "Renderer : " << renderer << endl;
    cout << "Version  : " << version << endl;
    cout << "Shaders  : " << shaders << endl;

}

void myApp::CheckGLErrors()
{
    GLenum err;
    while( (err = glGetError()) != GL_NO_ERROR )
    {
        // Process/log the error.
        switch( err )
        {
        case GL_INVALID_ENUM:
            cout << "OpenGL error: GL_INVALID_ENUM" << endl;
            break;

        case GL_INVALID_FRAMEBUFFER_OPERATION:
            cout << "OpenGL error: GL_INVALID_FRAMEBUFFER_OPERATION" << endl;
            break;

        case GL_INVALID_INDEX:
            cout << "OpenGL error: GL_INVALID_INDEX" << endl;
            break;

        case GL_INVALID_OPERATION:
            cout << "OpenGL error: GL_INVALID_OPERATION" << endl;
            break;

        case GL_INVALID_VALUE:
            cout << "OpenGL error: GL_INVALID_VALUE" << endl;
            break;

        default:
            // Unknown error
            break;
        }
    }
}
