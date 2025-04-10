# Hash293

## Описание проекта
**Hash293** – это кастомная хеш-функция, разработанная на C++ с целью обеспечения эффективного и безопасного хеширования данных. 
Проект ориентирован на изучение криптографических методов хеширования и их применения в современных системах безопасности.

## Возможности
- **Производительное хеширование** данных
- **Минимизация коллизий** благодаря продуманному алгоритму
- **Поддержка тестирования** с помощью Google Test
- **Кроссплатформенная сборка** с использованием CMake
- **Оптимизированная работа с памятью**

## Установка зависимостей (MSYS2 + GCC)
Перед сборкой проекта необходимо установить:

```sh
pacman -S mingw-w64-x86_64-gcc
pacman -S mingw-w64-x86_64-cmake
pacman -S mingw-w64-x86_64-gtest
pacman -S mingw-w64-x86_64-libsodium
pacman -S mingw-w64-x86_64-toolchain
```

## Сборка и запуск
1. Клонируйте репозиторий:
   ```sh
   git clone https://github.com/Eglant1ne/Hash293.git
   cd Hash293
   ```
2. Создайте директорию сборки и перейдите в неё:
   ```sh
   mkdir build && cd build
   ```
3. Запустите CMake:
   ```sh
   cmake .. -G "MinGW Makefiles"
   ```
4. Соберите проект:
   ```sh
   mingw32-make
   ```

## Запуск тестов
После сборки проекта тесты можно запустить с помощью:
```sh
./Hash293Tests
```

> [!NOTE]
> Hash293 можно использовать для:
> - Хранения паролей в хешированном виде
> - Контроля целостности данных
> - Построения криптографических протоколов

## Документация
Для удобства работы с кодом каждый файл снабжён детализированной документацией, описывающей основные принципы работы хеш-функции.

```cpp
#include <iostream>
#include "Hash293.h"

/**
 * @brief Entry point for the Hash293App application.
 * Example of use.
 */
int main() {
    const char* data = "data";
    int dataSize = strlen(data);

    std::string hash_secure = Hash293::generate_hash293pw(data, dataSize, 4);
    for(auto c: hash_secure) 
         std::cout << c;
    std::cout << std::endl;
    std::cout << Hash293::verify_hash293pw(hash_secure, data, dataSize) << std::endl;

    return 0;
}
```

## Авторы
- **Eglant1ne** – разработчик проекта

> [!TIP]
> Проект распространяется под лицензией **MIT**.
