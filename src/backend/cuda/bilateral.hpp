#include <Array.hpp>

namespace cuda
{

template<typename T, bool isColor>
Array<T> * bilateral(const Array<T> &in, const float &s_sigma, const float &c_sigma);

}
