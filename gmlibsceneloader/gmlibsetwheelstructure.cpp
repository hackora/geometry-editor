#include "gmlibsetwheelstructure.h"

#include "gmlibsceneloaderdatadescription.h"

// stl
#include <iostream>

GMlibSetWheelStructure::GMlibSetWheelStructure()
  : ODDL::Structure(int(GMStructTypes::GMlibSetWheel)){

  std::cout << "Constructing a GMlibSetWheelStructure object" << int(GMStructTypes::GMlibSetWheel)<< std::endl;
}

bool
GMlibSetWheelStructure::ValidateSubstructure(
    const ODDL::DataDescription *dataDescription,
    const ODDL::Structure *structure) const{

    std::cout << "subtype of " << GetStructureType() << " is " << structure->GetStructureType() << std::endl;
    return structure->GetStructureType() == ODDL::kDataFloat;
}
