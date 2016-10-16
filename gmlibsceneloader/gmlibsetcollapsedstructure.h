#ifndef GMLIBSETCOLLAPSEDSTRUCTURE_H
#define GMLIBSETCOLLAPSEDSTRUCTURE_H


#include "../openddl/openddl.h"

class GMlibSetCollapsedStructure : public ODDL::Structure {
public:
  GMlibSetCollapsedStructure();
  ~GMlibSetCollapsedStructure() = default;

  bool ValidateSubstructure(const ODDL::DataDescription *dataDescription, const Structure *structure) const;
};

#endif // GMLIBSETCOLLAPSEDSTRUCTURE_H
