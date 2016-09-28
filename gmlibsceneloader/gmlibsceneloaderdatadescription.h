#ifndef GMLIBSCENELOADERDATADESCRIPTION_H
#define GMLIBSCENELOADERDATADESCRIPTION_H


#include "../openddl/openddl.h"



enum class GMStructTypes {
  GMlibVersion = ODDL::mc_cast('G','M','V','N')
};




class GMlibSceneLoaderDataDescription : public ODDL::DataDescription{
public:
  using DataDescription::DataDescription;


  ODDL::Structure* CreateStructure(const ODDL::String &identifier) const override;
};

#endif // GMLIBSCENELOADERDATADESCRIPTION_H
