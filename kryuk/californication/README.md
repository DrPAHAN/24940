# Californication - California Time Display

This project contains a C program that displays the current time in California (Pacific Standard Time / Pacific Daylight Time) on Linux systems.

## Program

### californication.c
Displays the current time in California timezone, automatically handling PST/PDT transitions.

**Features:**
- Shows current date and time in California timezone
- Automatically handles PST (UTC-8) and PDT (UTC-7) transitions
- Uses `America/Los_Angeles` timezone setting
- Displays timezone abbreviation (PST/PDT)
- Based on the reference implementation in `ex_time.c`

## Compilation

Use the provided Makefile to compile the program:

```bash
make all
```

## Usage

Run the program to see California time:

```bash
./californication
```

## Example Output

```
Время в Калифорнии (PST/PDT):
Wed Dec 18 05:30:45 2024
12/18/24 5:30 PST
```

## Reference

This program is based on `ex_time.c`, which demonstrates basic time handling in C. The `californication.c` program extends this functionality to display time in a specific timezone (California) rather than the system's local timezone.

## Requirements

- Linux operating system
- GCC compiler
- Standard C library with time functions

## Notes

- The program uses standard POSIX time functions
- Timezone changes are handled automatically by the system
- California timezone follows US daylight saving time rules
- If UTC time is 20:00, California time will be 12:00 (PST) or 13:00 (PDT)
