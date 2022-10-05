# ------------------------------------------------------------------------------
# Top Level Simulation Script to source msim_setup.tcl
# ------------------------------------------------------------------------------
set QSYS_SIMDIR obj/default/runtime/sim
source msim_setup.tcl
# Copy generated memory initialization hex and dat file(s) to current directory
file copy -force C:/quartus_embebidos/alarm_4_10/software/alarm_clk/mem_init/hdl_sim/alarm_clk_RAM.dat ./ 
file copy -force C:/quartus_embebidos/alarm_4_10/software/alarm_clk/mem_init/alarm_clk_RAM.hex ./ 
