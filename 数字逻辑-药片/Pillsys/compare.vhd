library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity compare is
port(--x1输入当前已装,X2输入每瓶容量,X3输入每瓶容量上限
	X1,X2,X3:in std_logic_vector(7 downto 0);
    is_full,over_flow:out std_logic);
end compare;

architecture comp of compare is
signal a,b:std_logic:='0';
begin
    process(a1,a2,b1,b2)
	 begin
	     --比较上限和当前已装片数
	    if (X1(7 downto 4)>X3(7 downto 4) or (X1>X3) then 
		    b<='1';
		else
			b<='0'
			if(X1==X2)
				a<='1';
			else
				a<='0';
			end if;
		end if;
	 end process;
	 is_full<=a;
	 over_flow<=b;
end comp;