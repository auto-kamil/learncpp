#include <iostream>
#include <stdio.h>

#define TEST_2

#if defined(TEST_1)
#include "TemplateSpecialization_0.h"

int main() {
    Calc_t calc_machine(1);
    calc_machine.Calc();
    return 0;
}

#elif defined(TEST_1)
#include "TemplateSpecialization_1.h"

int main() {
    Calc_t calc_machine(1);
    calc_machine.Calc<>();
    return 0;
}

#elif defined(TEST_2)
#include "TemplateSpecialization_2.h"

int main() {
    Calc_t calc_machine(1);
    calc_machine.Calc();
    return 0;
}

#endif