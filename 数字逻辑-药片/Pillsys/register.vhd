library ieee;
use ieee.std_logic_1164.all;
--存取瓶数、每瓶药片数上限
entity regi is
port(
	w:in std_logic;
	clr,clk:in std_logic;
	K:in std_logic_vector(7 downto 0);
    D:out std_logic_vector(7 downto 0));
end regi;

architecture behave of regi is
begin
	process(clk)
	begin
		if clr='0' then
			D<="10011001";
		elsif rising_edge(clk) then
			if w='1' then
				D<=K;
			else
			end if;
		else
		end if;
	end process;
end behave;