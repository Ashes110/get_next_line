# get_next_line

"get_next_line" is a function that returns one line at a time from a given file descriptor.

# Usage

**1. Using it in your code**

```c
#include "get_next_line.h"
```

**2. Compiling the program**

```bash
gcc <filename> get_next_line.c get_next_line_utils.c
```

To change the buffer size when using the read function

```bash
gcc -D BUFFER_SIZE=<size> <filename> get_next_line.c get_next_line_utils.c
```
