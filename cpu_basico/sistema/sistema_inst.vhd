	component sistema is
		port (
			clk_clk       : in  std_logic                    := 'X'; -- clk
			reset_reset_n : in  std_logic                    := 'X'; -- reset_n
			regs_export   : out std_logic_vector(7 downto 0)         -- export
		);
	end component sistema;

	u0 : component sistema
		port map (
			clk_clk       => CONNECTED_TO_clk_clk,       --   clk.clk
			reset_reset_n => CONNECTED_TO_reset_reset_n, -- reset.reset_n
			regs_export   => CONNECTED_TO_regs_export    --  regs.export
		);
