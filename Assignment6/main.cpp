#include <iostream>

#include "processor.h"

int main() {
processor *test = new processor;
    test->start_parse();
    test->topword();
    test->topdigits();
    test->topcharacters();

delete test;
return 0;
}
