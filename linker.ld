ENTRY(kernel_main)

SECTIONS {
    . = 5M;

    .text : {
        *(.text)
    }

    .data : {
        *(.data)
    }

    .bss : {
        *(.bss)
    }
}