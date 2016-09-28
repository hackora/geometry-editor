#include "gmlibversionstructure.h"

#include "gmlibsceneloaderdatadescription.h"

// stl
#include <iostream>

GMlibVersionStructure::GMlibVersionStructure()
  : ODDL::Structure(int(GMStructTypes::GMlibVersion)){

  std::cout << "Constructing a GMlibVersionStructure object" << std::endl;
}

bool
GMlibVersionStructure::ValidateSubstructure(
    const ODDL::DataDescription *dataDescription,
    const ODDL::Structure *structure) const{

  std::cout << "subtype of " << GetStructureType() << " is " << structure->GetStructureType() << std::endl;
  return structure->GetStructureType() == ODDL::kDataInt32;
}
