
#include <execinfo.h>
#include <cstdlib>
#include <iostream>
#include "ExceptionHandler.h"

void ExceptionHandler::handle() {
    void *trace_elems[20];
    int trace_elem_count(backtrace(trace_elems, 20));
    char **stack_syms(backtrace_symbols(trace_elems, trace_elem_count));
    for (int i = 0; i < trace_elem_count; ++i) {
        std::cerr << stack_syms[i] << "\n";
    }
    free(stack_syms);
    exit(1);
}
