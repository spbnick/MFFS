void
reset(void)
{
    volatile unsigned int *rcc_apb2enr = (unsigned int *)(0x40021000 + 0x18);
    volatile unsigned int *gpioc_crh = (unsigned int *)(0x40011000 + 0x04);
    volatile unsigned int *gpioc_odr = (unsigned int *)(0x40011000 + 0x0c);
    volatile unsigned int i;
    /* Enable clock to GPIO port C */
    *rcc_apb2enr |= 1 << 4;
    /* Configure the PC13 pin for open-drain output, 2MHz max speed */
    *gpioc_crh = (*gpioc_crh & ~ (0xf << ((13-8)*4))) |
                 (6 << ((13-8)*4));
    /* Forever */
    while (1) {
        /* Wait */
        for (i = 0; i < 500000; i++);
        /* Toggle PC13 */
        *gpioc_odr ^= 1 << 13;
    }
}

int STACK[256];

const void *vectors[] __attribute__ ((section (".vectors"))) = {
    STACK + sizeof(STACK) / sizeof(*STACK),
    reset
};
