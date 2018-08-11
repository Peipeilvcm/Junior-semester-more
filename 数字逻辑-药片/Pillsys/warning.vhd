library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity warning is
port(
	clk,stop,is_finish,over_flow:in std_logic;
    ring,ogreen,ored:out std_logic);
end warning;

architecture func of warning is
signal a,b,c:std_logic;
begin
    process(stop,flag,over_flow)
    begin
	if over_flow='1' then--每瓶装片超额--特殊状态
		a<=over_flow;
		b<=over_flow;
		c<=over_flow;
	--当前系统正在装药且瓶数已到达上限 则系统暂停 闪烁发出警报
    elsif stop='0' and is_finish='1' then
        a<=clk;
        b<=not clk;
		c<='1';
	--当前为到达上限 则根据传送带模块传输的信号来输出装瓶状态对应的灯
    else
        a<=not stop;
        b<=stop;
		c<='0';
    end if;
    end process;
    ogreen<=a;
    ored<=b;
	ring<=c;
end func;
    