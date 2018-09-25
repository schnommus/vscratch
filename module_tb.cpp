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

    for(uint8_t ticks = 0; ticks != 8; ++ticks) {

        tb->x   = !!(ticks & (1 << 0));
        tb->y   = !!(ticks & (1 << 1));
        tb->cin = !!(ticks & (1 << 2));
        tb->eval();

        printf("%d + %d + %d = %d%d\n",
                tb->x, tb->y, tb->cin,
                tb->cout, tb->a);

        trace->dump(10*ticks);
    }

    trace->close();

    exit(EXIT_SUCCESS);
}
