#ifndef GMLIBEDVSTRUCTURE_H
#define GMLIBEDVSTRUCTURE_H


#include "../openddl/openddl.h"

class GMlibEDVStructure : public ODDL::Structure {
public:
  GMlibEDVStructure();
  ~GMlibEDVStructure() = default;

  bool ValidateSubstructure(const ODDL::DataDescription *dataDescription, const Structure *structure) const;
};

#endif // GMLIBEDVSTRUCTURE_H
