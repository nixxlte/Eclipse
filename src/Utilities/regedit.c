#include "Registry.h"
#include "../Modules/ASCM.h"
#include "Regedit.h"
#include "../Modules/Keyboard.h"
#include "../Modules/Console.h"   // Console commands, like Writeline("hello, world"); :3

#include <string.h>

// Code by NyanRay64 =3

static RegistryEntry* current = &root_registry;

void list_keys(RegistryEntry* node) {
    WriteLine("Keys under:");
    WriteLine(node->key);

    for (int i = 0; i < node->child_count; i++) {
        Write(" - ");
        WriteLine(node->children[i]->key);
    }
}

void regedit_init() {
  ASCM_show("ASCIIhline1");
  WriteLine("this option doesn't exist yet");
}

void regbeta_init() {
    char buffer[64];
    while (1) {
        Write("regedit> ");
        keyboard_readline(buffer, sizeof(buffer)); // read the user entry

        if (strcmp(buffer, "exit") == 0) {
            return; // exits regedit
        } else if (strcmp(buffer, "ls") == 0) {
            list_keys(current);
        } else if (strncmp(buffer, "cd ", 3) == 0) {
			// go to subkey
            char* name = buffer + 3;
            int found = 0;
            for (int i = 0; i < current->child_count; i++) {
                if (strcmp(current->children[i]->key, name) == 0) {
                    current = current->children[i];
                    found = 1;
                    break;
                }
            }
            if (!found) {
                WriteLine("Key not found");
            }
        } else if (strncmp(buffer, "mk ", 3) == 0) {
            // create subkey
            char* name = buffer + 3;
            create_key(current, name, "");
            WriteLine("Key created");
        } else {
            WriteLine("Unknown command. Try: ls, cd <key>, mk <key>, exit");
        }
    }
}
