int cursor = 0;

unsigned char text_color = 0x07;

char history[10][100];
int history_count = 0;

void clear_screen() {
    char *video_memory = (char*) 0xb8000;

    for (int i = 0; i < 80 * 25 * 2; i += 2) {
        video_memory[i] = ' ';      // empty character
        video_memory[i + 1] = 0x07; // color
    }

    cursor = 0; // reset cursor to top
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

void print(char *str) {

    char *video_memory = (char*) 0xb8000;

    for (int i = 0; str[i] != '\0'; i++) {

        if (str[i] == '\n') {

            cursor = (cursor / 160 + 1) * 160;

            // scroll if screen full
            if (cursor >= 80 * 25 * 2) {
                scroll();
            }

        } else {

            video_memory[cursor++] = str[i];
            video_memory[cursor++] = text_color;

            // scroll if screen full
            if (cursor >= 80 * 25 * 2) {
                scroll();
            }
        }
    }

    update_cursor();
}

static inline unsigned char inb(unsigned short port) {
    unsigned char result;
    __asm__ volatile ("inb %1, %0" : "=a"(result) : "Nd"(port));
    return result;
}

char get_char() {

    unsigned char scancode;

    while (1) {

        // wait for key press
        scancode = inb(0x60);

        // ignore releases
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
            case 0x0E: c = '\b'; break;
            case 0x1C: c = '\n'; break;

            default:
                continue;
        }

        // WAIT FOR KEY RELEASE
        while (1) {

            unsigned char release = inb(0x60);

            if (release == (scancode | 0x80))
                break;
        }

        return c;
    }
}

int strcmp(char str1[], char str2[]) {

    int i = 0;

    while (str1[i] != '\0' && str2[i] != '\0') {

        if (str1[i] != str2[i]) {
            return 0;
        }

        i++;
    }

    return str1[i] == str2[i];
}

void set_color(unsigned char color) {
    text_color = color;
}

void delay() {

    for (int i = 0; i < 100000000; i++);
}

void show_banner() {

    set_color(0x0A);

    print("   _____             _      ____   _____ \n");
    print("  / ____|           | |    / __ \\ / ____|\n");
    print(" | (___   __ _ _ __ | |_  | |  | | (___  \n");
    print("  \\___ \\ / _` | '_ \\| __| | |  | |\\___ \\ \n");
    print("  ____) | (_| | |_) | |_  | |__| |____) |\n");
    print(" |_____/ \\__,_| .__/ \\__|  \\____/|_____/ \n");
    print("              | |                        \n");
    print("              |_|                        \n\n");

    set_color(0x0F);
}

void halt() {

    while (1) {
        __asm__ volatile ("hlt");
    }
}

void strcpy(char dest[], char src[]) {

    int i = 0;

    while (src[i] != '\0') {

        dest[i] = src[i];
        i++;
    }

    dest[i] = '\0';
}

void scroll() {

    char *video_memory = (char*) 0xb8000;

    // move all lines one row up
    for (int i = 0; i < 24 * 80 * 2; i++) {

        video_memory[i] = video_memory[i + 160];
    }

    // clear last line
    for (int i = 24 * 160; i < 25 * 160; i += 2) {

        video_memory[i] = ' ';
        video_memory[i + 1] = text_color;
    }

    // move cursor to last line
    cursor = 24 * 160;
}

void kernel_main() {

    clear_screen();

    set_color(0x0A);
    print("Starting Sapt OS...\n");
    delay();

    set_color(0x0E);
    print("Loading modules...\n");
    delay();

    print("Initializing kernel...\n");
    delay();

    set_color(0x0F);
    print("Done.\n\n");
    delay();

    show_banner();

    set_color(0x0A);
    print("Welcome to Sapt OS\n");
    set_color(0x0F);
    print("Type 'help' for commands\n\n");
    set_color(0x0F);
    print("> ");

    char input[100];
    int index = 0;

    while (1) {

        char c = get_char();

        // ENTER
        if (c == '\n') {

            input[index] = '\0';

            if (history_count < 10) {
                strcpy(history[history_count], input);
                history_count++;
            }

            print("\n");

            if (strcmp(input, "help")) {

                print("Commands:\n");
                print("help  - show commands\n");
                print("clear - clear screen\n");
                print("info  - OS information\n");
                print("history - show command history\n");
                print("shutdown - shut down the system\n");

            } else if (strcmp(input, "info")) {

                print("Sapt OS v1.0\n");
                print("Basic Bootable Operating System\n");
                print("Made by Hridyansh\n");

            } else if (strcmp(input, "clear")) {

                clear_screen();

            } else if (strcmp(input, "history")) {

                print("Command History:\n");

                for (int i = 0; i < history_count; i++) {

                    print(history[i]);
                    print("\n");
                }
            } else if (strcmp(input, "shutdown")) {

                set_color(0x0C);

                print("Shutting down Sapt OS...\n");
                print("System Halted.");

                halt();
                outb(0x604, 0x2000);  // shutdown QEMU
            } else {

                print("Unknown command\n");
            }

            print("\n> ");

            index = 0;
        }

        // BACKSPACE
        else if (c == '\b') {

            if (index > 0) {

                index--;

                input[index] = '\0';

                cursor -= 2;

                char *video_memory = (char*) 0xb8000;

                video_memory[cursor] = ' ';
                video_memory[cursor + 1] = 0x07;

                update_cursor();
            }
        }

        // NORMAL CHARACTER
        else {

            input[index++] = c;

            char str[2];

            str[0] = c;
            str[1] = '\0';

            print(str);
        }
    }
}