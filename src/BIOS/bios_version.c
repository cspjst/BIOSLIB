#include "bios_version.h"

unsigned int bios_version() {
    return BIOS_VERSION;
}

const char* bios_version_string() {
    return BIOS_VERSION_STRING;
}
