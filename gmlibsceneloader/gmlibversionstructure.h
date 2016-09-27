#ifndef GMLIBVERSIONSTRUCTURE_H
#define GMLIBVERSIONSTRUCTURE_H


#include "../openddl/openddl.h"

class GMlibVersionStructure : public ODDL::Structure {
public:
  GMlibVersionStructure();
  ~GMlibVersionStructure() = default;

  bool ValidateSubstructure(const ODDL::DataDescription *dataDescription, const Structure *structure) const;
};

#endif // GMLIBVERSIONSTRUCTURE_H
