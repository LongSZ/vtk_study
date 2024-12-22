#include <vtkBMPReader.h>
#include <vtkImageViewer.h>
#include <vtkRenderWindowInteractor.h>

int main()
{
	vtkBMPReader *bmpReader = vtkBMPReader::New();
	bmpReader->SetFileName("viewport.bmp");

	vtkImageViewer *bmpViewer = vtkImageViewer::New();
	bmpViewer->SetInput(bmpReader->GetOutput());
	bmpViewer->SetColorLevel(128);
	bmpViewer->SetColorWindow(256);
	bmpViewer->Render();

	vtkRenderWindowInteractor *interactor = vtkRenderWindowInteractor::New();
	bmpViewer->SetupInteractor(interactor);
	interactor->Initialize();
	interactor->Start();

	//getchar();

	bmpReader->Delete();
	bmpViewer->Delete();
	interactor->Delete();
	
	return 0;

}