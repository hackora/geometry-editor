#ifndef GMLIBFLOATSTRUCTURE_H
#define GMLIBFLOATSTRUCTURE_H


#include "../openddl/openddl.h"

class GMlibFloatStructure : public ODDL::Structure {
public:
  GMlibFloatStructure();
  ~GMlibFloatStructure() = default;

  bool ValidateSubstructure(const ODDL::DataDescription *dataDescription, const Structure *structure) const;
};

#endif // GMLIBFLOATSTRUCTURE_H
