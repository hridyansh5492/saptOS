int cursor = 0;

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
    print("Simple Bootable Operating System\n\n");
    print("> ");

    while (1);
}