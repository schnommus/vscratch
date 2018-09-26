module module_impl
(
    input clock,

    input read,
    input write,

    input [7:0] din,
    output reg [7:0] dout,

    output reg [5:0] n_elements
);

reg [7:0] fifo_mem [0:31];

reg [4:0] read_ptr    = 5'b00000;
reg [4:0] write_ptr   = 5'b00000;

wire empty;
wire full;

assign empty = n_elements == 0;
assign full  = n_elements == 32;

always @(posedge clock)
begin
    if( read && !empty )
    begin
        dout <= fifo_mem[read_ptr];
        read_ptr <= read_ptr + 1;
        n_elements <= n_elements - 1;
    end
    if( write && !full )
    begin
        fifo_mem[write_ptr] <= din;
        write_ptr <= write_ptr + 1;
        n_elements <= n_elements + 1;
    end
end

endmodule
