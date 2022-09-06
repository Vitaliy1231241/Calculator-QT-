#ifndef BINARY_MATHHELPER_H
#define BINARY_MATHHELPER_H

#include "abstractmathhelper.h"
#include <stdexcept>

/**
 * @brief The BinaryMathHelper class performs binary mathematical operations
 * @implements AbstractMathHelper
 */
class BinaryMathHelper : public AbstractMathHelper {
    double lvalue;
    double rvalue;
    double result;

    bool hasLValue;
    bool hasRValue;

    void add() {
        result = lvalue + rvalue;
    }

    void subtract() {
        result = lvalue - rvalue;
    }

    void multiply() {
        result = lvalue * rvalue;
    }

    void divide() {
        if (rvalue != 0) {
            result = lvalue / rvalue;
        } else {
            throw std::runtime_error("Unable to divide by zero.");
        }
    }

public:
    void setLValue(double lvalue) {
        this->lvalue = lvalue;
        hasLValue = true;
    }

    void setRValue(double rvalue) {
        this->rvalue = rvalue;
        hasRValue = true;
    }

    double getLValue() const noexcept {
        return lvalue;
    }

    double getRValue() const noexcept {
        return lvalue;
    }

    bool hasLvalue() const {
        return hasLValue;
    }

    bool hasRvalue() const {
        return hasRValue;
    }

    void reset();

    BinaryMathHelper() : lvalue(0), rvalue(0), result(0), hasLValue(false), hasRValue(false) {}
    BinaryMathHelper(double lvalue, double rvalue);
    virtual void performOperation(Operator op) override;
    virtual double getResult() const override;
};

#endif // BINARY_MATHHELPER_H
