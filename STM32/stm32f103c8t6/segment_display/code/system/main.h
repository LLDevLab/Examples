#include "registers.h"
#include "..\display\display.h"
#include <stdint.h>

// PC13 подключено к RCLK пину дисплея
// PC14 подключено к SCLK пину дисплея
// PC15 подключено к DIO пину дисплея
enum port_c {PC13 = 0x2000, PC14 = 0x4000, PC15 = 0x8000};

static void port_c_init(void);
static void init(void);
void send_data(uint8_t pos, uint8_t value);
static void show_changes(void);
static void send(uint8_t data);
static void delay(void);