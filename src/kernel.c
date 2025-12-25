// were am I? wait... this is the code that defines the "Write" function? AM I IN A KERNEL???????

#include <stdint.h>
#include "Modules/Video.h"
#include "Modules/Keyboard.h"
#include "Modules/IDT.h"

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_MEMORY 0xB8000

// Code by NyanRay64 =3

uint16_t* terminal_buffer = (uint16_t*)VGA_MEMORY;
int terminal_row = 0;
int terminal_col = 0;
uint8_t terminal_color = 0x07;

extern const char* version = "Build 1";

void startup() {
    terminal_color = vga_entry_color(0x0F, 0x00); // White on black, like... any command-line kernel LMAO
    itd_init();
    pic_remap();
    keyboard_init();
    // Updating the permanently registry keys
    RegistryEntry* k_main = create_key(&root_registry, "KEY_MAIN", "");
    RegistryEntry* k_kernel = create_key(k_main, "KERNEL", "");
    WriteLine("Created main keys");
    create_key(k_kernel, "superbar", "0");
    create_key(k_kernel, "CanIhaveBetaRegistry", "1");
    create_key(k_kernel, "TerminalColor", "0x0F, 0x00");
    WriteLine("Created SubKeys");
    Clear();
}

void Update() {
    // this is empty for now >///<
}

void kernel_main() {
    startup();

    Writeline("Hello, world! :3");
    WriteAt("For testing purposes only, build 1", 10, 5, vga_entry_color(0x0F, 0x00));
    
    while (1) { Update(); }
}
