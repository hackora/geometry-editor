#include "gmlibsceneloaderdatadescription.h"

#include "gmlibversionstructure.h"
#include "gmlibcamerastructure.h"
#include "gmlibcamerastructure.h"
#include "gmlibsceneobjectdatastructure.h"
#include "gmlibsetstructure.h"
#include "gmlibsetcollapsedstructure.h"
#include "gmlibsetlightedstructure.h"
#include "gmlibsetvisiblestructure.h"
#include "gmlibpointstructure.h"
#include "gmlibvectorstructure.h"
#include "gmlibfloatstructure.h"
#include "gmlibptorusstructure.h"
#include "gmlibptorusdatastructure.h"
#include "gmlibpsurfdatastructure.h"
#include "gmlibenabledefvisualstructure.h"
#include "gmlibreplotstructure.h"
#include "gmlibsetradius1structure.h"
#include "gmlibsetradius2structure.h"
#include "gmlibsetwheelstructure.h"

#include <iostream>

ODDL::Structure *GMlibSceneLoaderDataDescription::CreateStructure(
    const ODDL::String &identifier) const {

  if(identifier == "GMlibVersion") {

    return new GMlibVersionStructure;
  }
  if(identifier == "Camera") {

    return new GMlibCameraStructure;
  }
  if(identifier == "SceneObjectData") {

    return new GMlibSceneObjectDataStructure;
  }
  if(identifier == "set") {

    return new GMlibSetStructure;
  }
  if(identifier == "Point") {

    return new GMlibPointStructure;
  }
  if(identifier == "Vector") {

    return new GMlibVectorStructure;
  }
  if(identifier == "setCollapsed") {

    return new GMlibSetCollapsedStructure;
  }
  if(identifier == "setLighted") {

    return new GMlibSetLightedStructure;
  }
  if(identifier == "setVisible") {

    return new GMlibSetVisibleStructure;
  }
  if(identifier == "PTorus") {

    return new GMlibPTorusStructure;
  }
  if(identifier == "PTorusData") {

    return new GMlibPTorusDataStructure;
  }
  if(identifier == "PSurfData") {

    return new GMlibPSurfDataStructure;
  }
  if(identifier == "enableDefaultVisualize") {

    return new GMlibEDVStructure;
  }
  if(identifier == "replot") {

    return new GMlibReplotStructure;
  }
  if(identifier == "setTubeRadius1") {

    return new GMlibSetRad1Structure;
  }
  if(identifier == "setTubeRadius1") {

    return new GMlibSetRad2Structure;
  }
  if(identifier == "setWheelRadius") {

    return new GMlibSetWheelStructure;
  }


  return nullptr;
}
