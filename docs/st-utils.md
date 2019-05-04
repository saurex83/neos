# Работа с программатором на Linux

### Установка st-link
Для работы с программатором st-link требуется установить:
У меня была проблема с компиляцией, важно установить
cmake и libusb. Причем если установить пакет libusb-dev то приложение не будет 
собираться. нужно именно libusb-1.0-0-dev.
Для установки программы:
cd build/Release
make clean - важная команда, без нее не собереться ничего
make install

Еще одна особенность- запусти /sbin/ldconfig для обновления установленых
библиотек в системе. Без этого будет ругаться на libstlink.so.1

sudo apt-get install libusb-1.0-0-dev
git clone https://github.com/texane/stlink stlink.git
cd stlink
make
//install udev rules
sudo cp etc/udev/rules.d/49-stlinkv* /etc/udev/rules.d/
//and restart udev
sudo udevadm control --reload


### Прошивка 
st-flash  write firmware.bin  0x08000000

## Работа с отладчиком
Сначало запускается gdb-server:
st-util -2 -p 4500

Потом отладчик:
arm-none-eabi-gdb template.elf

Подключаемся к серверу:
tar ext :4500

Загружаем прошивку:
load

Запускаем:
continue (или run)

Установка точки остановки:
b main

Остановка программы:
CNTR-C

Есть еще возможноть запускать с ключом -tui