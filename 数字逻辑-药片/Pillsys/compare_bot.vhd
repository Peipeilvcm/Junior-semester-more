library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity compare_bot is
port(--x1输入当前已装瓶数,X2输入瓶数上限
	X1,X2:in std_logic_vector(7 downto 0);
    is_finish:out std_logic);
end compare_bot;

architecture comp of compare_bot is
signal a:std_logic:='0';
begin
    process(X1,X2)
	 begin
	    if (X1=X2) then 
		    a<='1';
		else
			a<='0'
		end if;
	 end process;
	 is_finis1<=a;
end comp;