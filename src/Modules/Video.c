// This is part of the modules, and... yes, this is the same organization that i use for kernelMod

// Code by NyanRay64 =3

#include <stdint.h>

uint16_t* terminal_buffer = (uint16_t*)VGA_MEMORY;
int terminal_row = 0;
int terminal_col = 0;
uint8_t terminal_color = 0x07; // cinza no preto

// Sets the color to: white text on black background
uint8_t vga_entry_color(uint8_t fg, uint8_t bg) {
    return fg | bg << 4;
}

// Creates the character
uint16_t vga_entry(unsigned char uc, uint8_t color) {
    return (uint16_t) uc | (uint16_t) color << 8;
}

// Writes character in position: (x,y)
void terminal_putentryat(char c, uint8_t color, int x, int y) {
    terminal_buffer[y * VGA_WIDTH + x] = vga_entry(c, color);
}

// A simple text cursor control
void terminal_putchar(char c) {
    if (c == '\n') {
        terminal_col = 0;
        terminal_row++;
        return;
    }
    terminal_putentryat(c, terminal_color, terminal_col, terminal_row);
    terminal_col++;
    if (terminal_col >= VGA_WIDTH) {
        terminal_col = 0;
        terminal_row++;
    }
}

// Write strings (same C# code)
void Write(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        terminal_putchar(str[i]);
    }
}

// Write lines (also same C# code)
void WriteLine(const char* str) {
    Write(str);
    terminal_putchar('\n');
}

// Ignores the cursor and write something in some screen local
void WriteAt(const char* str, int x, int y, uint8_t color) {
    int col = x;
    int row = y;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\n') {
            col = x;
            row++;
            continue;
        }
        terminal_putentryat(str[i], color, col, row);
        col++;
        if (col >= VGA_WIDTH) {
            col = x;
            row++;
        }
    }
}

// Clears the screen
void Clear() 
{
    
    for (int y = 0; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            terminal_putentryat(' ', terminal_color, x, y);
        }
    }
    terminal_row = 0;
    terminal_col = 0;
}

void entry()
{

    Write("> ");

}