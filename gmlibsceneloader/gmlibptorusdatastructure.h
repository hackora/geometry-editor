#ifndef GMLIBPTORUSDATASTRUCTURE_H
#define GMLIBPTORUSDATASTRUCTURE_H


#include "../openddl/openddl.h"

class GMlibPTorusDataStructure : public ODDL::Structure {
public:
  GMlibPTorusDataStructure();
  ~GMlibPTorusDataStructure() = default;

  bool ValidateSubstructure(const ODDL::DataDescription *dataDescription, const Structure *structure) const;
};

#endif // GMLIBPTORUSDATASTRUCTURE_H
