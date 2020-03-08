#include <iostream>
#include <stdio.h>

struct Options { 
    enum opt {OPT_0, OPT_1};
};

template<Options::opt option = Options::OPT_0>
class Calculate
{
public:
    Calculate(int test) 
    :_test(test)
    {}
    
    void Calc()
    {
        std::cout << "Calc default" << std::endl;
    }

private:
    int _test;
};

template<>
void Calculate<Options::OPT_1>::Calc()
{
    std::cout << "Calc for OPT_1" << std::endl;
}

typedef Calculate<> Calc_t;