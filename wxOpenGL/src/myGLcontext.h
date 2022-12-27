#ifndef MYGLCONTEXT_H
#define MYGLCONTEXT_H

#include <wx/glcanvas.h>

// the rendering context used by all GL canvases
class myGLContext : public wxGLContext
{
public:
    myGLContext( wxGLCanvas *canvas );

    // render the cube showing it at given angles
    void DrawRotatedCube( float xangle, float yangle );

private:
    // textures for the cube faces
    GLuint m_textures[6];
};

#endif // MYGLCONTEXT_H
