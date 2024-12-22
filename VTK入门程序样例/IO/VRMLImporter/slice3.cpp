


#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkVRMLImporter.h"
#include "vtkPolyDataMapper.h"
#include "vtkLODActor.h"
#include "vtkCamera.h"

void main()
{
  vtkRenderer *ren1 = vtkRenderer::New();
  vtkRenderWindow *renWin = vtkRenderWindow::New();
    renWin->AddRenderer(ren1);
  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWin);

	vtkVRMLImporter *importer=vtkVRMLImporter::New();
//	  importer-> SetRenderWindow(renWin);
	  importer-> SetFileName ("NEFERTITI.WRL");
	  importer-> Read();

	importer-> GetRenderer()->SetBackground( 0.1, 0.2, 0.4);
	renWin-> SetSize (500,500);
	renWin->AddRenderer(importer-> GetRenderer());

	importer-> GetRenderer()-> ResetCamera();
	importer-> GetRenderer()-> GetActiveCamera()->Zoom( 1.4);

  renWin->Render();
  iren->Start();
}
