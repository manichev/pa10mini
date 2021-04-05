# pa10project
For students of BMSTU CAD/CAE/PDM/PLM Department, Moscow
Actually C++ code only, C# code to be in future

Данный проект проверен на Windows XP (sp3) и Windows 7,8 (32 bit и 64 bit) строго с компилятором MicroSoft Visual Studio 2008  и конфигурацией win32.
Из каталога .../distrib дистрибутивов:
1. MicroSoft Visual Studio 2008 желательно иметь на диске С:
2. Инсталлировать Qt для MicroSoft Visual Studio 2008
3. Переписать содержимое каталога Qwt для MicroSoft Visual Studio 2008 в каталог C:/Qwt
4. Переписась  содержимое каталога win-flex-bizon для MicroSoft Visual Studio 2008 в каталог C:/win-flex-bison
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

Скачать все файлы проекта можно по ссылке:
https://yadi.sk/d/G90W2UG0W_N-Zg
