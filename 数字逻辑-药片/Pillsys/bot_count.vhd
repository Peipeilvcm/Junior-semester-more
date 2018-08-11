library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity bot_count is
port(
	clr,full:in std_logic;
	Y:out std_logic_vector(7 downto 0));
end bot_count; 

architecture func of bot_count is
signal count_i,count_j:std_logic_vector(3 downto 0);
begin
    process(full,clr)
	begin
	     --外部清零信号有效则清零
	    if clr='0' then
	        count_i<="0000";
		    count_j<="0000";
		--满瓶信号的上升沿累加瓶数
	    elsif rising_edge(full) then              
	         if count_i="1001" then
		        count_i<="0000";
				    if count_j="1001" then
				        count_j<="0000";
				    else 
				        count_j<=count_j+'1';
				    end if;
			else
				count_i<=count_i+'1';
			end if;
        end if;
    end process;
	Y(3 downto 0)<=count_i;
	Y(7 downto 4)<=count_j;
end func;
				