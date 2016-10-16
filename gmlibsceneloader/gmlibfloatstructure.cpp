#include "gmlibfloatstructure.h"

#include "gmlibsceneloaderdatadescription.h"

// stl
#include <iostream>

GMlibFloatStructure::GMlibFloatStructure()
  : ODDL::Structure(int(GMStructTypes::GMlibFloat)){

  std::cout << "Constructing a GMlibFloatStructure object" << int(GMStructTypes::GMlibFloat)<< std::endl;
}

bool
GMlibFloatStructure::ValidateSubstructure(
    const ODDL::DataDescription *dataDescription,
    const ODDL::Structure *structure) const{

  bool valid=true;
  Structure *substructure = structure->GetFirstSubnode();
  while (substructure)
  {
    if (substructure->GetStructureType() != ODDL::kDataFloat){
      valid = false;
    }

    substructure = structure->Next();
  }

  return valid;
}
