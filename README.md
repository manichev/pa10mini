# ПА 10 "Мини"
Позволяет вводить схемное и текстовое описание системы обыкновенных дифференциальных уравнений или дифференциально-алгебраических систем, с возможность ее решения и вывода результата на графики:
![image](https://user-images.githubusercontent.com/19983888/201083592-39b3b945-f0ba-4632-8add-3b1104e4679f.png)
![image](https://user-images.githubusercontent.com/19983888/201084970-a4c9907c-7b93-4e94-a605-a5d2330e9de1.png)
![image](https://user-images.githubusercontent.com/19983888/201083799-862dc67f-adc6-4a20-beaa-c72db9d53064.png)

Решение уравнений, заданных в текствовм виде:  
![image](https://user-images.githubusercontent.com/19983888/201086828-daed3283-8536-4e83-a59c-d97d5bc9824f.png)
![image](https://user-images.githubusercontent.com/19983888/201086736-a265b1b5-2569-42d3-9890-2a6a3da63f46.png)
![image](https://user-images.githubusercontent.com/19983888/201086665-831fecd5-a6ae-4e04-8c76-148b5e1db92a.png)

В данном репозитории анализируется ТЗ проекта ПА 10.

Прототипы ПА10мини были разработаны на С++ и C#

For students of BMSTU CAD/CAE/PDM/PLM Department, Moscow

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

## Настройка программы
Под Windows в настройках указать путь к g++, например: 
```
C:/Qt/Tools/mingw810_64/bin/c++.exe
```

## Запуск программы
Для работы программы необходимо скопировать директорию `manzhuk` вместе со всем ее содержимым 
в директорию с исполняемым файлом (или рядом с директрией `debug` или `release` в каталоге сборки).

## Другие версии проекта ПА

Скачать все файлы проекта PA10mini на C# можно по ссылке:
https://yadi.sk/d/dRNygY-HirlE0Q
Это старые коды требуют отладки, подробное описание в дипломах Баженова и Алиева.

Также выложены исходники предыдущего проекта ПА9:
https://disk.yandex.ru/d/BIEPc6IpCKaWqQ
