# ❌⭕ Tic Tac Toe (C++ Network Edition)

Простая реализация игры "Крестиков-ноликов" с поддержкой сетевой игры

## Режимы

- [x] **Мультиплеер** - сетевая дуэль (стабильно) 
- [ ] **Локальный (Hotseat)** - двое за одним ПК (в разработке)
- [ ] **Против ИИ** - одиночный режим (в разработке)

## Конфигурация

Создайте файл конфигурации `config.json` рядом с файлом игры и добавьте туда эти настройки:

```json
{
   "network": {
      "ip": "127.0.0.1",
      "port": 53000,
      "timeout": 15
   }
}
```

## Как играть по сети
1. **Сервер:** Один из игроков должен запустить приложение и выбрать режим сервера (настройте `server_ip` в `config.json`).
2. **Клиент:** Второй игрок вводит IP-адрес сервера в конфиге и запускает приложение.
3. **Порт:** Убедитесь, что порт `53000` (по умолчанию) открыт в вашем брандмауэре.

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

