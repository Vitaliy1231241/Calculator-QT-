#include "binarymathhelper.h"

void BinaryMathHelper::reset() {
   hasLValue = false;
   hasRValue = false;
   lvalue = 0.0;
   rvalue = 0.0;
   result = 0;
}

BinaryMathHelper::BinaryMathHelper(double lvalue, double rvalue) : lvalue(lvalue), rvalue(rvalue), result(0),
                                                                   hasLValue(true), hasRValue(true) {}

void BinaryMathHelper::performOperation(Operator op) {
    switch (op) {
    case ADD:
        add();
        break;
    case SUBTRACT:
        subtract();
        break;
    case MULTIPLY:
        multiply();
        break;
    case DIVIDE:
        try {
            divide();
        } catch (std::runtime_error & e) {
            throw;
        }
        break;
    default:
        // Ignore --> Return lvalue
        result = lvalue;
    }
}

double BinaryMathHelper::getResult() const {
    return result;
}
