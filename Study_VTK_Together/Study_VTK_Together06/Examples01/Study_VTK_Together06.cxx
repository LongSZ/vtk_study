#include <vtkConeSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkCommand.h>
#include <vtkProperty.h>

class vtkMyCallback : public vtkCommand
{
public:
	static vtkMyCallback *New() 
	{ return new vtkMyCallback; }
	virtual void Execute(vtkObject *caller, unsigned long, void*)
	{
		vtkRenderer *renderer = reinterpret_cast<vtkRenderer*>(caller);
		cout << renderer->GetActiveCamera()->GetPosition()[0] << " "
			<< renderer->GetActiveCamera()->GetPosition()[1] << " "
			<< renderer->GetActiveCamera()->GetPosition()[2] << "\n";
	}
};

class vtkMyCallback2 : public vtkCommand
{
public:
	static vtkMyCallback2 *New()
	{
		return new vtkMyCallback2;
	}
	virtual void Execute(vtkObject *caller, unsigned long eventId, void *callData)
	{
		vtkActor *actor = reinterpret_cast<vtkActor*>(caller);
		actor->GetProperty()->SetColor(1.0,0.0,0.0);
	}
};

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

	vtkMyCallback2 *mycallback2 = vtkMyCallback2::New();
	coneActor->AddObserver(vtkCommand::PickEvent,mycallback2);
	mycallback2->Delete();

	vtkRenderer *renderer=vtkRenderer::New();
	renderer->AddActor(coneActor);
	renderer->SetBackground(.1,0.2,0.4);

	vtkMyCallback *mo1 = vtkMyCallback::New();
	renderer->AddObserver(vtkCommand::StartEvent,mo1);
	mo1->Delete(); 

	vtkRenderWindow *renWin=vtkRenderWindow::New();
	renWin->SetSize(400,400);
	renWin->AddRenderer(renderer);

	vtkRenderWindowInteractor *interactor = vtkRenderWindowInteractor::New();
	interactor->SetRenderWindow(renWin);
	renWin->Render();
	interactor->Initialize();
	interactor->Start();
   
	cone->Delete();
	coneActor->Delete();
	coneMapper->Delete();
	renderer->Delete();
	renWin->Delete();
	interactor->Delete();

	return 0;

}