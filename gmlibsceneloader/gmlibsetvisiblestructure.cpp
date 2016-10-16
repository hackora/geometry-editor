#include "gmlibsetvisiblestructure.h"

#include "gmlibsceneloaderdatadescription.h"

// stl
#include <iostream>

GMlibSetVisibleStructure::GMlibSetVisibleStructure()
  : ODDL::Structure(int(GMStructTypes::GMlibSetVisible)){

  std::cout << "Constructing a GMlibSetVisibleStructure object" << int(GMStructTypes::GMlibSetVisible)<< std::endl;
}

bool
GMlibSetVisibleStructure::ValidateSubstructure(
    const ODDL::DataDescription *dataDescription,
    const ODDL::Structure *structure) const{

    std::cout << "subtype of " << GetStructureType() << " is " << structure->GetStructureType() << std::endl;
    return structure->GetStructureType() == ODDL::kDataBool ;
}
