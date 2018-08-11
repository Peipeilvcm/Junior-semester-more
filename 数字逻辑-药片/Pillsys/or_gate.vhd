library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
--综合传输带的停止信号与上限报警的暂停信号 用于控制药片装瓶
entity or_gate is
port(clr1,clr2:in std_logic;
    clr_out:out std_logic);
end or_gate;

architecture arc of or_gate is
signal c_temp:std_logic;
begin
    process(s1,s2)
	begin
	    c_temp<=clr1 or clr2;
	end process;
	clr_out<=c_temp;
end arc;