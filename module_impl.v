module module_impl
(
 input x,
 input y,
 input cin,
 
 output a, 
 output cout
 );
 
assign {cout,a} =  cin + y + x;
 
endmodule
