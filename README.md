# ft\_nm
A completely UNIX project from 42. In this project I attempt to recreate the utility software `nm`.

The objective of this software is to list all symbols contained in binary files, and filter and sort them accordingly to the options passed on arguments.

My version only supports ELF binaries x86 and x86\_64.

## Options
### Requiered by subject
There is no mandatory options. But, as printing all symbols without ordering nor filtering seemed a little bit like cheating. Therefore I chose to implement the same default comportement as the original `nm`. Doing so, I used the standard of ELF to read the headers and find the symbol names, values and types.

### Bonus options of the subject
- `-a`: Displays all symbols, including debugging symbols.
- `-g`: Only displays external symbols.
- `-u`: Only displays undefined symbols.
- `-r`: Sorts the symbols in inverse order.
- `-p`: Doesn't sort the symbols at all.

### Personnal additions
- `-h`: Displays a help message
- `-v`: Displays the current version of the project 
