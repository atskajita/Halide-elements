#include <iostream>
#include "Halide.h"
#include "Element.h"

using namespace Halide;
using namespace Halide::Element;

template<typename T>
class ErodeCross : public Halide::Generator<ErodeCross<T>> {
public:
    GeneratorParam<int32_t> width{"width", 1024};
    GeneratorParam<int32_t> height{"height", 768};
    GeneratorParam<int32_t> iteration{"iteration", 2};
    ImageParam src{type_of<T>(), 2, "src"};
    GeneratorParam<int32_t> window_width{"window_width", 3, 3, 17};
    GeneratorParam<int32_t> window_height{"window_height", 3, 3, 17};

    Var x, y;

    Func build() {

        Func input("input");
        input(x, y) = src(x, y);

        RDom r(-(window_width / 2), window_width, -(window_height / 2), window_height);
        r.where(r.x == 0 || r.y == 0);
        for (int32_t i = 0; i < iteration; i++) {
            Func clamped = BoundaryConditions::repeat_edge(input, {{0, cast<int32_t>(width)}, {0, cast<int32_t>(height)}});
            Func workbuf("workbuf");
            Expr val = minimum_unroll(r, clamped(x + r.x, y + r.y));
            workbuf(x, y) = val;
            workbuf.compute_root();
            input = workbuf;
            schedule(workbuf, {width, height});
        }

        schedule(src, {width, height});
        
        return input;
    }
};

RegisterGenerator<ErodeCross<uint8_t>> erode_cross_u8{"erode_cross_u8"};
RegisterGenerator<ErodeCross<uint16_t>> erode_cross_u16{"erode_cross_u16"};
