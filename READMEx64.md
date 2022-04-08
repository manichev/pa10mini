# Сборка и запуск ПА10-мини

## Windows

### Общие шаги

1. Установить [Qt5](https://www.qt.io/download-open-source).
   При запуске установщика поставить галочку напротив Qt5.xx (например, 15),  
MinGW (например, mingw730_64) и Qt Creator, если собираетесь собирать в нем.

2. Скачать [QWT](https://qwt.sourceforge.io/). Архив содержит .pro файл, его можно открыть и собрать с помощью Qt Creator'а.
Сборка и установка QWT под minGW:  
- открыть cmd;  
- задать переменные окружения, вызвав `C:\Qt\5.x.x\mingw81_64\bin\qtenv2.bat`  
- `mkdir build && cd build`;  
- `qmake ..`;  
- `C:\Qt\Tools\mingw810_64\bin\mingw32-make.exe`;  
- `C:\Qt\Tools\mingw810_64\bin\mingw32-make.exe install`;  
- отредактировать файл проекта `.pro`, указав путь к `qwt.prf`:  
`windows: include ( $$QWT_DIR/features/qwt.prf )`  

3. Скачать [dlfcn-win32](git@github.com:dlfcn-win32/dlfcn-win32.git).  
Собрать проект можно посредством Qt Creator'a, выбрав тот же комплект, что и при сборке `QWT`.  
В файле проекта указать путь к исходным кодам:  
`windows: INCLUDEPATH += C:\...\dlfcn-win32\src`

### Сборка под Visual Studio

1. Скачать и установить [Visual Studio Community Edition](https://docs.microsoft.com/visualstudio/install/install-visual-studio) версии 2017 или 2019 (проверялось на 2017).
2. Создать решение
`qmake -tp vc`
3. Собрать `QWT` и `libdl` под Visual Studio.
4. В свойствах проекта указать пути к библиотечным файлам `QWT` и `libdl`.

### Сборка в Qt Creator
Выбрать комплект аналогичный комплектам сборки библиотек.
После сборки скопировать директорию `manzhuk` в корневую директорию сборки.

## Linux
Установить библиотеку `qwt-qt5`:
```
$ sudo apt-get install libqwt-qt5-*
```

# Настройка программы
Под Windows в настройках указать путь к g++.

# Запуск программы
Для работы программы необходимо скопировать `manzhuk` в директорию с исполняемым файлом.