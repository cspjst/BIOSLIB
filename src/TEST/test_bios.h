#ifndef TEST_BIOS_H
#define TEST_BIOS_H

#include <stdio.h>
#include <assert.h>

#include "../BIOS/bios_memory_services.h"
#include "../BIOS/bios_keyboard_services.h"
#include "../BIOS/bios_keyboard_scan_codes.h"
#include "../BIOS/bios_keyboard_constants.h"
#include "../BIOS/bios_video_services.h"
#include "../BIOS/bios_video_services_types.h"
#include "../BIOS/bios_video_services_constants.h"
#include "../BIOS/bios_clock_services.h"
#include "../BIOS/bios_clock_constants.h"

void test_bios_memory(void) {
    printf("Testing BIOS memory functions...\n");
    unsigned short base_memory;
    //unsigned long total_bytes;

    // Get base memory size
    base_memory = bios_get_startup_memory_kb();

    // Display in various units
    printf("Base memory (conventional):\n");
    printf("  %u KB\n", base_memory);
    printf("  %lu bytes\n", (unsigned long)base_memory * 1024L);
    printf("  %u paragraphs\n", base_memory * 64);  // 64 paragraphs per KB

    // Sanity checks
    printf("\nSanity check: ");
    if(base_memory > 0 && base_memory <= 640) {
        printf("PASS (within 0-640K range)\n");
    } else if(base_memory > 640 && base_memory < 1024) {
        printf("WARNING: Unusual value (%u KB) - some systems report >640K\n", base_memory);
    } else {
        printf("FAIL: Impossible value (%u KB)\n", base_memory);
    }
    printf("BIOS memory functions tests passed\n\n");
}

void test_bios_keys() {
    printf("Testing KEY functions...\n");
    assert(sizeof(unsigned char) == 1);
    assert(sizeof(unsigned short) == 2);
    assert(sizeof(unsigned int) == 2);

    bios_key_t key;
    bios_key_status_t key_state;
    bios_keybd_info_t flags;
    int key_count = 0;

    printf("Press any key to test (ESC to quit, F1 for help)\n");
    printf("------------------------------------------------\n");

    // Show initial shift states
    bios_get_keyboard_flags(&flags);
    printf("Initial flags: %s%s%s%s%s%s%s%s\n",
        (flags & BIOS_KEY_RIGHT_SHIFT) ? "RSHIFT " : "",
        (flags & BIOS_KEY_LEFT_SHIFT) ? "LSHIFT " : "",
        (flags & BIOS_KEY_CTRL) ? "CTRL " : "",
        (flags & BIOS_KEY_ALT) ? "ALT " : "",
        (flags & BIOS_KEY_SCROLL_LOCK) ? "SCROLL " : "",
        (flags & BIOS_KEY_NUM_LOCK) ? "NUM " : "",
        (flags & BIOS_KEY_CAPS_LOCK) ? "CAPS " : "",
        (flags & BIOS_KEY_INSERT) ? "INSERT " : "(none)");

    while(1) {
        // Show status (non-blocking peek)
        bios_get_keystroke_status(&key_state);

        // Get full key (blocking read)
        bios_wait_for_keystroke_and_read(&key);
        key_count++;

        // Get flags after keypress
        bios_get_keyboard_flags(&flags);

        // Decode and display key information
        printf("[%03d] ", key_count);

        // Show if it's a special or normal key
        if(key.parts.ascii >= 32 && key.parts.ascii <= 126) {
            // Printable ASCII
            printf("'%c' ", key.parts.ascii);
        } else if(key.parts.ascii == 0) {
            // Special function key
            printf("(special) ");
        } else {
            // Control character
            printf("(0x%02X) ", key.parts.ascii);
        }

        // Show scan code with name if known
        printf("scan=0x%02X ", key.parts.scan);
        switch(key.parts.scan) {
            case SCAN_ESC:      printf("(ESC)"); break;
            case SCAN_ENTER:    printf("(ENTER)"); break;
            case SCAN_BACKSPACE: printf("(BACKSPACE)"); break;
            case SCAN_TAB:      printf("(TAB)"); break;
            case SCAN_SPACE:    printf("(SPACE)"); break;
            case SCAN_F1:       printf("(F1)"); break;
            case SCAN_F2:       printf("(F2)"); break;
            case SCAN_F3:       printf("(F3)"); break;
            case SCAN_F4:       printf("(F4)"); break;
            case SCAN_F5:       printf("(F5)"); break;
            case SCAN_F6:       printf("(F6)"); break;
            case SCAN_F7:       printf("(F7)"); break;
            case SCAN_F8:       printf("(F8)"); break;
            case SCAN_F9:       printf("(F9)"); break;
            case SCAN_F10:      printf("(F10)"); break;
            case SCAN_UP:       printf("(UP)"); break;
            case SCAN_DOWN:     printf("(DOWN)"); break;
            case SCAN_LEFT:     printf("(LEFT)"); break;
            case SCAN_RIGHT:    printf("(RIGHT)"); break;
            case SCAN_HOME:     printf("(HOME)"); break;
            case SCAN_END:      printf("(END)"); break;
            case SCAN_PGUP:     printf("(PGUP)"); break;
            case SCAN_PGDN:     printf("(PGDN)"); break;
            case SCAN_INS:      printf("(INSERT)"); break;
            case SCAN_DEL:      printf("(DELETE)"); break;
        }

        // Show shift state
        printf(" [");
        if(flags & BIOS_KEY_RIGHT_SHIFT) printf("RSh ");
        if(flags & BIOS_KEY_LEFT_SHIFT) printf("LSh ");
        if(flags & BIOS_KEY_CTRL) printf("Ctrl ");
        if(flags & BIOS_KEY_ALT) printf("Alt ");
        if(flags & BIOS_KEY_SCROLL_LOCK) printf("ScrLk ");
        if(flags & BIOS_KEY_NUM_LOCK) printf("NumLk ");
        if(flags & BIOS_KEY_CAPS_LOCK) printf("Caps ");
        if(flags & BIOS_KEY_INSERT) printf("Ins ");
        if(flags == 0) printf("none");
        printf("]\n");

        // Help screen on F1
        if(key.parts.scan == SCAN_F1) {
            printf("ESC: Quit\n");
            printf("F1:  Show this help\n");
            printf("F2:  Show status info\n");
            printf("Any other key: Display key info\n");
        }

        // Show status info on F2
        if(key.parts.scan == SCAN_F2) {
            printf("Keys pressed: %d\n", key_count);
            printf("Key available flag: %d\n", key_state.pressed);
            printf("Flags register: 0x%02X\n", flags);
        }

        // Quit on ESC
        if(key.parts.scan == SCAN_ESC) {
            printf("\nTest complete. %d keys processed.\n", key_count);
            break;
        }
    }
    printf("BIOS key functions tests passed\n\n");
}

