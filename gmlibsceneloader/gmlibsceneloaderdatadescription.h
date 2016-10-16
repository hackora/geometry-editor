#ifndef GMLIBSCENELOADERDATADESCRIPTION_H
#define GMLIBSCENELOADERDATADESCRIPTION_H


#include "../openddl/openddl.h"



enum class GMStructTypes {
  GMlibVersion = ODDL::mc_cast('G','M','V','N'),
  GMlibCamera =  ODDL::mc_cast('G','G','V','N'),
  GMlibSceneObjectData = ODDL::mc_cast('G','G','G','N'),
  GMlibSet = ODDL::mc_cast('G','G','G','G'),
  GMlibSetCollapsed = ODDL::mc_cast('G','G','G','L'),
  GMlibSetLighted = ODDL::mc_cast('G','G','L','L'),
  GMlibSetVisible = ODDL::mc_cast('G','L','G','L'),
  GMlibPoint = ODDL::mc_cast('G','M','N','N'),
  GMlibVector = ODDL::mc_cast('G','N','N','N'),
  GMlibFloat = ODDL::mc_cast('M','N','N','N'),
  GMlibPTorus = ODDL::mc_cast('P','T','R','S'),
  GMlibPTorusData = ODDL::mc_cast('P','T','R','D'),
  GMlibPSurfData = ODDL::mc_cast('S','R','F','D'),
  GMlibEDV = ODDL::mc_cast('E','D','V','S'),
  GMlibReplot = ODDL::mc_cast('R','P','L','T'),
  GMlibSetRad1 = ODDL::mc_cast('S','R','A','D'),
  GMlibSetRad2 = ODDL::mc_cast('T','R','A','D'),
  GMlibSetWheel = ODDL::mc_cast('W','E','E','L'),




};




class GMlibSceneLoaderDataDescription : public ODDL::DataDescription{
public:
  using DataDescription::DataDescription;


  ODDL::Structure* CreateStructure(const ODDL::String &identifier) const override;
};

#endif // GMLIBSCENELOADERDATADESCRIPTION_H
