#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkSphereSource.h"
#include "vtkElevationFilter.h"
#include "vtkDataSetMapper.h"
#include "vtkActor.h"
#include "vtkLinearSubdivisionFilter.h"

//#include "SaveImage.h"

void main(int argc, char* argv[]) {
    vtkNew<vtkSphereSource> sphere;
    sphere->SetPhiResolution(10);       //Set the number of points in the latitude direction
    sphere->SetThetaResolution(10);     //Set the number of points in the longitude direction

    vtkNew<vtkElevationFilter> colorIt;
    colorIt->SetInputConnection(sphere->GetOutputPort());
    colorIt->SetLowPoint(0, 0, -1);
    colorIt->SetHighPoint(0, 0, 1);

    vtkNew<vtkLinearSubdivisionFilter> butterfly;
    butterfly->SetInputConnection(colorIt->GetOutputPort());
    butterfly->SetNumberOfSubdivisions(1);

    vtkNew<vtkDataSetMapper> mapper;
    mapper->SetInputConnection(butterfly->GetOutputPort());

    vtkNew<vtkActor> actor;
    actor->SetMapper(mapper);

    vtkNew<vtkRenderer> renderer;
    renderer->AddActor(actor);
    renderer->SetBackground(1, 1, 1);

    vtkNew<vtkRenderWindow> renWin;
    renWin->AddRenderer(renderer);
    renWin->SetSize(300, 300);
    renWin->Render();

    //  SAVEIMAGE( renWin );

    vtkNew<vtkRenderWindowInteractor> iren;
    iren->SetRenderWindow(renWin);
    iren->Start();
}
