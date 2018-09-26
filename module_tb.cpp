#include <stdlib.h>
#include "Vmodule_impl.h"
#include "verilated.h"
#include <verilated_vcd_c.h>

int main(int argc, char **argv) {
    // Initialize Verilators variables
    Verilated::commandArgs(argc, argv);

    // Create an instance of our module under test
    Vmodule_impl *tb = new Vmodule_impl;

    Verilated::traceEverOn(true);

    VerilatedVcdC *trace = new VerilatedVcdC;
    tb->trace(trace, 99);
    trace->open("trace.vcd");

    for(uint8_t ticks = 0; ticks != 70; ++ticks) {

        if(ticks < 34) {
            tb->din = ticks;
            tb->write = 1;
            tb->read = 0;
        } else {
            tb->din = 0;
            tb->write = 0;
            tb->read = 1;
        }


        tb->clock = 0;
        tb->eval();
        trace->dump(10*ticks);

        tb->clock = 1;
        tb->eval();
        trace->dump(10*ticks + 5);

        printf("[n_elements %d] din: %d dout: %d\n", tb->n_elements, tb->din, tb->dout);
    }

    trace->close();

    exit(EXIT_SUCCESS);
}
