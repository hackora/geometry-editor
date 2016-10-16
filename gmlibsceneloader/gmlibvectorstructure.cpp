#include "gmlibvectorstructure.h"

#include "gmlibsceneloaderdatadescription.h"

// stl
#include <iostream>

GMlibVectorStructure::GMlibVectorStructure()
  : ODDL::Structure(int(GMStructTypes::GMlibVector)){

  std::cout << "Constructing a GMlibVectorStructure object" << int(GMStructTypes::GMlibVector)<< std::endl;
}

bool
GMlibVectorStructure::ValidateSubstructure(
    const ODDL::DataDescription *dataDescription,
    const ODDL::Structure *structure) const{

  std::cout << "subtype of " << GetStructureType() << " is " << structure->GetStructureType() << std::endl;
  return structure->GetStructureType() == ODDL::kDataFloat;
}
