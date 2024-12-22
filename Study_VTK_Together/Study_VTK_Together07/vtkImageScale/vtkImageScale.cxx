// ㊣?角y℅車?谷車?車迆?芍豕?米ㄓ﹞迄CT赤???2⊿??那??角車|DICOM???t?D赤﹞D??⊿?㏒ 
 
// First include the required header files for the VTK classes we are using. 
 
#include "vtkDICOMImageReader.h" 
#include "vtkBMPReader.h" 
#include "vtkVolume16Reader.h" 
#include "vtkImageViewer.h" 
#include "vtkRenderWindowInteractor.h" 
 
//??2“o‘那y 
#include "vtkImageMagnify.h" 
#include "vtkTransform.h" 
 
  
int main() 
{ 
    vtkBMPReader   *dr =  vtkBMPReader::New(); 
	  dr->SetDataByteOrderToLittleEndian(); 
	  dr->SetFileName("mm.bmp"); 
	  dr->SetDataOrigin(0,0,0.0); 
	 vtkTransform *t1=vtkTransform::New();	 
		t1->RotateZ(0); 
	  dr->SetTransform(t1); 
 
//=================================================	   
//??2“2迄℅¯ 
 
    vtkImageMagnify *mfy=vtkImageMagnify::New(); 
	//赤???﹞?∩車,2??芍車? 
      mfy->SetInputConnection(dr->GetOutputPort()); 
	  mfy->SetMagnificationFactors(3,2,2);//???邦﹞?∩車??那y㊣?,??DCM赤????TD∫ 
 
//======================================================= 
 
    vtkImageViewer  *viewer = vtkImageViewer::New(); 
	  viewer->SetInput(mfy->GetOutput()); 
	  viewer->SetColorWindow(1000); 
	  viewer->SetColorLevel(200); 
	  viewer->SetPosition(0,0); 
	  viewer->Render(); 
 
    vtkRenderWindowInteractor *viewerinter = vtkRenderWindowInteractor::New(); 
	  viewer->SetupInteractor(viewerinter); 
 
    vtkImageViewer  *viewer2 = vtkImageViewer::New(); 
	  viewer2->SetInput(dr->GetOutput()); 
	  viewer2->SetColorWindow(256); 
	  viewer2->SetColorLevel(200); 
	  viewer2->SetPosition(0,100); 
	  viewer2->Render(); 
 
    vtkRenderWindowInteractor *viewerinter2 = vtkRenderWindowInteractor::New(); 
	  viewer2->SetupInteractor(viewerinter2); 
 
	    
	viewerinter->Initialize(); 
    viewerinter->Start();  
   

//	cout<GetPatientName()<GetHeight()<GetWidth()<GetStudyUID()<GetDataByteOrderAsString()<GetHeaderSize()<GetPixelSpacing()<Delete(); 
	mfy->Delete(); 
	viewer->Delete(); 
	viewerinter->Delete(); 
    viewer2->Delete(); 
	viewerinter2->Delete(); 
	return 0; 
} 
