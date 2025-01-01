#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkConeSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkCubeSource.h"
#include "vtkSphereSource.h"
#include "vtkProperty.h"
#include "vtkRenderer.h"
#include "vtkProperty.h"
//#include "SaveImage.h"

void main(int argc, char* argv[]) {
    // create an actor and give it cone geometry
    vtkNew<vtkConeSource> cone;
    cone->SetResolution(8);
    vtkNew<vtkPolyDataMapper> coneMapper;
    coneMapper->SetInputConnection(cone->GetOutputPort());
    vtkNew<vtkActor> coneActor;
    coneActor->SetMapper(coneMapper);
    coneActor->GetProperty()->SetColor(1, 0, 0);

    // create an actor and give it cube geometry
    vtkNew<vtkCubeSource> cube;
    vtkNew<vtkPolyDataMapper> cubeMapper;
    cubeMapper->SetInputConnection(cube->GetOutputPort());
    vtkNew<vtkActor> cubeActor;
    cubeActor->SetMapper(cubeMapper);
    cubeActor->GetProperty()->SetColor(0, 1, 0);

    // create an actor and give it sphere geometry
    vtkNew<vtkSphereSource> sphere;
    sphere->SetThetaResolution(16); 
    sphere->SetPhiResolution(16);
    vtkNew<vtkPolyDataMapper> sphereMapper;
    sphereMapper->SetInputConnection(sphere->GetOutputPort());
    vtkNew<vtkActor> sphereActor;
    sphereActor->SetMapper(sphereMapper);
    sphereActor->GetProperty()->SetColor(0, 0, 1);

    // assign our actor to both renderers, set the viewports and background of the renderers
    vtkNew<vtkRenderer> ren1, ren2, ren3;
    ren1->AddActor(coneActor);
    ren1->SetBackground(0.9, 0.9, 0.9);
    ren1->SetViewport(0, 0, 0.5, 1);
    ren2->AddActor(sphereActor);
    ren2->SetViewport(0.5, 0, 1, 1);
    ren2->SetBackground(1, 1, 1);
    ren3->AddActor(cubeActor);
    ren3->SetBackground(1, 1, 1);

    // set the size of our window
    vtkNew<vtkRenderWindow> renWindow1, renWindow2;
    renWindow1->AddRenderer(ren1);
    renWindow1->AddRenderer(ren2);
    renWindow1->SetSize(300, 150);
    renWindow1->SetPosition(0, 50);
    renWindow1->Render();
    renWindow2->AddRenderer(ren3);
    renWindow2->SetSize(300, 300);
    renWindow2->SetPosition(0, 300);
    renWindow2->Render();

    vtkNew<vtkRenderWindowInteractor> iren1, iren2;
    iren1->SetRenderWindow(renWindow1);
    iren2->SetRenderWindow(renWindow2);
    iren1->Start();
}