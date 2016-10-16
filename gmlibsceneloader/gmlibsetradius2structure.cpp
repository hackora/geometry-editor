#include "gmlibsetradius2structure.h"

#include "gmlibsceneloaderdatadescription.h"

// stl
#include <iostream>

GMlibSetRad2Structure::GMlibSetRad2Structure()
  : ODDL::Structure(int(GMStructTypes::GMlibSetRad2)){

  std::cout << "Constructing a GMlibSetRad2Structure object" << int(GMStructTypes::GMlibSetRad2)<< std::endl;
}

bool
GMlibSetRad2Structure::ValidateSubstructure(
    const ODDL::DataDescription *dataDescription,
    const ODDL::Structure *structure) const{

    std::cout << "subtype of " << GetStructureType() << " is " << structure->GetStructureType() << std::endl;
    return structure->GetStructureType() == ODDL::kDataFloat;

}
