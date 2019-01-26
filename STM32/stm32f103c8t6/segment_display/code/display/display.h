#ifndef _DISPLAY_H_

#define _DISPLAY_H_

#include <stdint.h>

enum disp_pos {POS_1 = 0x10, POS_2 = 0x20, POS_3 = 0x40, POS_4 = 0x80};
enum segments {SEG_1 = 0x7f, SEG_2 = 0xbf, SEG_3 = 0xdf, SEG_4 = 0xef, SEG_5 = 0xf7, SEG_6 = 0xfb, SEG_7 = 0xfd, SEG_DOT = 0xfe};

static void (*display_send_data)(uint8_t dig, uint8_t value);
void display_init(void (*send_data)(uint8_t dig, uint8_t value));
void display_digit(uint8_t digit_pos, uint8_t value);

static uint8_t get_disp_pos(uint8_t digit_pos);
static uint8_t val_to_seg(uint8_t value);

#endif