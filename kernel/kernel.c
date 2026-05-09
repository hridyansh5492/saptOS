int cursor = 0;

void clear_screen() {
    char *video_memory = (char*) 0xb8000;

    for (int i = 0; i < 80 * 25 * 2; i += 2) {
        video_memory[i] = ' ';      // empty character
        video_memory[i + 1] = 0x07; // color
    }

    cursor = 0; // reset cursor to top
}

void print(char *str) {
    char *video_memory = (char*) 0xb8000;

    for (int i = 0; str[i] != '\0'; i++) {

        if (str[i] == '\n') {
            // move cursor to next line
            cursor = (cursor / 160 + 1) * 160;
        } else {
            video_memory[cursor++] = str[i];
            video_memory[cursor++] = 0x07;
        }
    }
}

static inline unsigned char inb(unsigned short port) {
    unsigned char result;
    __asm__ volatile ("inb %1, %0" : "=a"(result) : "Nd"(port));
    return result;
}

char get_char() {

    unsigned char scancode;

    while (1) {

        scancode = inb(0x60);

        // ignore key releases
        if (scancode & 0x80)
            continue;

        switch (scancode) {

            case 0x1E: return 'a';
            case 0x30: return 'b';
            case 0x2E: return 'c';
            case 0x20: return 'd';
            case 0x12: return 'e';
            case 0x21: return 'f';
            case 0x22: return 'g';
            case 0x23: return 'h';
            case 0x17: return 'i';
            case 0x24: return 'j';
            case 0x25: return 'k';
            case 0x26: return 'l';
            case 0x32: return 'm';
            case 0x31: return 'n';
            case 0x18: return 'o';
            case 0x19: return 'p';
            case 0x10: return 'q';
            case 0x13: return 'r';
            case 0x1F: return 's';
            case 0x14: return 't';
            case 0x16: return 'u';
            case 0x2F: return 'v';
            case 0x11: return 'w';
            case 0x2D: return 'x';
            case 0x15: return 'y';
            case 0x2C: return 'z';

            case 0x39: return ' ';
            case 0x1C: return '\n';
        }
    }
}

static inline void outb(unsigned short port, unsigned char value) {
    __asm__ volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}

void update_cursor() {

    unsigned short position = cursor / 2;

    outb(0x3D4, 14);
    outb(0x3D5, position >> 8);

    outb(0x3D4, 15);
    outb(0x3D5, position);
}

void kernel_main() {
    clear_screen();

    print("Welcome to Sapt OS\n");
    print("> ");

    while (1) {

        char c = get_char();

        // ENTER key
        if (c == '\n') {

            print("\n");
            print("> ");
            update_cursor();

        } else {

            // print typed character
            char str[2];

            str[0] = c;
            str[1] = '\0';

            print(str);
            update_cursor();
        }
    }
}