#ifndef GMLIBSETLIGHTEDSTRUCTURE_H
#define GMLIBSETLIGHTEDSTRUCTURE_H


#include "../openddl/openddl.h"

class GMlibSetLightedStructure : public ODDL::Structure {
public:
  GMlibSetLightedStructure();
  ~GMlibSetLightedStructure() = default;

  bool ValidateSubstructure(const ODDL::DataDescription *dataDescription, const Structure *structure) const;
};

#endif // GMLIBSETLIGHTEDSTRUCTURE_H
