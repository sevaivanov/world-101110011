#ifndef PGTREE1_H
#define PGTREE1_H

#include "PGObject.h"
#include "PGTree.h"
#include "GLObject.h"
#include "RotationalObject.h"
#include "Vector.h"

class PGTree1 : public PGTree {
public:
    PGTree1(Point offset, float radius = 0.05f, float steps = 0.01, float height = 0.5f);
};

#endif /* PGTREE1_H */

