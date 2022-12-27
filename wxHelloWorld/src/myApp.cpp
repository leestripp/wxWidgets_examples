#include "myApp.h"
#include "myFrame.h"

bool myApp::OnInit()
{
	myFrame *frame = new myFrame( "Hello World", wxPoint(50, 50), wxSize(450, 340) );
    frame->Show( true );
	return true;
}
