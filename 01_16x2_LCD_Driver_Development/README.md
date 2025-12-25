# 01 – 16x2 LCD Driver Development

This project demonstrates how to drive a **16x2 character LCD (HD44780 compatible)** using a **Tiva C Series microcontroller** in **4-bit mode**.  
The implementation uses **TivaWare DriverLib** and focuses on low-level GPIO control, LCD initialization, and basic text output.

---

## Project Structure

```
01_16x2_LCD_Driver_Development/
│
├── lcd.c        → LCD driver implementation
├── lcd.h        → LCD pin definitions & function prototypes
└── main.c       → Application entry point and example usage
```

---

## Hardware Requirements

- Tiva C Series Microcontroller (e.g. TM4C123GH6PM)
- 16x2 Character LCD (HD44780 compatible)
- 10kΩ Potentiometer (LCD contrast)
- Breadboard & jumper wires
- 220Ω resistor

---

## LCD Pin Connections

| LCD Pin | Function        | Tiva Port / Pin |
|--------|------------------|-----------------|
| RS     | Register Select  | PE1             |
| RW     | Read / Write     | PE2             |
| EN     | Enable           | PE3             |
| D4     | Data Bit 4       | PB4             |
| D5     | Data Bit 5       | PB5             |
| D6     | Data Bit 6       | PB6             |
| D7     | Data Bit 7       | PB7             |
| VSS    | GND              | GND             |
| VDD    | +5V              | 5V              |
| V0     | Contrast         | Potentiometer   |

---

## LCD Driver Logic

The LCD operates in **4-bit mode**, meaning data is transferred in two steps  
(high nibble first, then low nibble).

---

## lcd.h – Header Definitions

### Pin Definitions
```c
#define RS  GPIO_PIN_1
#define RW  GPIO_PIN_2
#define EN  GPIO_PIN_3

#define D4  GPIO_PIN_4
#define D5  GPIO_PIN_5
#define D6  GPIO_PIN_6
#define D7  GPIO_PIN_7
```

### Function Prototypes
```c
void LCD_init(void);
void writeCommand(void);
void LCD_clear(void);
void writeData(void);
void LCD_setcursorPosition(unsigned char row, unsigned char column);
char data(char value);
void printf(char *s);
```

---

## lcd.c – Function Descriptions

### `LCD_init()`
Initializes GPIO ports and configures the LCD in 4-bit mode.

Includes:
- GPIO configuration  
- LCD wake-up sequence  
- Display ON / Cursor OFF  
- Clear display  
- Return cursor to home position  

---

### `writeCommand()`
Sends a command to the LCD by toggling the **EN** pin.

---

### `writeData()`
Sends a data pulse when writing character data.

---

### `data(char value)`
Sends a single ASCII character to the LCD using 4-bit communication.

---

### `LCD_setcursorPosition(row, column)`
Moves the cursor to the desired position.

| Row | DDRAM Address |
|-----|----------------|
| 1   | 0x80           |
| 2   | 0xC0           |

---

### `printf(char *s)`
Writes a null-terminated string to the LCD.

---

### `LCD_clear()`
Clears the LCD screen and resets the cursor.

---

## main.c – Application Flow

```c
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
```

### Execution Flow

- System clock and GPIO initialized  
- LCD initialized in 4-bit mode  
- Two lines of text written  
- Program enters infinite loop  

---

## Example Output

```
*m2Mericyamannn*
****************
```

---

## Notes

- Delays are implemented using `SysCtlDelay`
- Delay values may need adjustment depending on system clock

---

## Summary

This project provides a clean and structured example of driving a **16x2 LCD** using a **Tiva C microcontroller**, serving as a foundation for more advanced embedded applications.

---

![Potentiometer Wiring](images/1breadboardphoto.jpeg)
