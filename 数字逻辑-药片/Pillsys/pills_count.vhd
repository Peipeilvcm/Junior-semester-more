library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity pills_count is
port(
	w:in std_logic;
	stop:in std_logic;
    clr,clk:in std_logic;
	Y:out std_logic_vector(7 downto 0));
end pills_count; 

architecture plus_1 of pillcnt is
signal count_i,count_j:std_logic_vector(3 downto 0):"0000";
begin
    process(clk,clr)
	 begin
	     if clr='0' then
	        count_i<="0000";
		    count_j<="0000";
        elsif stop='1' then--停止
		  --装药的工作状态则累加药片数
	    elsif rising_edge(clk) then
			if w='1' then
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
			else
			end if;
		else
        end if;
    end process;
	Y(3 downto 0)<=count_i;
	Y(7 downto 4)<=count_j;
end plus_1;
				