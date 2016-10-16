#ifndef GMLIBPTORUSSTRUCTURE_H
#define GMLIBPTORUSSTRUCTURE_H


#include "../openddl/openddl.h"

class GMlibPTorusStructure : public ODDL::Structure {
public:
  GMlibPTorusStructure();
  ~GMlibPTorusStructure() = default;

  bool ValidateSubstructure(const ODDL::DataDescription *dataDescription, const Structure *structure) const;
};

#endif // GMLIBPTORUSSTRUCTURE_H
