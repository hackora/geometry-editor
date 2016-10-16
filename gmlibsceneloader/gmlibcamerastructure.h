#ifndef GMLIBCAMERASTRUCTURE_H
#define GMLIBCAMERASTRUCTURE_H


#include "../openddl/openddl.h"

class GMlibCameraStructure : public ODDL::Structure {
public:
  GMlibCameraStructure();
  ~GMlibCameraStructure() = default;

  bool ValidateSubstructure(const ODDL::DataDescription *dataDescription, const Structure *structure) const;
};

#endif // GMLIBCAMERASTRUCTURE_H
