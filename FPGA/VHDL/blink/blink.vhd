library ieee;
use ieee.std_logic_1164.all;
-- Work – рабочая библиотека, в которую по умолчанию Quartus компилирует наш код.
-- Отдельно с помощью ключевого слова library ее объявлять не надо, она по умолчанию всегда включена в проект
use work.all;		-- Указываем что хотим использовать все объекты из библиотеки work, иначе перед каждым из объектов не описанном в данном файле придеться писать work.object_name (например work.delay)					

entity blink is
	port(clk: in std_logic; led: out std_logic_vector(0 to 2) := "000"); 
end entity blink;

architecture blink_arch of blink is
	component timeout is
		generic(delay_g: integer);
		port(clock: in std_logic; time_out: out std_logic); 
	end component;
	
	-- Эта техника мапинга называется "Configuration Specification"
	-- Здесь мы мапим сигналы из component'a с сигналами соответствубщей entity
	-- Использую ее в данном примере в целях иллюстрации
	for all: timeout					-- Для всех сущностей типа timeout 
		use entity delay(delay_arch)	-- Использовать entity delay с архитектурой delay_arch
		generic map(delay_g)			-- delay_g компонента идет в первый generic в entity delay
		port map(clock, time_out);		-- сигнал clock компонента идет в первый порт и сигнал time_out компонента во 2ой порт entity delay
		
	signal sec_s: std_logic := '0';
begin
	-- VHDL позволяет в integer значениях использовать нижние подчеркивания для удобства
	sec: timeout 	
			-- На плате распаян кварц с частотой 50Mhz, для подсчета 0.5с нужно отсчитать 25 000 000 передних фронтов сигнала
			generic map(25_000_000)
			port map(clk, sec_s);
			
	led1: timeout
			generic map(1)					-- Светодиод мигает с частотой 0.5с * 2 (так как delay срабатывает только на передный фронт сигнала) = 1с  
			port map(sec_s, led(0));

	led2: timeout
			generic map(2)					-- Светодиод мигает с частотой 0.5с * 4 = 2с
			port map(sec_s, led(1));
			
	led3: timeout
			generic map(3)					-- Светодиод мигает с частотой 0.5с * 6 = 3с
			port map(sec_s, led(2));
end blink_arch;