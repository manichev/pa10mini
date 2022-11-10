# pa10project

В данном репозитории анализируется ТЗ проекта.

Прототипы ПА10мини были разработаны на С++ и C#

For students of BMSTU CAD/CAE/PDM/PLM Department, Moscow

Проект PA10mini на С++ проверен на Windows XP (sp3) и Windows 7,8 (32 bit и 64 bit) строго с компилятором MicroSoft Visual Studio 2008  и конфигурацией win32.
Из каталога .../distrib дистрибутивов:
1. MicroSoft Visual Studio 2008 желательно иметь на диске С:
2. Инсталлировать Qt для MicroSoft Visual Studio 2008
3. Переписать содержимое каталога Qwt для MicroSoft Visual Studio 2008 в каталог C:/Qwt
4. Переписась  содержимое каталога win_flex_bizon для MicroSoft Visual Studio 2008 в каталог C:/win_flex_bison
5. Из каталога .../sources исходников:
   Переписать содержимое .../PA10mini в каталог С:/PA10mini
6. Создать переменную среды:
QTDIR
C:\Qt\4.8.5
7. Добавить в переменную среды (строго в начало описания этой переменной!):
Path
C:\Program Files\Microsoft Visual Studio 9.0\Common7\IDE;C:\Program Files\Microsoft Visual Studio 9.0\VC\bin;c:\win_flex_bison;%SystemRoot%\system32;
8. Скомпилировать проект  в каталоге С:/PA10mini и запустить на выполнение, проверить 2 режима ввода - математический и схемный.

Если каталоги Windows, MicroSoft Visual Studio 2008 и Program Files (Program Files (x86)) находятся не на диске C:, то надо заменить С: на другой диск в соотвествующих путях и скорректировать makefile в каталоге: C:\PA10mini\PA10mini\manzhuk\fcttask

Скачать все файлы проекта PA10mini на C++ можно по ссылке:
https://yadi.sk/d/S7yNYGJA5WRCZg
Эти коды компилируются и работают, - репозиторий PA10mini

Скачать все файлы проекта PA10mini на C# можно по ссылке:
https://yadi.sk/d/dRNygY-HirlE0Q
Это старые коды требуют отладки, подробные оптсания в дилломах Баженова и Алиева

Также выложены исходники предыдущего проекта ПА9:
https://disk.yandex.ru/d/BIEPc6IpCKaWqQ
