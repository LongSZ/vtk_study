#include "vtkfltkwindowGUI.h"
//#include "vtkConeSource.h"
//#include "vtkActor.h"
//#include "vtkPolyDataMapper.h"
//#include "vtkRenderWindow.h"

int main( int argc, char ** argv)
{
	//vtkConeSource *cone = vtkConeSource::New();
	vtkfltkwindowGUI* gui = new vtkfltkwindowGUI;
	gui->Show();
	Fl::run();
	return 0;
}