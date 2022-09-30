	component alarmSystem is
		port (
			clk_clk           : in  std_logic                    := 'X'; -- clk
			reset_reset_n     : in  std_logic                    := 'X'; -- reset_n
			display_h1_export : out std_logic_vector(7 downto 0);        -- export
			display_h0_export : out std_logic_vector(7 downto 0);        -- export
			display_m1_export : out std_logic_vector(7 downto 0);        -- export
			display_m0_export : out std_logic_vector(7 downto 0);        -- export
			display_s1_export : out std_logic_vector(7 downto 0);        -- export
			display_s0_export : out std_logic_vector(7 downto 0);        -- export
			alarm_export      : out std_logic;                           -- export
			btn_set_export    : in  std_logic                    := 'X'; -- export
			btn_up_export     : in  std_logic                    := 'X'; -- export
			btn_down_export   : in  std_logic                    := 'X'; -- export
			swc_sel_export    : in  std_logic                    := 'X'; -- export
			swc_alarm_export  : in  std_logic                    := 'X'  -- export
		);
	end component alarmSystem;

	u0 : component alarmSystem
		port map (
			clk_clk           => CONNECTED_TO_clk_clk,           --        clk.clk
			reset_reset_n     => CONNECTED_TO_reset_reset_n,     --      reset.reset_n
			display_h1_export => CONNECTED_TO_display_h1_export, -- display_h1.export
			display_h0_export => CONNECTED_TO_display_h0_export, -- display_h0.export
			display_m1_export => CONNECTED_TO_display_m1_export, -- display_m1.export
			display_m0_export => CONNECTED_TO_display_m0_export, -- display_m0.export
			display_s1_export => CONNECTED_TO_display_s1_export, -- display_s1.export
			display_s0_export => CONNECTED_TO_display_s0_export, -- display_s0.export
			alarm_export      => CONNECTED_TO_alarm_export,      --      alarm.export
			btn_set_export    => CONNECTED_TO_btn_set_export,    --    btn_set.export
			btn_up_export     => CONNECTED_TO_btn_up_export,     --     btn_up.export
			btn_down_export   => CONNECTED_TO_btn_down_export,   --   btn_down.export
			swc_sel_export    => CONNECTED_TO_swc_sel_export,    --    swc_sel.export
			swc_alarm_export  => CONNECTED_TO_swc_alarm_export   --  swc_alarm.export
		);
