#include "gmlibsetlightedstructure.h"

#include "gmlibsceneloaderdatadescription.h"

// stl
#include <iostream>

GMlibSetLightedStructure::GMlibSetLightedStructure()
  : ODDL::Structure(int(GMStructTypes::GMlibSetLighted)){

  std::cout << "Constructing a GMlibSetLightedStructure object" << int(GMStructTypes::GMlibSetLighted)<< std::endl;
}

bool
GMlibSetLightedStructure::ValidateSubstructure(
    const ODDL::DataDescription *dataDescription,
    const ODDL::Structure *structure) const{

    std::cout << "subtype of " << GetStructureType() << " is " << structure->GetStructureType() << std::endl;
    return structure->GetStructureType() == ODDL::kDataBool ;
}
