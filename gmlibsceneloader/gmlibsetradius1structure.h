#ifndef GMLIBSETRAD1STRUCTURE_H
#define GMLIBSETRAD1STRUCTURE_H


#include "../openddl/openddl.h"

class GMlibSetRad1Structure : public ODDL::Structure {
public:
  GMlibSetRad1Structure();
  ~GMlibSetRad1Structure() = default;

  bool ValidateSubstructure(const ODDL::DataDescription *dataDescription, const Structure *structure) const;
};

#endif // GMLIBSETRAD1STRUCTURE_H
