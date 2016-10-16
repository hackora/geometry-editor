#ifndef GMLIBSETRAD2STRUCTURE_H
#define GMLIBSETRAD2STRUCTURE_H


#include "../openddl/openddl.h"

class GMlibSetRad2Structure : public ODDL::Structure {
public:
  GMlibSetRad2Structure();
  ~GMlibSetRad2Structure() = default;

  bool ValidateSubstructure(const ODDL::DataDescription *dataDescription, const Structure *structure) const;
};

#endif // GMLIBSETRAD2STRUCTURE_H
