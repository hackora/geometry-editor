#ifndef GMLIBSETWHEELSTRUCTURE_H
#define GMLIBSETWHEELSTRUCTURE_H


#include "../openddl/openddl.h"

class GMlibSetWheelStructure : public ODDL::Structure {
public:
  GMlibSetWheelStructure();
  ~GMlibSetWheelStructure() = default;

  bool ValidateSubstructure(const ODDL::DataDescription *dataDescription, const Structure *structure) const;
};

#endif // GMLIBSETWHEELSTRUCTURE_H
