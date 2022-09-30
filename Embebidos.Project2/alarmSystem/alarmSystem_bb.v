
module alarmSystem (
	clk_clk,
	reset_reset_n,
	display_h1_export,
	display_h0_export,
	display_m1_export,
	display_m0_export,
	display_s1_export,
	display_s0_export,
	alarm_export,
	btn_set_export,
	btn_up_export,
	btn_down_export,
	swc_sel_export,
	swc_alarm_export);	

	input		clk_clk;
	input		reset_reset_n;
	output	[7:0]	display_h1_export;
	output	[7:0]	display_h0_export;
	output	[7:0]	display_m1_export;
	output	[7:0]	display_m0_export;
	output	[7:0]	display_s1_export;
	output	[7:0]	display_s0_export;
	output		alarm_export;
	input		btn_set_export;
	input		btn_up_export;
	input		btn_down_export;
	input		swc_sel_export;
	input		swc_alarm_export;
endmodule
