#ifndef GMLIBPSURFDATASTRUCTURE_H
#define GMLIBPSURFDATASTRUCTURE_H


#include "../openddl/openddl.h"

class GMlibPSurfDataStructure : public ODDL::Structure {
public:
  GMlibPSurfDataStructure();
  ~GMlibPSurfDataStructure() = default;

  bool ValidateSubstructure(const ODDL::DataDescription *dataDescription, const Structure *structure) const;
};

#endif // GMLIBPSURFDATASTRUCTURE_H