void test_bios_video() {
    printf("Testing bios video...\n");

    bios_video_state_t state;
    unsigned char original_mode;
    bios_get_video_state(&state);
    original_mode = state.mode;
    printf("Original mode: 0x%02X %s\n", original_mode, bios_video_mode_names[original_mode]);
    assert(original_mode != MDA_TEXT_MONOCHROME_80X25); // unable set video mode using BIOS
    assert(original_mode != CGA_TEXT_16_COLOUR_40X25); // already target mode
    getchar();
    bios_set_video_mode(CGA_TEXT_16_COLOUR_40X25);
    bios_get_video_state(&state);
    printf("New mode: 0x%02X %s\n", state.mode, bios_video_mode_names[state.mode]);
    assert(state.mode == CGA_TEXT_16_COLOUR_40X25);
    getchar();
    bios_set_video_mode(original_mode);
    bios_get_video_state(&state);
    assert(state.mode == original_mode);
    printf("Restored mode: 0x%02X %s\n", state.mode, bios_video_mode_names[state.mode]);

    printf("bios video tests passed\n\n");
}

void test_bios_read_system_clock(void) {
    printf("Testing bios time services...\n");

    bios_ticks_since_midnight_t ticks;
    float total_seconds;
    float hours, minutes, seconds;

    /* Read current ticks */
    bios_read_system_clock(&ticks);

    /* Calculate time using floats */
    total_seconds = (float)ticks / TICKS_PER_SECOND;
    hours   = total_seconds / 3600.0;
    minutes = (total_seconds / 60.0) - (hours * 60.0);
    seconds = total_seconds - (hours * 3600.0) - (minutes * 60.0);

    printf("  Ticks since midnight: %lu\n", (unsigned long)ticks);
    printf("  Approximate time: %02.0f:%02.0f:%02.0f\n", hours, minutes, seconds);

    /* Sanity checks */
    printf("  Sanity check: ");
    assert((unsigned long)ticks < 0x1800B0);
    printf("PASS\n");
}

void test_bios_set_system_clock(void) {

    bios_ticks_since_midnight_t original_ticks;
    bios_ticks_since_midnight_t verify_ticks;
    unsigned char error;

    /* Save current time */
    bios_read_system_clock(&original_ticks);
    printf("  Original ticks: %lu\n", (unsigned long)original_ticks);

    /* Set to 0 (midnight) */
    printf("  Setting ticks to 0... ");
    error = bios_set_system_clock(0);

    if(error == 0) {
        printf("PASS\n");
    } else {
        printf("FAIL (error=0x%02X)\n", error);
    }

    /* Verify reset */
    bios_read_system_clock(&verify_ticks);
    printf("  Verified ticks: %lu\n", (unsigned long)verify_ticks);

    /* Restore original time */
    printf("  Restoring original time... ");
    error = bios_set_system_clock(original_ticks);
    if(error == 0) {
        printf("PASS\n");
    } else {
        printf("FAIL (error=0x%02X)\n", error);
    }
}

void test_bios() {
    test_bios_read_system_clock();
    test_bios_set_system_clock();
    test_bios_memory();
    test_bios_keys();
    test_bios_video();
}

#endif
