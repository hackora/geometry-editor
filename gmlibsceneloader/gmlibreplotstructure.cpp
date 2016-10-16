#include "gmlibreplotstructure.h"

#include "gmlibsceneloaderdatadescription.h"

// stl
#include <iostream>

GMlibReplotStructure::GMlibReplotStructure()
  : ODDL::Structure(int(GMStructTypes::GMlibReplot)){

  std::cout << "Constructing a GMlibReplotStructure object" << int(GMStructTypes::GMlibReplot)<< std::endl;
}

bool
GMlibReplotStructure::ValidateSubstructure(
    const ODDL::DataDescription *dataDescription,
    const ODDL::Structure *structure) const{

    std::cout << "subtype of " << GetStructureType() << " is " << structure->GetStructureType() << std::endl;
    return structure->GetStructureType() == ODDL::kDataInt8;
}
