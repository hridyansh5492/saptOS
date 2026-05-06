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

void kernel_main() {
    print("Welcome to Sapt OS\n");
    print("Before clear...\n");

    // delay loop (just for demo)
    for (int i = 0; i < 100000000; i++);

    clear_screen();

    print("Screen Cleared!\n");
    print("> ");

    while (1);
}