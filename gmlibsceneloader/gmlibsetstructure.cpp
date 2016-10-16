#include "gmlibsetstructure.h"

#include "gmlibsceneloaderdatadescription.h"

// stl
#include <iostream>

GMlibSetStructure::GMlibSetStructure()
  : ODDL::Structure(int(GMStructTypes::GMlibSet)){

  std::cout << "Constructing a GMlibSetStructure object" << int(GMStructTypes::GMlibSet)<< std::endl;
}

bool
GMlibSetStructure::ValidateSubstructure(
    const ODDL::DataDescription *dataDescription,
    const ODDL::Structure *structure) const{
  bool valid=true;
  Structure *substructure = structure->GetFirstSubnode();
  while (substructure)
  {
    if ((substructure->GetStructureType() != int(GMStructTypes::GMlibPoint)) && (substructure->GetStructureType() != int(GMStructTypes::GMlibVector)))
    {
      valid = false;
    }

    substructure = structure->Next();
  }

  return valid;
}
