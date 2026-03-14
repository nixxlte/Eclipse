// Code by imNyan.T64 -w-

#include "Registry.h"
#include <stdlib.h>
#include <string.h>

RegistryEntry root_registry = {
    .key = "ROOT",
    .value = "",
    .child_count = 0
};

RegistryEntry* create_key(RegistryEntry* parent, const char* name, const char* value) {
    if (parent->child_count >= MAX_CHILDREN) return NULL;

    RegistryEntry* new_key = malloc(sizeof(RegistryEntry));
    if (!new_key) return NULL;

    strcpy(new_key->key, name);
    strcpy(new_key->value, value);
    new_key->child_count = 0;

    parent->children[parent->child_count++] = new_key;
    return new_key;
}