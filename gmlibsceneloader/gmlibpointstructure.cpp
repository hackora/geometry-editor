#include "gmlibpointstructure.h"

#include "gmlibsceneloaderdatadescription.h"

// stl
#include <iostream>

GMlibPointStructure::GMlibPointStructure()
  : ODDL::Structure(int(GMStructTypes::GMlibPoint)){

  std::cout << "Constructing a GMlibPointStructure object" << int(GMStructTypes::GMlibPoint)<< std::endl;
}

bool
GMlibPointStructure::ValidateSubstructure(
    const ODDL::DataDescription *dataDescription,
    const ODDL::Structure *structure) const{

  std::cout << "subtype of " << GetStructureType() << " is " << structure->GetStructureType() << std::endl;
  return structure->GetStructureType() == ODDL::kDataFloat ;
}
