-- Описание каждой новой сущности устройства (entity) начинается с подключения используемых ею библиотек 
library ieee;					-- Стандартной библиотека ieee
use ieee.std_logic_1164.all;	-- Включаем все компоненты из пакета std_logic_1164 стандартной библиотеки ieee

-- Описываем сущность устройства
entity delay is
	generic (delay_cnt: integer); 							-- При объявлении entity, поле generic не является обязательным
	port(clk: in std_logic; out_s: out std_logic := '0');	-- Описываем входные и выходные сигналы устройства
end entity delay;

-- В секции architecture описывается то, как устройство будет работать
-- С одной entity может быть связано одна или более архитектур
architecture delay_arch of delay is
begin
	-- Внутри секции процесс все события выполняются последовательно
	-- Процесс начинает исполняться как только хотябы 1 из указанных в его sensivity list'е сигналов меняет свое значение
	delay_proc: process(clk)
		variable clk_cnt: integer range 0 to delay_cnt := 0;
		variable out_v: std_logic := '0';
	begin
		if(rising_edge(clk)) then				-- Если имеем дело с передним фронтом сигнала
			clk_cnt := clk_cnt + 1;					
				
			if(clk_cnt >= delay_cnt) then
				
				-- switch/case в языке VHDL 
				case out_v is
					when '0' => 
						out_v := '1';
					when others =>
						out_v := '0';
				end case;
				
				clk_cnt := 0;
				out_s <= out_v;					-- Устанавливаем в сигнал out_s значение переменной out_v
			end if;
		end if;
	end process delay_proc;
end delay_arch;