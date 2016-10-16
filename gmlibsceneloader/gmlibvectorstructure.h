#ifndef GMLIBVECTORSTRUCTURE_H
#define GMLIBVECTORSTRUCTURE_H


#include "../openddl/openddl.h"

class GMlibVectorStructure : public ODDL::Structure {
public:
  GMlibVectorStructure();
  ~GMlibVectorStructure() = default;

  bool ValidateSubstructure(const ODDL::DataDescription *dataDescription, const Structure *structure) const;
};

#endif // GMLIBVECTORSTRUCTURE_H
