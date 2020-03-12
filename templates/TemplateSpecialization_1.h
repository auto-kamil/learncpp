#include <iostream>
#include <stdio.h>

class Calculate
{
public:
    enum Options { OPT_0, OPT_1};

    Calculate(int test) 
    :_test(test)
    {}
    
    template<Options option = Options::OPT_0>
    void Calc()
    {
        std::cout << "Calc default" << std::endl;
    }

private:
    int _test;
};

template<>
<<<<<<< HEAD
void Calculate::Calc<Calculate::OPT_1>()
=======
inline void Calculate::Calc<Calculate::OPT_1>()
>>>>>>> Template specification C98 and modern style
{
    std::cout << "Calc for OPT_1" << std::endl;
}

using Calc_t = Calculate;