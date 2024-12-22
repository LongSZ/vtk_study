#include <vtkConeSource.h>
#include <vtkCubeSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkActor.h>
#include <vtkRenderWindowInteractor.h>

int main()
{
	vtkConeSource *cone=vtkConeSource::New();
	cone->SetResolution (10);
	cone->SetHeight(3);
	cone->SetRadius(1);

	vtkCubeSource *cube = vtkCubeSource::New();

	vtkPolyDataMapper *coneMapper=vtkPolyDataMapper::New();
	coneMapper->SetInput(cone->GetOutput());

	vtkPolyDataMapper *cubeMapper = vtkPolyDataMapper::New();
	cubeMapper->SetInput(cube->GetOutput());

	vtkActor *coneActor=vtkActor::New();
	coneActor->SetMapper(coneMapper);

	vtkActor *cubeActor = vtkActor::New();
	cubeActor->SetMapper(cubeMapper);
	
	vtkRenderer *renderer = vtkRenderer::New();
	renderer->AddActor(coneActor);
	renderer->SetBackground(1.0,0.0,0.0);
	renderer->SetViewport(0.0,0.0,0.5,0.5);

	vtkRenderer *renderer2 = vtkRenderer::New();
	renderer2->AddActor(cubeActor);
	renderer2->SetBackground(0.0,1.0,0.0);
	renderer2->SetViewport(0.5,0.0,1.0,0.5);

	vtkRenderer *renderer3 = vtkRenderer::New();
	renderer3->AddActor(cubeActor);
	renderer3->SetBackground(0.0,0.0,1.0);
	renderer3->SetViewport(0.0,0.5,0.5,1.0);

	vtkRenderer *renderer4 = vtkRenderer::New();
	renderer4->AddActor(cubeActor);
	renderer4->SetBackground(1.0,1.0,0.0);
	renderer4->SetViewport(0.5,0.5,1.0,1.0);

	vtkRenderWindow *renWin=vtkRenderWindow::New();
	renWin->SetSize(640,480);
	renWin->AddRenderer(renderer);
	renWin->AddRenderer(renderer2);
	renWin->AddRenderer(renderer3);
	renWin->AddRenderer(renderer4);

	vtkRenderWindowInteractor *interactor=vtkRenderWindowInteractor::New();
	interactor->SetRenderWindow(renWin);


	renWin->Render();
	interactor->Initialize();
	interactor->Start();
	
	coneActor->Delete();
	cone->Delete();
	coneMapper->Delete();
	cube->Delete();
	cubeActor->Delete();
	cubeMapper->Delete();
	renderer->Delete();
	renderer2->Delete();
	renderer3->Delete();
	renderer4->Delete();
	renWin->Delete();
	interactor->Delete();

	return 0;

}