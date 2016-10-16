#ifndef GMLIBPOINTSTRUCTURE_H
#define GMLIBPOINTSTRUCTURE_H


#include "../openddl/openddl.h"

class GMlibPointStructure : public ODDL::Structure {
public:
  GMlibPointStructure();
  ~GMlibPointStructure() = default;

  bool ValidateSubstructure(const ODDL::DataDescription *dataDescription, const Structure *structure) const;
};

#endif // GMLIBPointSTRUCTURE_H
