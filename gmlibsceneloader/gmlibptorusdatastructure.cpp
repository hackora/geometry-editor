#include "gmlibptorusdatastructure.h"

#include "gmlibsceneloaderdatadescription.h"

// stl
#include <iostream>

GMlibPTorusDataStructure::GMlibPTorusDataStructure()
  : ODDL::Structure(int(GMStructTypes::GMlibPTorusData)){

  std::cout << "Constructing a GMlibPTorusDataStructure object" << int(GMStructTypes::GMlibPTorusData)<< std::endl;
}

bool
GMlibPTorusDataStructure::ValidateSubstructure(
    const ODDL::DataDescription *dataDescription,
    const ODDL::Structure *structure) const{

  std::cout << "subtype of " << GetStructureType() << " is " << structure->GetStructureType() << std::endl;
  return (structure->GetStructureType() == int(GMStructTypes::GMlibPTorus) || structure->GetStructureType() == int(GMStructTypes::GMlibSetRad1)
          || structure->GetStructureType() == int(GMStructTypes::GMlibSetRad2) || structure->GetStructureType() == int(GMStructTypes::GMlibSetWheel));
}
