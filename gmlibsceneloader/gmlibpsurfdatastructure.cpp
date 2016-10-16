#include "gmlibpsurfdatastructure.h"

#include "gmlibsceneloaderdatadescription.h"

// stl
#include <iostream>

GMlibPSurfDataStructure::GMlibPSurfDataStructure()
  : ODDL::Structure(int(GMStructTypes::GMlibPSurfData)){

  std::cout << "Constructing a GMlibPSurfDataStructure object" << int(GMStructTypes::GMlibPSurfData)<< std::endl;
}

bool
GMlibPSurfDataStructure::ValidateSubstructure(
    const ODDL::DataDescription *dataDescription,
    const ODDL::Structure *structure) const{

  std::cout << "subtype of " << GetStructureType() << " is " << structure->GetStructureType() << std::endl;
  return ((structure->GetStructureType() == int(GMStructTypes::GMlibEDV)) || (structure->GetStructureType() == int(GMStructTypes::GMlibReplot)));
}
