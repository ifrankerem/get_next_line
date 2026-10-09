<div align="center">

# 📄 get_next_line

**Read one line at a time from a file descriptor — no matter how big the file.**

![Language](https://img.shields.io/badge/language-C-00599C?style=flat-square)
![Build](https://img.shields.io/badge/build-make-427819?style=flat-square)
![Norminette](https://img.shields.io/badge/norm-42%20standard-2b9348?style=flat-square)
![Stars](https://img.shields.io/github/stars/ifrankerem/get_next_line?style=flat-square)

</div>

---

## 📋 Table of Contents

- [About](#about)
- [How It Works](#how-it-works)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Project Layout](#project-layout)
- [Design Notes](#design-notes)
- [Author](#author)
- [Acknowledgements](#acknowledgements)

---

## 📖 About

**get_next_line** returns a single line read from a file descriptor, newline included, without losing the rest of the stream between calls. It is the workhorse utility behind `minishell`, `so_long` and `cub3d`, where files and maps get consumed one line at a time.

The signature is deliberately boring:

```c
char *get_next_line(int fd);
```

Returns the line, `NULL` on end-of-file or error.

---

## ⚙️ How It Works

1. `read()` fills a buffer of `BUFFER_SIZE` bytes and appends it to a **static** remainder string.
2. The remainder is scanned for `\n`.
3. Everything up to and including the newline is copied out as the return value.
4. Whatever follows the newline stays parked in the static buffer for the next call.
5. On EOF with an empty remainder, the buffer is freed and `NULL` is returned.

That static variable is what makes the function stateful without a global — and also why the implementation is careful about freeing it exactly once.

---

## 🚀 Getting Started

**Prerequisites**

- `gcc` or `clang`
- `make`

**Build**

```sh
git clone https://github.com/ifrankerem/get_next_line.git
cd get_next_line
```

Compile with your own buffer size:

```sh
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
    get_next_line.c get_next_line_utils.c main.c -o demo
```

---

## 💻 Usage

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int   fd;
    char *line;

    fd = open("file.txt", O_RDONLY);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

---

## 🗂 Project Layout

```
get_next_line/
├── get_next_line.c        # buffer read + line extraction
├── get_next_line_utils.c  # join, remainder and free helpers
└── get_next_line.h        # public header
```

---

## 🧠 Design Notes

- `BUFFER_SIZE` is a compile-time `-D` flag, so the same source works for `1` or for `1000000`.
- Handles files with and without a trailing newline, and empty files.
- No leaks: the static remainder is released on EOF and on read errors.
- Only `read`, `malloc` and `free` are used for I/O.

---

## 👤 Author

**İrfan Kerem Arslan** — [@ifrankerem](https://github.com/ifrankerem)

---

## 📄 License

Built for the **42 Common Core** curriculum. Shared for learning and portfolio purposes.

---

## 🙏 Acknowledgements

- [awesome-readme](https://github.com/matiassingers/awesome-readme) — structure inspiration for this README