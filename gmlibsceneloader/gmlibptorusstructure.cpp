#include "gmlibptorusstructure.h"

#include "gmlibsceneloaderdatadescription.h"

// stl
#include <iostream>

GMlibPTorusStructure::GMlibPTorusStructure()
  : ODDL::Structure(int(GMStructTypes::GMlibPTorus)){

  std::cout << "Constructing a GMlibPTorusStructure object" << int(GMStructTypes::GMlibPTorus)<< std::endl;
}

bool
GMlibPTorusStructure::ValidateSubstructure(
    const ODDL::DataDescription *dataDescription,
    const ODDL::Structure *structure) const{

  std::cout << "subtype of " << GetStructureType() << " is " << structure->GetStructureType() << std::endl;
  return (structure->GetStructureType() == int(GMStructTypes::GMlibSceneObjectData) || structure->GetStructureType() == int(GMStructTypes::GMlibPTorus)
          || structure->GetStructureType() == int(GMStructTypes::GMlibPTorusData) || structure->GetStructureType() == int(GMStructTypes::GMlibPSurfData));
}
