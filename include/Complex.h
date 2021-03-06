#ifndef HALIDE_ELEMENT_COMPLEX_H
#define HALIDE_ELEMENT_COMPLEX_H

#include <Halide.h>

namespace Halide {
namespace Element {

//
// Complex Expression
//
struct ComplexExpr {
    Expr x;
    Expr y;
};

ComplexExpr operator+(const ComplexExpr& a, const ComplexExpr& b)
{
    return {a.x+b.x, a.y+b.y};
}

ComplexExpr operator-(const ComplexExpr& a, const ComplexExpr& b)
{
    return {a.x-b.x, a.y-b.y};
}

ComplexExpr operator*(const ComplexExpr& a, const ComplexExpr& b)
{
    return {a.x*b.x - a.y*b.y, a.x*b.y + a.y*b.x};
}

} // Element
} // Halide

#endif