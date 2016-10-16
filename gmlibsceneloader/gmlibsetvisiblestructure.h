#ifndef GMLIBSETVISIBLESTRUCTURE_H
#define GMLIBSETCOLLAPSEDSTRUCTURE_H


#include "../openddl/openddl.h"

class GMlibSetVisibleStructure : public ODDL::Structure {
public:
  GMlibSetVisibleStructure();
  ~GMlibSetVisibleStructure() = default;

  bool ValidateSubstructure(const ODDL::DataDescription *dataDescription, const Structure *structure) const;
};

#endif // GMLIBSETVISIBLESTRUCTURE_H
