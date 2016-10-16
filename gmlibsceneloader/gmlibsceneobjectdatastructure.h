#ifndef GMLIBSCENEOBJECTDATASTRUCTURE_H
#define GMLIBSCENEOBJECTDATASTRUCTURE_H


#include "../openddl/openddl.h"

class GMlibSceneObjectDataStructure : public ODDL::Structure {
public:
  GMlibSceneObjectDataStructure();
  ~GMlibSceneObjectDataStructure() = default;

  bool ValidateSubstructure(const ODDL::DataDescription *dataDescription, const Structure *structure) const;
};

#endif // GMLIBSCENEOBJECTDATASTRUCTURE_H
