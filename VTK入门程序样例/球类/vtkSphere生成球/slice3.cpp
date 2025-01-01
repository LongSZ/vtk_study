#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkSphere.h"
#include "vtkImplicitBoolean.h"
#include "vtkActor.h"
#include "vtkCamera.h"
#include "vtkProperty.h"
#include "vtkPolyData.h"
#include "vtkSampleFunction.h"
#include "vtkContourFilter.h"
#include "vtkPolyDataNormals.h"
#include "vtkPolyDataMapper.h"
#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkCommand.h"
#include "vtkCallbackCommand.h"
#include "vtkHexahedron.h"

void main() {
    vtkNew<vtkSphere> iceCream;
    iceCream->SetCenter(1, 0, 0);
    iceCream->SetRadius(1);

    vtkNew<vtkHexahedron> hexahedron;

    vtkNew<vtkSampleFunction> theCreamSample;
    theCreamSample->SetImplicitFunction((vtkImplicitFunction*)iceCream);
    theCreamSample->SetModelBounds(-1.25, 2.25, -1.25, 1.25, -1.25, 1.25);
    theCreamSample->SetSampleDimensions(60, 60, 60);
    theCreamSample->ComputeNormalsOff();

    vtkNew<vtkContourFilter> theCreamSurface;
    theCreamSurface->SetInputConnection(theCreamSample->GetOutputPort());
    theCreamSurface->SetValue(0, 0.0);

    vtkNew<vtkPolyDataMapper> creamMapper;
    creamMapper->SetInputConnection(theCreamSurface->GetOutputPort());
    creamMapper->ScalarVisibilityOff();

    vtkNew<vtkActor> creamActor;
    creamActor->SetMapper(creamMapper);
    creamActor->GetProperty()->SetColor(0.6, 0.6, 1);

    vtkNew<vtkRenderer> ren1;
    ren1->AddActor(creamActor);
    ren1->SetBackground(1, 1, 1);
    ren1->ResetCamera();

    vtkNew<vtkRenderWindow> renWin;
    renWin->AddRenderer(ren1);
    renWin->SetSize(600, 600);
    renWin->Render();

    vtkNew<vtkRenderWindowInteractor> iren;
    iren->SetRenderWindow(renWin);
    iren->Start();
}