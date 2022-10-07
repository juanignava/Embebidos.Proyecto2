# Minimum SoC design for alarm clock

#### How to run?

1. Open Platform designer

2. Hit Tools and Nios II Command Shell, this opens a terminal, open two of them

3. In the first terminal go to `/cygdrive/c/quartus_embebidos/alarm_4_10/Quartus/output_files`

4. Connect the FPGA to the power and to the computer and then run `nios2-configure-sof -d 2 alarm_clk.sof`

5. Run `jtagconfig`

6. Go back to the path `quartus_embebidos/alarm_4_10/software/alarm_clk`

7. In the second terminal go to `/cygdrive/c/quartus_embebidos/alarm_4_10/software/alarm_clk` and run `make`

8. Then in the second terminal run `nios2-download --go alarm_clk.elf` make sure the reset in the FPGA is off

9. In the first terminal run ``

#### Important links

- Guide for making a hello world: https://youtu.be/1e3h6zHxcpU

- For downloading eclipse for Nios II: https://www.intel.com/content/www/us/en/support/programmable/articles/000086893.html

- If you get an error message like "Failed to execute wsl dos2unix create-this-bsp...." this is solved by: https://www.intel.com/content/www/us/en/support/programmable/articles/000086893.html and https://www.terasic.com.tw/wiki/Getting_Start_Install_WSL

- Platform design tutorial: https://www.intel.com/content/www/us/en/docs/programmable/683609/21-3/creating-a-system-with.html
