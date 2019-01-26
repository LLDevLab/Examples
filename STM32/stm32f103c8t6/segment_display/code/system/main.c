#include "main.h"

int main(void)
{
	uint8_t i, j;
	init();
	
	while(1)
	{
		for(i = 1; i <= 4; i++)
		{
			for(j = 0; j <= 9; j++)
			{
				display_digit(i, j);
				delay();
			}
		}
	}
	
	return 0;
}

// Инициализируем PORT C для работы
static void port_c_init(void)
{
	RCC_APB2ENR = 0x10;				// Включаем тактирование PORT C пинов
	GPIOC_CRH = 0x22200000;			// Устанавливаем PC13, PC14, PC15 для работы как output, на частоте до 2mhz
}

static void init(void)
{	
	port_c_init();
	
	display_init(&send_data);
}

static void show_changes(void)
{
	// Для отображение изменений на экране переключаем PC13 (RCLK) из 0 в 1 и обратно
	uint16_t ports = 0;
	
	ports |= PC13; 
	GPIOC_ODR = ports;
		
	ports = 0; 
	GPIOC_ODR = ports;
}

void send_data(uint8_t pos, uint8_t value)
{
	// NB! Порядок важен, первым передаем значение, затем позицию на дисплее
	send(value);
	send(pos);
	show_changes();
}

static void send(uint8_t data)
{
	uint8_t i;
	uint16_t ports = 0;								// ports - 16 бит (uint16_t), а не 32 потому, что старшие 2 байта GPIOC_ODR регистра не используются
	
	for(i = 0; i < 8; i++)
	{	
		// Если передаваемый бит = 1, то выставляем значение PC15 (DIO) в high, в противном случае в low
		// Таким образом передаем значение нулевого бита на дисплей
		if((data & 0x01) > 0)
			ports = PC15;
		else
			ports = 0;
		
		GPIOC_ODR = ports;
		
		// Выставляет значение PC14 (SCLK) в high (началась передача данных)
		ports |= PC14; 
		GPIOC_ODR = ports;
	
		// Убираем сигнал с PC15 (DIO)
		ports &= ~PC15;
		GPIOC_ODR = ports;
		
		// Убираем сигнал с PC14 (SCLK) (передача данных закончилась )
		ports &= ~PC14; 
		GPIOC_ODR = ports;
		
		// Берем следующий бит для передачи (сдвигаем значение data вправо на 1 бит)
		data = data >> 1;
	}
}

// Функция задержки
static void delay(void)
{
	int i = 0x000FFFFF;
	while(i > 0)
	{
		i--;
	}
}
	