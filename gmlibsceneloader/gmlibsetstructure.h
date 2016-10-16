#ifndef GMLIBSETSTRUCTURE_H
#define GMLIBSETSTRUCTURE_H


#include "../openddl/openddl.h"

class GMlibSetStructure : public ODDL::Structure {
public:
  GMlibSetStructure();
  ~GMlibSetStructure() = default;

  bool ValidateSubstructure(const ODDL::DataDescription *dataDescription, const Structure *structure) const;
};

#endif // GMLIBSETSTRUCTURE_H
