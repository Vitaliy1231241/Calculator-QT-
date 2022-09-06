#ifndef ABSTRACTMATHHELPER_H
#define ABSTRACTMATHHELPER_H

#include "operator.h"

class AbstractMathHelper {
public:
    explicit AbstractMathHelper() {}
    ~AbstractMathHelper() {}

    virtual void performOperation(Operator op) = 0;
    virtual double getResult() const = 0;
};

#endif // ABSTRACTMATHHELPER_H
