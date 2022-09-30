// alarmSystem_tb.v

// Generated using ACDS version 20.1 720

`timescale 1 ps / 1 ps
module alarmSystem_tb (
	);

	wire        alarmsystem_inst_clk_bfm_clk_clk;              // alarmSystem_inst_clk_bfm:clk -> [alarmSystem_inst:clk_clk, alarmSystem_inst_reset_bfm:clk]
	wire        alarmsystem_inst_alarm_export;                 // alarmSystem_inst:alarm_export -> alarmSystem_inst_alarm_bfm:sig_export
	wire  [0:0] alarmsystem_inst_btn_down_bfm_conduit_export;  // alarmSystem_inst_btn_down_bfm:sig_export -> alarmSystem_inst:btn_down_export
	wire  [0:0] alarmsystem_inst_btn_set_bfm_conduit_export;   // alarmSystem_inst_btn_set_bfm:sig_export -> alarmSystem_inst:btn_set_export
	wire  [0:0] alarmsystem_inst_btn_up_bfm_conduit_export;    // alarmSystem_inst_btn_up_bfm:sig_export -> alarmSystem_inst:btn_up_export
	wire  [7:0] alarmsystem_inst_display_h0_export;            // alarmSystem_inst:display_h0_export -> alarmSystem_inst_display_h0_bfm:sig_export
	wire  [7:0] alarmsystem_inst_display_h1_export;            // alarmSystem_inst:display_h1_export -> alarmSystem_inst_display_h1_bfm:sig_export
	wire  [7:0] alarmsystem_inst_display_m0_export;            // alarmSystem_inst:display_m0_export -> alarmSystem_inst_display_m0_bfm:sig_export
	wire  [7:0] alarmsystem_inst_display_m1_export;            // alarmSystem_inst:display_m1_export -> alarmSystem_inst_display_m1_bfm:sig_export
	wire  [7:0] alarmsystem_inst_display_s0_export;            // alarmSystem_inst:display_s0_export -> alarmSystem_inst_display_s0_bfm:sig_export
	wire  [7:0] alarmsystem_inst_display_s1_export;            // alarmSystem_inst:display_s1_export -> alarmSystem_inst_display_s1_bfm:sig_export
	wire  [0:0] alarmsystem_inst_swc_alarm_bfm_conduit_export; // alarmSystem_inst_swc_alarm_bfm:sig_export -> alarmSystem_inst:swc_alarm_export
	wire  [0:0] alarmsystem_inst_swc_sel_bfm_conduit_export;   // alarmSystem_inst_swc_sel_bfm:sig_export -> alarmSystem_inst:swc_sel_export
	wire        alarmsystem_inst_reset_bfm_reset_reset;        // alarmSystem_inst_reset_bfm:reset -> alarmSystem_inst:reset_reset_n

	alarmSystem alarmsystem_inst (
		.alarm_export      (alarmsystem_inst_alarm_export),                 //      alarm.export
		.btn_down_export   (alarmsystem_inst_btn_down_bfm_conduit_export),  //   btn_down.export
		.btn_set_export    (alarmsystem_inst_btn_set_bfm_conduit_export),   //    btn_set.export
		.btn_up_export     (alarmsystem_inst_btn_up_bfm_conduit_export),    //     btn_up.export
		.clk_clk           (alarmsystem_inst_clk_bfm_clk_clk),              //        clk.clk
		.display_h0_export (alarmsystem_inst_display_h0_export),            // display_h0.export
		.display_h1_export (alarmsystem_inst_display_h1_export),            // display_h1.export
		.display_m0_export (alarmsystem_inst_display_m0_export),            // display_m0.export
		.display_m1_export (alarmsystem_inst_display_m1_export),            // display_m1.export
		.display_s0_export (alarmsystem_inst_display_s0_export),            // display_s0.export
		.display_s1_export (alarmsystem_inst_display_s1_export),            // display_s1.export
		.reset_reset_n     (alarmsystem_inst_reset_bfm_reset_reset),        //      reset.reset_n
		.swc_alarm_export  (alarmsystem_inst_swc_alarm_bfm_conduit_export), //  swc_alarm.export
		.swc_sel_export    (alarmsystem_inst_swc_sel_bfm_conduit_export)    //    swc_sel.export
	);

	altera_conduit_bfm alarmsystem_inst_alarm_bfm (
		.sig_export (alarmsystem_inst_alarm_export)  // conduit.export
	);

	altera_conduit_bfm_0002 alarmsystem_inst_btn_down_bfm (
		.sig_export (alarmsystem_inst_btn_down_bfm_conduit_export)  // conduit.export
	);

	altera_conduit_bfm_0002 alarmsystem_inst_btn_set_bfm (
		.sig_export (alarmsystem_inst_btn_set_bfm_conduit_export)  // conduit.export
	);

	altera_conduit_bfm_0002 alarmsystem_inst_btn_up_bfm (
		.sig_export (alarmsystem_inst_btn_up_bfm_conduit_export)  // conduit.export
	);

	altera_avalon_clock_source #(
		.CLOCK_RATE (50000000),
		.CLOCK_UNIT (1)
	) alarmsystem_inst_clk_bfm (
		.clk (alarmsystem_inst_clk_bfm_clk_clk)  // clk.clk
	);

	altera_conduit_bfm_0003 alarmsystem_inst_display_h0_bfm (
		.sig_export (alarmsystem_inst_display_h0_export)  // conduit.export
	);

	altera_conduit_bfm_0003 alarmsystem_inst_display_h1_bfm (
		.sig_export (alarmsystem_inst_display_h1_export)  // conduit.export
	);

	altera_conduit_bfm_0003 alarmsystem_inst_display_m0_bfm (
		.sig_export (alarmsystem_inst_display_m0_export)  // conduit.export
	);

	altera_conduit_bfm_0003 alarmsystem_inst_display_m1_bfm (
		.sig_export (alarmsystem_inst_display_m1_export)  // conduit.export
	);

	altera_conduit_bfm_0003 alarmsystem_inst_display_s0_bfm (
		.sig_export (alarmsystem_inst_display_s0_export)  // conduit.export
	);

	altera_conduit_bfm_0003 alarmsystem_inst_display_s1_bfm (
		.sig_export (alarmsystem_inst_display_s1_export)  // conduit.export
	);

	altera_avalon_reset_source #(
		.ASSERT_HIGH_RESET    (0),
		.INITIAL_RESET_CYCLES (50)
	) alarmsystem_inst_reset_bfm (
		.reset (alarmsystem_inst_reset_bfm_reset_reset), // reset.reset_n
		.clk   (alarmsystem_inst_clk_bfm_clk_clk)        //   clk.clk
	);

	altera_conduit_bfm_0002 alarmsystem_inst_swc_alarm_bfm (
		.sig_export (alarmsystem_inst_swc_alarm_bfm_conduit_export)  // conduit.export
	);

	altera_conduit_bfm_0002 alarmsystem_inst_swc_sel_bfm (
		.sig_export (alarmsystem_inst_swc_sel_bfm_conduit_export)  // conduit.export
	);

endmodule