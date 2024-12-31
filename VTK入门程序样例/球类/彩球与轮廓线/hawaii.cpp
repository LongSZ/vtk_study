#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkPolyDataReader.h"
#include "vtkElevationFilter.h"
#include "vtkLookupTable.h"
#include "vtkDataSetMapper.h"
#include "vtkActor.h"
#include "vtkCamera.h"
#include "vtkSphereSource.h"
#include "vtkTexture.h"
#include "vtkJPEGReader.h"
#include "vtkProperty.h"
#include "vtkStripper.h"
#include "vtkPolyData.h"
#include "vtkShrinkPolyData.h"
#include "vtkPolyDataMapper.h"
#include "vtkPolyDataNormals.h"
#include "vtkExtractEdges.h"

int main() {
    vtkNew<vtkSphereSource> hawaii;
    hawaii->SetPhiResolution(8);        //Set the number of points in the latitude direction
    hawaii->SetThetaResolution(80);     //Set the number of points in the longitude direction
    hawaii->Update();

    vtkNew<vtkPolyDataNormals> cowNormals;
    cowNormals->SetInputConnection(hawaii->GetOutputPort());

    vtkNew<vtkStripper> cutStrips;
    cutStrips->SetInputConnection(cowNormals->GetOutputPort());
    cutStrips->Update();

    vtkNew<vtkExtractEdges> extract;
    extract->SetInputConnection(cowNormals->GetOutputPort());

    vtkNew<vtkPolyDataMapper> cutMapper;
    cutMapper->SetInputConnection(extract->GetOutputPort());

    vtkNew<vtkActor> cutActor;
    cutActor->SetMapper(cutMapper);
    cutActor->GetProperty()->SetColor(0, 0, 1);

    vtkNew<vtkShrinkPolyData> shrink2;
    shrink2->SetInputConnection(cowNormals->GetOutputPort());
    shrink2->SetShrinkFactor(0.90);

    vtkNew<vtkElevationFilter> elevation;
    elevation->SetInputConnection(shrink2->GetOutputPort());
    //elevation->SetLowPoint(0, 0, -1);
    //elevation->SetHighPoint(0, 0, 1);
    //elevation->SetScalarRange(0, 1);

    vtkNew<vtkLookupTable> lut;
    lut->SetHueRange(0.7, 0);
    lut->SetSaturationRange(1.0, 0);
    lut->SetValueRange(0.5, 1.0);
    lut->SetNumberOfColors(8);
    lut->Build();
    lut->SetTableValue(0, 0.0000, 0.7800, 0.5500, 1);
    lut->SetTableValue(1, 0.2353, 0.7020, 0.4431, 1);
    lut->SetTableValue(2, 0.5608, 0.7373, 0.5608, 1);
    lut->SetTableValue(3, 0.3333, 0.4196, 0.1843, 1);
    lut->SetTableValue(4, 0.5000, 0.1647, 0.1647, 1);
    lut->SetTableValue(5, 0.6400, 0.5800, 0.5000, 1);
    lut->SetTableValue(6, 0.9608, 0.9608, 0.8627, 1);
    lut->SetTableValue(7, 1.0000, 0.8941, 0.7686, 1);

    vtkNew<vtkDataSetMapper> hawaiiMapper;
    hawaiiMapper->SetInputConnection(elevation->GetOutputPort());
    //hawaiiMapper->SetScalarRange(0, 1000);
    //hawaiiMapper->SetLookupTable(lut);
    //hawaiiMapper->ImmediateModeRenderingOn();

    vtkNew<vtkJPEGReader> texture_reader;
    texture_reader->SetFileName("beach.jpg");

    vtkNew<vtkTexture> texture;
    texture->SetInputConnection(texture_reader->GetOutputPort());
    texture->InterpolateOn();

    vtkNew<vtkActor> hawaiiActor;
    hawaiiActor->SetMapper(hawaiiMapper);
    hawaiiActor->SetTexture(texture);

    //Create the RenderWindow, Renderer and both Actors, Add the actors to the renderer, set the background and size
    vtkNew<vtkRenderer> ren1, ren2;
    ren1->AddActor(hawaiiActor);
    ren1->AddActor(cutActor);
    ren1->SetBackground(0.4, 0.4, 0.0);
    ren1->SetViewport(0, 0, 0.5, 1.0);
    ren2->AddActor(cutActor);
    ren2->SetBackground(0.4, 0.4, 0.0);
    ren2->SetViewport(0.5, 0, 1.0, 1.0);

    vtkNew<vtkRenderWindow> renWin;
    renWin->AddRenderer(ren1);
    renWin->AddRenderer(ren2);
    renWin->SetSize(1000, 500);
    //renWin->DoubleBufferOff();
    renWin->Render();

    vtkNew<vtkRenderWindowInteractor> iren;
    iren->SetRenderWindow(renWin);
    iren->Initialize();
    iren->Start();

    return 0;
}