library ieee;
use ieee.std_logic_1164.all;

entity delay_tb is end;	-- Данная entity не будет иметь входных и выходных сигналов (используется только при симуляции)

architecture delay_tb_arch of delay_tb is
	-- Объявляем компонент delay
	-- В самом простом случае (как сдесь) название компонента = названию entity
	-- И так как у entity delay только одна архитектура, то объявление компонента сводиться к тому, 
	-- что мы просто копируем generic и port из соответствующей entity
	component delay is
		generic (delay_cnt: integer := 2);						-- 2 по умлчанию
		port(clk: in std_logic; out_s: out std_logic);
	end component;

	-- Объявляем 3 сигнала типа std_logic
	signal clk_s: std_logic := '0';		-- Задаем значение сигнала по умолчанию '0'
	signal delay_out_s, delay_out2_s: std_logic;
begin
	-- Порядок присвоения сигналов внутри архитектуры значения не имеет
	-- Здесь все операции происходят параллельно
	
	-- Меняем значение сигнала clk_s на противоположный каждые 40 ns 
	clk_s <= not clk_s after 40 ns;		-- after работает только при симуляции
	
	-- Создаем экземпляр delay entity (dalay1)
	-- Инициализируем его generic (delay_cnt) = 4
	-- Указываем, что входным сигналом, для delay1 будет clk_s, а выходным delay_out_s
	delay1: delay 
			generic map(4)
			port map(clk_s, delay_out_s);					 
	
	-- Создаем экземпляр delay entity (dalay2)
	-- Его generic (delay_cnt) = 2 (по умлчанию)
	-- Указываем, что входным сигналом, для delay2 будет clk_s, а выходным delay_out2_s
	delay2: delay port map (out_s => delay_out2_s, clk => clk_s);
end delay_tb_arch;