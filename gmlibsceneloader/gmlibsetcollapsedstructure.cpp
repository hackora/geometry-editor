#include "gmlibsetcollapsedstructure.h"

#include "gmlibsceneloaderdatadescription.h"

// stl
#include <iostream>

GMlibSetCollapsedStructure::GMlibSetCollapsedStructure()
  : ODDL::Structure(int(GMStructTypes::GMlibSetCollapsed)){

  std::cout << "Constructing a GMlibSetCollapsedStructure object" << int(GMStructTypes::GMlibSetCollapsed)<< std::endl;
}

bool
GMlibSetCollapsedStructure::ValidateSubstructure(
    const ODDL::DataDescription *dataDescription,
    const ODDL::Structure *structure) const{

    std::cout << "subtype of " << GetStructureType() << " is " << structure->GetStructureType() << std::endl;
    return structure->GetStructureType() == ODDL::kDataBool ;
}
