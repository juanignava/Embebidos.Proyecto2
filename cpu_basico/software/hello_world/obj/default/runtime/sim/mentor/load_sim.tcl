# ------------------------------------------------------------------------------
# Top Level Simulation Script to source msim_setup.tcl
# ------------------------------------------------------------------------------
set QSYS_SIMDIR obj/default/runtime/sim
source msim_setup.tcl
# Copy generated memory initialization hex and dat file(s) to current directory
file copy -force c:/quartus_embebidos/cpu_basico/software/hello_world/mem_init/hdl_sim/sistema_RAM.dat ./ 
file copy -force c:/quartus_embebidos/cpu_basico/software/hello_world/mem_init/sistema_RAM.hex ./ 
