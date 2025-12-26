#include "IDT.h"
#include "Video.h"

#define IDT_SIZE 256

struct idt_entry idt[IDT_SIZE];
struct idt_ptr idtp;

// Assembly... no, PLS NOO-
extern void idt_load(struct idt_ptr*);

static void idt_set_gate(int n, uint32_t handler, uint16_t selector, uint8_t type_attr) {
    idt[n].offset_low = handler & 0xFFFF;
    idt[n].selector = selector;
    idt[n].zero = 0;
    idt[n].type_attr = type_attr;
    idt[n].offset_high = (handler >> 16) & 0xFFFF;
}

void idt_init() 
{

    idtp.limit = (sizeof(struct idt_entry) * IDT_SIZE) - 1;
    idtp.base = (uint32_t)&idt;

    for (int i = 0; i < IDT_SIZE; i++) {
        idt[i].offset_low = 0;
        idt[i].selector = 0;
        idt[i].zero = 0;
        idt[i].type_attr = 0;
        idt[i].offset_high = 0;
    }

    idt_load(&idtp);

    idt_set_gate(33, (uint32_t)irq1_handler_asm, 0x08, 0x8E); // IRQ1
    idt_load(&idtp);

    Writeline("Loaded IDT.");

}
