#include <vtkConeSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkInteractorStyleTrackballActor.h>
#include <vtkProperty.h>

int main()
{
	vtkConeSource *cone=vtkConeSource::New();
	cone->SetResolution (10);
	cone->SetHeight(3);
	cone->SetRadius(1);

	vtkPolyDataMapper *coneMapper=vtkPolyDataMapper::New();
	coneMapper->SetInput(cone->GetOutput());

	vtkActor *coneActor=vtkActor::New();
	coneActor->SetMapper(coneMapper);
	//coneActor->GetProperty()->SetColor(1,0.0,0.0);
	
	vtkProperty *coneProperty=vtkProperty::New();
	coneProperty->SetColor(1.0,1.0,0.0);
	//coneProperty->LightingOff ();
	coneActor->SetProperty(coneProperty);

	vtkRenderer *renderer=vtkRenderer::New();
	renderer->AddActor(coneActor);
	renderer->SetBackground(.1,0.2,0.4);

	vtkRenderWindow *renWin=vtkRenderWindow::New();
	renWin->SetSize(400,200);
	renWin->AddRenderer(renderer);

	vtkRenderWindowInteractor *interactor=vtkRenderWindowInteractor::New();
	interactor->SetRenderWindow(renWin);

	//vtkInteractorStyleTrackballCamera *style = 
	//	vtkInteractorStyleTrackballCamera::New();
	//interactor->SetInteractorStyle(style);

	vtkInteractorStyleTrackballActor *style =
		vtkInteractorStyleTrackballActor::New();
	interactor->SetInteractorStyle(style);


	//for (int i=0; i=3600; i++)
	//{
		renWin->Render();
		renderer->GetActiveCamera()->Azimuth(1);
	//}

	interactor->Initialize();
	interactor->Start();
    
	cone->Delete();
	coneActor->Delete();
	coneMapper->Delete();
	renderer->Delete();
	renWin->Delete();
	interactor->Delete();
	style->Delete();
	coneProperty->Delete();

	return 0;

}