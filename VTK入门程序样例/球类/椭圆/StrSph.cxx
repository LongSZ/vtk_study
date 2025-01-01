#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkSphereSource.h"
#include "vtkTransform.h"
#include "vtkTransformFilter.h"
#include "vtkElevationFilter.h"
#include "vtkLookupTable.h"
#include "vtkDataSetMapper.h"
#include "vtkActor2D.h"
#include "vtkCamera.h"
#include "vtkScalarBarActor.h"
#include "vtkCoordinate.h"
#include "vtkPolyDataMapper2D.h" 

void main(int argc, char* argv[]) {
    vtkNew<vtkSphereSource> sphere;
    sphere->SetThetaResolution(12);
    sphere->SetPhiResolution(12);

    vtkNew<vtkTransform> aTransform;
    aTransform->Scale(1, 1.5, 2);

    vtkNew<vtkTransformFilter> transFilter;
    transFilter->SetInputConnection(sphere->GetOutputPort());
    transFilter->SetTransform(aTransform);

    vtkNew<vtkElevationFilter> colorIt;
    colorIt->SetInputConnection(transFilter->GetOutputPort());
    colorIt->SetLowPoint(0, 0, -1);
    colorIt->SetHighPoint(0, 0, 1);

    vtkNew<vtkLookupTable> lut;
    lut->SetHueRange(0, 0);
    lut->SetSaturationRange(0, 0);
    lut->SetValueRange(.1, 1);

    vtkNew<vtkCoordinate> normCoords;
    normCoords->SetCoordinateSystemToWorld();
    //normCoords->SetCoordinateSystemToDisplay (); 
    //normCoords->SetCoordinateSystemToNormalizedDisplay (); 
    //normCoords->SetCoordinateSystemToViewport (); 
    //normCoords->SetCoordinateSystemToNormalizedViewport (); 
    //normCoords->SetCoordinateSystemToView ();

    vtkNew<vtkPolyDataMapper2D> mapper;
    mapper->SetLookupTable(lut);
    mapper->SetInputConnection(colorIt->GetOutputPort());
    mapper->SetTransformCoordinate(normCoords);

    vtkNew<vtkActor2D> actor;
    actor->SetMapper(mapper);

    //Create a scalar bar
    vtkNew<vtkScalarBarActor> scalarBar;
    scalarBar->SetLookupTable(mapper->GetLookupTable());
    scalarBar->SetTitle("Color Table");
    scalarBar->GetPositionCoordinate()->SetCoordinateSystemToNormalizedViewport();
    scalarBar->GetPositionCoordinate()->SetValue(0.1, 0.01);
    //scalarBar-> GetPositionCoordinate()
    scalarBar->SetNumberOfLabels(6);
    scalarBar->SetOrientationToHorizontal();
    scalarBar->SetWidth(0.8);
    scalarBar->SetHeight(0.12);

    vtkNew<vtkRenderer> renderer;
    renderer->AddActor(actor);
    renderer->AddActor2D(scalarBar);
    renderer->SetBackground(1, 1, 0);
    renderer->GetActiveCamera()->Elevation(60.0);
    renderer->GetActiveCamera()->Azimuth(30.0);
    renderer->GetActiveCamera()->Zoom(1.3);

    vtkNew<vtkRenderWindow> renWin;
    renWin->AddRenderer(renderer);
    renWin->SetSize(300, 300);
    renWin->Render();

    // interact with data
    vtkNew<vtkRenderWindowInteractor> iren;
    iren->SetRenderWindow(renWin);
    iren->Start();
}