#include "gmlibenabledefvisualstructure.h"

#include "gmlibsceneloaderdatadescription.h"

// stl
#include <iostream>

GMlibEDVStructure::GMlibEDVStructure()
  : ODDL::Structure(int(GMStructTypes::GMlibEDV)){

  std::cout << "Constructing a GMlibEDVStructure object" << int(GMStructTypes::GMlibEDV)<< std::endl;
}

bool
GMlibEDVStructure::ValidateSubstructure(
    const ODDL::DataDescription *dataDescription,
    const ODDL::Structure *structure) const{
    std::cout << "subtype of " << GetStructureType() << " is " << structure->GetStructureType() << std::endl;
    return structure->GetStructureType() == ODDL::kDataBool;
}
