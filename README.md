# Project 1.2 — MyString

Безопасная альтернатива стандартной `string.h` с защитой от buffer overflow по умолчанию.

## 🎯 Цель проекта

Стандартная библиотека `<string.h>` (glibc) содержит функции, которые **не проверяют размер буфера** и **не гарантируют null-терминацию**. Это приводит к уязвимостям:
- **CWE-120** — Buffer Copy without Checking Size of Input
- **CWE-170** — Improper Null Termination
- **CWE-476** — NULL Pointer Dereference

Цель проекта — написать собственную библиотеку `mystring.h`, где **безопасность встроена в контракт** каждой функции (по аналогии с `strlcpy` из OpenBSD).

## 🗺 План работы (Roadmap)

### Шаг 1 ✅ — Подготовка структуры тестов для libc
Создать тесты, которые **доказывают уязвимости** стандартных функций `string.h`.

### Шаг 2 ⬜ — Реализация безопасной библиотеки `mystring.h`
Написать собственные версии функций с защитой от переполнения.

### Шаг 3 ⬜ — Тестирование `mystring.h`
Показать, что те же самые атаки, которые ломают libc, **не работают** против `mystring.h`.

### Шаг 4 ⬜ — Презентация и документация
Подготовить демонстрацию с примерами уязвимостей и их исправлений.

## 🧪 Тестируемые функции (Шаг 1)

### Group 1 — Copy
- `strcpy`   — CWE-120 (переполнение)
- `strncpy`  — CWE-170 (нет `\0` при усечении)
- `strlcpy`  — безопасная альтернатива

### Group 2 — Concatenation
- `strcat`   — CWE-120 (переполнение)
- `strncat`  — CWE-193 (off-by-one)
- `strlcat`  — безопасная альтернатива

### Group 3 — Length & Compare
- `strlen`   — CWE-125 (out-of-bounds read при отсутствии `\0`)
- `strcmp`   — CWE-476 (NULL dereference)
- `strncmp`  — edge cases с `n=0`

### Group 4 — Search
- `strchr`   — CWE-476, CWE-125
- `strstr`   — CWE-476, пустой needle

### Group 5 — Tokenize
- `strtok`   — CWE-362 (не thread-safe), CWE-676 (модифицирует исходную строку)

## 🛠 Технологии

- Язык: **C99**
- Компилятор: **GCC / Clang**
- Тестирование: **AddressSanitizer** (`-fsanitize=address`), **UBSan** (`-fsanitize=undefined`)

## 📂 Структура проекта


```
Project-1.2
├─ Makefile
├─ README.md
├─ src
├─ test
└─ test_default_libc
   ├─ group_1_copy
   │  ├─ testStrCpy.c
   │  ├─ testStrLCpy.c
   │  └─ testStrNCpy.c
   ├─ group_2_concatenation
   │  ├─ testStrCat.c
   │  ├─ testStrLCat.c
   │  └─ testStrNCat.c
   ├─ group_3_length_compare
   │  ├─ testStrCmp.c
   │  ├─ testStrLen.c
   │  └─ testStrNcmp.c
   ├─ group_4_search
   │  ├─ testStrChr.c
   │  └─ testStrStr.c
   ├─ group_5_tokenize
   │  └─ testStrTok.c
   ├─ test.h
   └─ test_runner.c

```
