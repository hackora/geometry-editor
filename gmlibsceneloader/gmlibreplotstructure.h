#ifndef GMLIBREPLOTSTRUCTURE_H
#define GMLIBREPLOTSTRUCTURE_H


#include "../openddl/openddl.h"

class GMlibReplotStructure : public ODDL::Structure {
public:
  GMlibReplotStructure();
  ~GMlibReplotStructure() = default;

  bool ValidateSubstructure(const ODDL::DataDescription *dataDescription, const Structure *structure) const;
};

#endif // GMLIBREPLOTSTRUCTURE_H
