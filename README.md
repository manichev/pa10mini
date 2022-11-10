# ПА 10 "Мини"
Позволяет вводить схемное и текстовое описание системы обыкновенных дифференциальных уравнений или дифференциально-алгебраических систем, с возможность ее решения и вывода результата на графики:
![image](https://user-images.githubusercontent.com/19983888/201083592-39b3b945-f0ba-4632-8add-3b1104e4679f.png)
![image](https://user-images.githubusercontent.com/19983888/201084970-a4c9907c-7b93-4e94-a605-a5d2330e9de1.png)
![image](https://user-images.githubusercontent.com/19983888/201083799-862dc67f-adc6-4a20-beaa-c72db9d53064.png)

![image](https://user-images.githubusercontent.com/19983888/201086828-daed3283-8536-4e83-a59c-d97d5bc9824f.png)
![image](https://user-images.githubusercontent.com/19983888/201086736-a265b1b5-2569-42d3-9890-2a6a3da63f46.png)
![image](https://user-images.githubusercontent.com/19983888/201086665-831fecd5-a6ae-4e04-8c76-148b5e1db92a.png)

В данном репозитории анализируется ТЗ проекта ПА 10.

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
