#include "gmlibsceneobjectdatastructure.h"

#include "gmlibsceneloaderdatadescription.h"

// stl
#include <iostream>

GMlibSceneObjectDataStructure::GMlibSceneObjectDataStructure()
  : ODDL::Structure(int(GMStructTypes::GMlibSceneObjectData)){

  std::cout << "Constructing a GMlibSceneObjectDataStructure object" << int(GMStructTypes::GMlibSceneObjectData)<< std::endl;
}

bool
GMlibSceneObjectDataStructure::ValidateSubstructure(
    const ODDL::DataDescription *dataDescription,
    const ODDL::Structure *structure) const{

    bool valid=true;
    Structure *substructure = structure->GetFirstSubnode();
    while (substructure)
    {
      if ((substructure->GetStructureType() != int(GMStructTypes::GMlibSet)) && (substructure->GetStructureType() != int(GMStructTypes::GMlibSetCollapsed))
             && (substructure->GetStructureType() != int(GMStructTypes::GMlibSetVisible)) && (substructure->GetStructureType() != int(GMStructTypes::GMlibSetLighted)))
      {
        valid = false;
      }

      substructure = structure->Next();
    }

    return valid;
}
