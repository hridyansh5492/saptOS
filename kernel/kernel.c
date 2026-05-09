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

        // Ignore key release codes
        if (scancode & 0x80)
            continue;

        char c = 0;

        switch (scancode) {
            case 0x1E: c = 'a'; break;
            case 0x30: c = 'b'; break;
            case 0x2E: c = 'c'; break;
            case 0x20: c = 'd'; break;
            case 0x12: c = 'e'; break;
            case 0x21: c = 'f'; break;
            case 0x22: c = 'g'; break;
            case 0x23: c = 'h'; break;
            case 0x17: c = 'i'; break;
            case 0x24: c = 'j'; break;
            case 0x25: c = 'k'; break;
            case 0x26: c = 'l'; break;
            case 0x32: c = 'm'; break;
            case 0x31: c = 'n'; break;
            case 0x18: c = 'o'; break;
            case 0x19: c = 'p'; break;
            case 0x10: c = 'q'; break;
            case 0x13: c = 'r'; break;
            case 0x1F: c = 's'; break;
            case 0x14: c = 't'; break;
            case 0x16: c = 'u'; break;
            case 0x2F: c = 'v'; break;
            case 0x11: c = 'w'; break;
            case 0x2D: c = 'x'; break;
            case 0x15: c = 'y'; break;
            case 0x2C: c = 'z'; break;
            case 0x39: c = ' '; break;
            case 0x1C: c = '\n'; break;
        }

        // wait until key release
        while (!(inb(0x60) & 0x80));

        return c;
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