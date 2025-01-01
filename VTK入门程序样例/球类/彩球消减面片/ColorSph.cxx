#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkSphereSource.h"
#include "vtkElevationFilter.h"
#include "vtkDataSetMapper.h"
#include "vtkActor.h"
#include "vtkButterflySubdivisionFilter.h"
#include "vtkDecimatePro.h"
#include "vtkSmoothPolyDataFilter.h" 

//#include "SaveImage.h"

void main(int argc, char* argv[]) {
    vtkNew<vtkSphereSource> sphere;
    sphere->SetPhiResolution(12);       //Set the number of points in the latitude direction
    sphere->SetThetaResolution(12);     //Set the number of points in the longitude direction

    vtkNew<vtkElevationFilter> colorIt;
    colorIt->SetInputConnection(sphere->GetOutputPort());
    colorIt->SetLowPoint(0, 0, -1);
    colorIt->SetHighPoint(0, 0, 1);

    //产生色彩渐变效果
    vtkNew<vtkButterflySubdivisionFilter> butterfly;
    butterfly->SetInputConnection(colorIt->GetOutputPort());
    butterfly->SetNumberOfSubdivisions(1);

    vtkNew<vtkDecimatePro> deci;
    deci->SetInputConnection(butterfly->GetOutputPort());
    deci->SetTargetReduction(0.5);

    vtkNew<vtkSmoothPolyDataFilter> smooth;
    smooth->SetInputConnection(deci->GetOutputPort());
    smooth->SetNumberOfIterations(50);

    vtkNew<vtkDataSetMapper> mapper;    //可将所有的数据转换成点，线和多角形/三角形然后映射到图形制度
    mapper->SetInputConnection(smooth->GetOutputPort());

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