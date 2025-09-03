# MyDatabase
Database written in C, exercise purposes.

## How to use

To clean the project, run:
```
make clean
```

To build the project and create new file, run:
```
make run ARGS="-n -f mydbfile.db"
```

To open existing file, run:
```
make run ARGS="-f mydbfile.db"
```

To delete existing file, run:
```
make run ARGS="-d -f mydbfile.db"
```

In order to add an employee, one has to provide valid string structure after -a flag, e.g.:
```
-a "Jan Kowalski;Warszawa;10"
```
Notice that delimeter is semicolon without spaces before and after it.

To list all employees pass -l flag:
```
-a "Jan Kowalski;Warszawa;10" -l
```