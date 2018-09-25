TARGET = module
VC = verilator
VFLAGS = -Wall -trace -cc

.PHONY: default all clean

default: $(TARGET)
all: default

Vmodule_impl.mk: module_impl.v
	$(VC) $(VFLAGS) $^

module: Vmodule_impl.mk
	cd obj_dir && make -f Vmodule_impl.mk && cd ..
	g++ -Iobj_dir -I/usr/share/verilator/include /usr/share/verilator/include/verilated.cpp /usr/share/verilator/include/verilated_vcd_c.cpp module_tb.cpp obj_dir/Vmodule_impl__ALL.a -o module

clean:
	-rm -rf obj_dir *.vcd module
