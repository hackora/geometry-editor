#include "gmlibcamerastructure.h"

#include "gmlibsceneloaderdatadescription.h"

// stl
#include <iostream>

GMlibCameraStructure::GMlibCameraStructure()
  : ODDL::Structure(int(GMStructTypes::GMlibCamera)){

  std::cout << "Constructing a GMlibCameraStructure object" << int(GMStructTypes::GMlibCamera)<< std::endl;
}

bool
GMlibCameraStructure::ValidateSubstructure(
    const ODDL::DataDescription *dataDescription,
    const ODDL::Structure *structure) const{

  std::cout << "subtype of " << GetStructureType() << " is " << structure->GetStructureType() << std::endl;
  return structure->GetStructureType() == int(GMStructTypes::GMlibSceneObjectData);
}
