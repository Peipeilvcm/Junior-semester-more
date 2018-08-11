library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
--药片装瓶系统顶层设计
entity pillsys is
port(
		clk,clr,state_qd:in std_logic;
		K:in std_logic_vector(7 downto 0);
		Y1:out std_logic_vector(7 downto 0);
		Y2:out std_logic_vector(11 downto 0);
		green,red,wring:out std_logic);
end pillsys;

architecture state_ex of pillsys is

--一瓶的药片计数实体
component pills_count is
port(
	stop:in std_logic;
    clr,clk:in std_logic;
	Y:out std_logic_vector(7 downto 0));
end component;

--所有药片总数计数实体
component all_pills_count is
port(
	stop:in std_logic;
    clr,clk:in std_logic;
	Y:out std_logic_vector(11 downto 0));
end component;

--传送带实体
component belt is
    port(
		clk,is_full:in std_logic;
	    stop,clr:out std_logic);--clr给计数器清零,stop控制是否继续装片
end component;

--寄存器实体
component regi is
port(
	w:in std_logic;
	clr,clk:in std_logic;
	K:in std_logic_vector(7 downto 0);
    D:out std_logic_vector(7 downto 0));
end component;

--比较实体
component compare is
port(--x1输入当前已装,X2输入每瓶容量,X3输入每瓶容量上限
	X1,X2,X3:in std_logic_vector(7 downto 0);
    is_full,over_flow:out std_logic);
end component;

--或门,清空单瓶药片计数器
component or_gate is
port(clr1,clr2:in std_logic;
    clr_out:out std_logic);
end component;

component bot_count is
port(
	clr,full:in std_logic;
	Y:out std_logic_vector(7 downto 0));
end bot_count;

component compare_bot is
port(--x1输入当前已装瓶数,X2输入瓶数上限
	X1,X2:in std_logic_vector(7 downto 0);
    is_finish:out std_logic);
end component;

--告警\状态显示
component warning is
port(
	clk,stop,is_finish,over_flow:in std_logic;
    ring,ogreen,ored:out std_logic);
end component;

TYPE state IS (state0,state1,state2,state3,state4);
SIGNAl pr_state,nx_state:state;
SIGNAl s_cnt,nx_cnt:integer range 0 to 2:=0;
SIGNAl w:STD_LOGIC_VECTOR(3 downto 0):="0000";
signal regi_y1,regi_y2,regi_y3,plcnt_y4,botcnt_y5:std_logic_vector(7 downto 0);
signal all_pill_y5:std_logic_vector(11 downto 0);
signal stop_temp,clr2_temp,clr_temp,full_temp,over_flow_temp,ring_temp,green_temp,red_temp,finish_temp:std_logic;
signal Y1_temp:std_logic_vector(7 downto 0);
signal Y2_temp:std_logic_vector(11 downto 0);

Begin
	p1_reg_perbnum:regi port map(clk=>clk,clr=>clr,w=>w(0),K=>K,D=>regi_y1);--每瓶药片数上限
	p2_reg_botnum:regi port map(clk=>clk,clr=>clr,w=>w(1),K=>K,D=>regi_y2);--瓶数上限
	p3_reg_curbnum:regi port map(clk=>clk,clr=>clr,w=>w(1),K=>K,D=>regi_y3);--当前每瓶想要装入药片数
	p4:pills_count port map(stop=>stop_temp,clr=>clr_temp,clk=>clk,Y=>plcnt_y4);--每瓶药片计数
	p5_clr_or:or_gate port map(clr1=>clr,clr2=>clr2_temp,clr_out=>clr_temp);
	p5:compare port map(X1=>plcnt_y4,X2=>regi_y3,X3=>regi_y1,is_full=>full_temp,over_flow_temp);--比较器
	p6:belt port map(is_full=>full_temp,clk=>clk,stop=>stop_temp,clr=>clr2_temp);--传送带
	p7:all_pills_count port map(stop=>stop_temp,clr=>clr,clk=>clk,Y=>all_pill_y5);--输出总药片数
	p8:warning port map(clk=>clk,stop=>stop_temp,is_finish=>finish_temp,over_flow=>over_flow_temp,ring=>wring,ogreen=>green,ored=>red);
	p9:bot_count port map(clr=>clr,full=>full_temp,Y=>botcnt_y5);--瓶数计数器
	p10:compare_bot port map(X1=>botcnt_y5,X2=>regi_y2,is_finish=>finish_temp);--比较瓶数是否达到上限
	
	PROCESS(state_qd,clr)
	begin
		if(clr='0') then
			pr_state<=state0;
		elsif rising_edge(state_qd) then
			pr_state<=nx_state;
			s_cnt<=ne_cnt;
		end if;
	end process;

	process(s_cnt,pr_state)
	begin
		case pr_state is
		when state0 =>
		--清零状态
			w<="0000";
			Y1_temp<="00000000";
			Y2_temp<="000000000000";
			nx_state<=state1;
			nx_cnt<=0;
		when state1 =>
		--设置每瓶片数上限+设置瓶数上限
			if(s_cnt=0) then
				w<="0001";
				Y1_temp<=K;
				Y2_temp<="111111111111";
				nx_cnt<=1;--设置每瓶片数上限
				nx_state<=state1;
			elsif(s_cnt=1)	then
				w<="0010";
				Y1_temp<=regi_y1;
				Y2_temp<="111100000000"+K;
				nx_cnt<=0;--设置瓶数上限
				nx_state<=state2;
			else
			end if;
		when state2 =>
			--设置当前实际装入每瓶药片数
			w<="0100";
			Y1_temp<=K;
			Y2_temp<=Y2_temp<="111111111111";
			nx_cnt<=0;--设置每瓶实际装入值
			nx_state<=state3;
		when state3 =>
			--工作状态计数
			w<="1000";
			if(s_cnt=0) then--显示当前瓶中已装药片的数量+总药片数量
				Y1_temp<=plcnt_y4;
				Y2_temp<=all_pill_y5;
				nx_cnt<=1;
				nx_state<=state3;
			elsif (s_cnt=1) then--显示已装瓶数+总药片数量
				Y1_temp<=botcnt_y5;
				Y2_temp<=all_pill_y5;
				nx_cnt<=2;
				nx_state<=state3;
			elsif (s_cnt=2)--显示每瓶药片数上限,瓶数上限
				Y1_temp<=regi_y1;
				Y2_temp<="111100000000"+regi_y2;
				nx_cnt<=3;
				nx_state<=state3;
			else--显示当前设置每瓶装入的药片数
				Y1_temp<=regi_y3;
				Y2_temp<="111111111111";
				nx_cnt<=0;
				nx_state<=state3;
			end if;
		when others=>
			nx_state<=state0;
		end case;
	end process;
	Y1<=Y1_temp;
	Y2<=Y2_temp;
end state_ex;
