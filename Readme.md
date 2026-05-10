# Sapt OS v1.0

A basic bootable operating system developed using **C** and **x86 Assembly** for educational and learning purposes.

---

## 📖 Description

Sapt OS is a mini operating system project created to understand how operating systems work internally — from the boot process to kernel execution and hardware-level screen and keyboard interaction.

This project helped in learning:

* How bootloaders work
* Kernel development basics
* VGA text mode programming
* Keyboard input handling
* Memory-level screen output
* Command-line interfaces
* Basic shell functionality

Sapt OS boots using **GRUB**, loads a custom kernel, and runs inside **QEMU Emulator**.

---

## 🚀 Features

### Core Features

* Bootable Operating System
* GRUB Bootloader Integration
* Custom Kernel in C and Assembly
* VGA Text Mode Output
* Custom Print Function
* Screen Clearing Support
* Cursor Management

### Terminal Features

* Keyboard Input Handling
* Interactive Command Prompt
* Backspace Support
* Command History
* Auto Screen Scrolling
* Colored Terminal Output

### Built-in Commands

* `help` → Show available commands
* `info` → Display OS information
* `clear` → Clear terminal screen
* `history` → Show command history
* `time` → Display system uptime
* `shutdown` → Halt the operating system

### Arithmetic Commands

* `add <a> <b>`
* `sub <a> <b>`
* `mul <a> <b>`
* `div <a> <b>`
* `rem <a> <b>`

Example:

```bash
add 10 5
mul 6 7
```

### UI Features

* Boot Animation
* ASCII Startup Banner
* Colored Text Interface

---

## 🛠️ Technologies Used

* C Programming Language
* x86 Assembly (NASM)
* GRUB Bootloader
* QEMU Emulator
* GCC Compiler
* LD Linker
* Makefile Automation

---

## 📂 Project Structure

```text
saptOS/
│
├── iso/
│   └── boot/
│       ├── grub/
│       │   └── grub.cfg
│       └── kernel.bin
│
├── kernel/
│   ├── boot.s
│   └── kernel.c
│
├── linker.ld
├── Makefile
└── sapt.iso
```

---

## ⚙️ Installation & Setup

### Clone Repository

```bash
git clone https://github.com/hridyansh5492/saptOS
cd saptOS
```

### Install Required Packages (Linux)

```bash
sudo apt install build-essential gcc nasm qemu-system-x86 grub-pc-bin xorriso
```

### Build & Run

```bash
make run
```

---

## 💻 Usage

Once the OS boots, use commands like:

```bash
help
info
history
time
add 10 5
shutdown
```

---

## 🎯 Purpose of the Project

This project was built as a semester mini project and learning experiment to understand low-level system programming and operating system fundamentals.

---

## 📌 Future Improvements

* Interrupt Handling
* Real-Time Clock Support
* File System
* Mouse Support
* Better Shell Commands
* Memory Management
* Multitasking

---

## 🤝 Contributing

Contributions and suggestions are welcome.

Fork the repository and create a pull request.

---

## 📄 License

This project is licensed under the MIT License — see the [LICENSE](LICENSE) file for details.

---

## 👨‍💻 Author

Developed by **Hridyansh**

GitHub: https://github.com/hridyansh5492

---

## ⭐ Feedback

If you found this project interesting, consider giving it a star on GitHub.
