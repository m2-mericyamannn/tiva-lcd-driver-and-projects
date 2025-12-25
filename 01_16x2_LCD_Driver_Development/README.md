### 1 - 16x2 LCD Driver Development
This project demonstrates how to drive a 16x2 character LCD (HD44780 compatible) using a Tiva C Series microcontroller in 4-bit mode.
The project includes low-level GPIO control, LCD initialization, command/data transmission, and basic text output.
The implementation is written using TivaWare DriverLib.

### Project Structure
01_16x2_LCD_Driver_Development/
│
├── lcd.c        → LCD driver implementation
├── lcd.h        → LCD pin definitions & function prototypes
└── main.c       → Application entry point and example usage

### Hardware Requirements

Tiva C Series Microcontroller (e.g. TM4C123GH6PM)

16x2 Character LCD (HD44780 compatible)

10kΩ Potentiometer (LCD contrast)

Breadboard & jumper wires

220Ω Resistor

### LCD Pin Connections
| LCD Pin | Function        | Tiva Port / Pin |
| ------- | --------------- | --------------- |
| RS      | Register Select | PE1             |
| RW      | Read / Write    | PE2             |
| EN      | Enable          | PE3             |
| D4      | Data Bit 4      | PB4             |
| D5      | Data Bit 5      | PB5             |
| D6      | Data Bit 6      | PB6             |
| D7      | Data Bit 7      | PB7             |
| VSS     | GND             | GND             |
| VDD     | +5V             | 5V              |
| V0      | Contrast        | Potentiometer   |

### LCD Driver Logic

The LCD is operated in 4-bit mode, meaning data is sent in two nibbles (high nibble first, then low nibble).

### lcd.h – Header Definitions
Pin Definitions
#define RS  GPIO_PIN_1
#define RW  GPIO_PIN_2
#define EN  GPIO_PIN_3

#define D4  GPIO_PIN_4
#define D5  GPIO_PIN_5
#define D6  GPIO_PIN_6
#define D7  GPIO_PIN_7

### lcd.h Function Prototypes
void LCD_init(void);
void writeCommand(void);
void LCD_clear(void);
void writeData(void);
void LCD_setcursorPosition(unsigned char row, unsigned char column);
char data(char value);
void printf(char *s);

### lcd.c – Function Descriptions
LCD_init()

Initializes GPIO ports and configures the LCD in 4-bit mode.
Performs:

GPIO configuration

LCD wake-up sequence

Display ON / Cursor OFF

Clear display

Return cursor home

writeCommand()

Sends a command pulse to the LCD by toggling the EN pin.

writeData()

Sends a data enable pulse when writing character data.

data(char value)

Sends one ASCII character to the LCD using 4-bit communication.

LCD_setcursorPosition(row, column)

Moves the cursor to the desired position.

Row	Address
1	0x80
2	0xC0
printf(char *s)

Writes a string to the LCD character by character.

clear_LCD()

Clears the LCD screen and resets cursor position.

### main.c – Application Flow
int main(void)
{
    Tiva_init();
    LCD_init();

    LCD_setcursorPosition(1, 1);
    printf("*m2Mericyamannn*");

    LCD_setcursorPosition(2, 1);
    printf("****************");

    while(1);
}

What Happens:

System clock and GPIO initialized

LCD initialized in 4-bit mode

Two lines of text written

Program enters infinite loop

### Example Output
*m2Mericyamannn*
****************

⚠️ Notes
Delays are implemented using SysCtlDelay

For better portability, delay values may be adjusted based on system clock

✅ Summary

This project provides a clean and structured example of driving a 16x2 LCD with Tiva C

![Potentiometer Wiring](images/1breadboardphoto.jpeg)
