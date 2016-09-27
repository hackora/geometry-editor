#include "gmlibsceneloaderdatadescription.h"

#include "gmlibversionstructure.h"

ODDL::Structure *GMlibSceneLoaderDataDescription::CreateStructure(
    const ODDL::String &identifier) const {

  if(identifier == "GMlibVersion") {
    return new GMlibVersionStructure;
  }

  return nullptr;
}
