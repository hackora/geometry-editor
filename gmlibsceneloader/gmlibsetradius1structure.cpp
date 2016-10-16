#include "gmlibsetradius1structure.h"

#include "gmlibsceneloaderdatadescription.h"

// stl
#include <iostream>

GMlibSetRad1Structure::GMlibSetRad1Structure()
  : ODDL::Structure(int(GMStructTypes::GMlibSetRad1)){

  std::cout << "Constructing a GMlibSetRad1Structure object" << int(GMStructTypes::GMlibSetRad1)<< std::endl;
}

bool
GMlibSetRad1Structure::ValidateSubstructure(
    const ODDL::DataDescription *dataDescription,
    const ODDL::Structure *structure) const{

    std::cout << "subtype of " << GetStructureType() << " is " << structure->GetStructureType() << std::endl;
    return structure->GetStructureType() == ODDL::kDataFloat;
}
