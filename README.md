# Tic Tac Toe

**Игра крестики нолики**

## Режимы

- Локальный против бота **(в разработке)**
- Локальный на одном компьютере вдвоем **(в разработке)**
- Мультиплеер

## Сборка проекта

Для сборки проекта необходимо иметь:

- `CMake` 3.10+
- `Make`
- `C++ 17`+
- `SFML` version 3.0+
- `nlohmann_json` version 3.12.0+

### Arch Linux

```bash
sudo pacman -Syu
sudo pacman -S gcc make cmake sfml nlohmann-json
```

### Ubuntu/Debian

```bash
sudo apt update
sudo apt install build-essential cmake libsfml-dev nlohmann-json3-dev
```

### Fedora

```bash
sudo dnf check-update
sudo dnf install gcc-c++ make cmake SFML-devel json-devel
```

### macOS

```bash
brew update
brew install cmake sfml nlohmann-json
```

### Windows

Стоит использовать пакетный менеджер `vcpkg` совместно с компилятором `MSVC` или `MinGW`

```bash
vcpkg install sfml:x64-windows
vcpkg install nlohmann-json:x64-windows
```

**Сборка через CMake**

```bash
mkdir build && cd build && cmake .. && make
```

