library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity belt is
    port(
		clk,is_full:in std_logic;
	    stop,clr:out std_logic);
end belt;

architecture convert of belt is
signal s:std_logic;
begin
    process(clk)
	begin
	     --当前瓶未装满 传输带停止 正在装瓶
	    if is_full='0' then
		    clr<='1';
			s<='0';
		--当前为装瓶状态且瓶已满 装瓶立即停止 传输带移动
		elsif s='0' then
		    clr<='1';
			s<='1';
		--新瓶到达时间为一拍时间脉冲 瓶中药片计数清零 装瓶开始
		elsif rising_edge(clk) then
			s<='0';
			clr<='0';
		end if;
    end process;
	stop<=s;
end convert;    