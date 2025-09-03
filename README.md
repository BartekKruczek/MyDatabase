# MyDatabase

This repository contains example how to create and update simple database in C language. It's been made for educational purposes.

## How to use

User can communicate with database file through **make** statement with additional options:
- `clean`; clean previously created binary files inside *bin* directory,
- `run`; required with **make** statement every time used would like to interact with database.

On top of that, after **make run** option, there are possible following flags:
- `n`; single use flag to create new database file,
- `f`;(required) filepath to desired database file either to create new one or interact with existing,
- `a`; append new employee to database with following syntax: *Name;Address;Hours worked*,
- `l`; list all correctly added employees with their id, name, address and worked hours accordingly,
- `u`; update worked hours existing employee passing following syntax: *Name;Address;New hours*,
- `h`; print help.

## Examples

To clean the project, run:
```bash
make clean
```

To build the project, create new file, append and list employees:
```bash
make run ARGS="-n -f mydbfile.db -a "Jan Kowalski;Warszawa;10" -l"
```

To open and interact with exisitng database just skipp `-n` flag.