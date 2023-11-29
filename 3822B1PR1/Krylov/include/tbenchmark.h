#ifndef __TBENCHMARK_H__
#define __TBENCHMARK_H__

#include <chrono>

template<class unit>
class TSimpleBenchmark
{
private:
    std::chrono::high_resolution_clock::time_point begin;
public:
    TSimpleBenchmark()
            : begin(std::chrono::high_resolution_clock::now())
    {}

    unit elapsed() const
    {
        return std::chrono::duration_cast<unit>
                (std::chrono::high_resolution_clock::now() - begin);
    }

    void reset()
    {
        begin = std::chrono::high_resolution_clock::now();
    }
};

#endif // __TBENCHMARK_H__
