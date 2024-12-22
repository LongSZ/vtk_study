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
#include <vtkLight.h>
#include <vtkCamera.h>

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
	//coneProperty->SetColor(1.0,1.0,0.0);
	//coneProperty->LightingOff ();
	coneActor->SetProperty(coneProperty);

	vtkRenderer *renderer = vtkRenderer::New();
	renderer->AddActor(coneActor);
	renderer->SetBackground(.1,0.2,0.4);

	vtkLight *light = vtkLight::New();
	//light->SetSpecularColor(1.0,0.0,0.0);
	//light->SetDiffuseColor(0.0,1.0,0.0);
	light->SetColor(0.0,0.0,1.0);
	renderer->AddLight(light);

	/*vtkCamera *camera = vtkCamera::New();
	camera->SetPosition(5.0,0.0,0.0);
	camera->SetFocalPoint(-1.0,0.0,0.0);
	camera->SetViewUp(0.0,1.0,0.0);
	renderer->SetActiveCamera(camera);*/
	renderer->GetActiveCamera()->SetPosition(5.0,0.0,0.0);
	renderer->GetActiveCamera()->SetFocalPoint(-1.0,0.0,0.0);
	renderer->GetActiveCamera()->SetViewUp(0.0,1.0,0.0);

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
	light->Delete();
	//camera->Delete();

	return 0;

}