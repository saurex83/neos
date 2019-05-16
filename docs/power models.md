# Режим пониженного энергопотребления
Микроконтроллер STM32L151 имеет несколько режимов пониженного энергопотребления.
Режим нужен такой, что бы можно было работать с таймерами. Таймер по 
прерыванию выводил бы МК из пониженого потребления. 
Таймер RTC wakeup не годится, его нельзя перепрограмировать без останова, но 
только таймер wakeup может пробудить МК из глубоких режимов сна. Следовательно
все режимы глубокого сна принципиально не устраивают.

Выбирая между двумя вариантами, остановимся на втором так как ток потребления
на 29% ниже не смотря на задержку включения. Частота 127 кГц необходима
для таймеров TIM9,10,11 так как частота шины APB должна быть минимум в два раза
выше частоты LSE. 
Основную частоту примем MCU MSI = 4.2 Мгц из-за низкого тока потребления.

## Вариант 1
Режим Low power run mode. Он умеренно потребляет ток при рабочем таймере. 
Вход в режим LPRM производит ОС neos. Код IDLE циклично проверяет MCU что он 
наодится в режиме LPRM. Любое возникшее прерывание переводит МК в режим
RUN_MODE (MSI = 4.2 МГц) после выхода из прерывания код IDLE увидит что частота 
измениласьи завершится, разблокировав планировщик задач.

## Вариант 2
Режим low power sleep mode с частотой MSI = 127 кГц, Fhclk = 127 кГц с включеной
флеш памятью и таймером. 
Состояние MCU в low power sleep mode:
* Регулятор в режиме пониженого энергосбережения
* RAM выключена (данные сохраняются)
* Флеш память выключена
* Тактирование CPU выключено
* Тактирование AHB и APB выкляется аппаратно когда вся переферия отключена
* Vcore = range 2. Только тогда можно войти в LP sleep.
* MSI = range 1 (65 кГц)
* IO сохраняют свое состояние
* ADC не работает

Выход из LP sleep mode
* Выход по WFI
* Регулятор в переходит в основной режим (1.8V, range 1)
* Флеш память включается
* Задержка влючения равна времени выхода регулятора из пониженого потребления
* Источник тактового сигнала тот же что был и перед переходом в сон


## Sleep mode
Остановлен только CPU. Переферия продолжает работать.
Ток потребления Fmsi=65 кГц 60 мка. Fmsi=4.2 Мгц 250 мка.
Время пробуждения 0.36 мкс.
IM10LPEN 
SYSCFGLPEN смотри док. активность таймеров во время сна

## Low power run mode
Тактирование CPU осуществляется от MSI на частоте 65 кГц, Fhclk = 32 кГц.
Внутриний регулятор находится в режиме пониженого энергопотребления
Типовое потреблении 24 мка (32 макс.) при работе с флешпамяти.
При MSI = 65 кГц, Fhclk = 65 кГц ток потребления 31 мка

## Low power sleep mode
MSI = 65 кГц, флеш выключена. Ток потребления 4.4 мка.
MSI = 65 кГц, флеш включена.  Ток потребления 17.5 мка.
MSI = 65 кГц, Fhclk = 65 кГц флеш,uart,tim9. Ток потребления 18 мка.
MSI = 131 кГц, Fhclk = 127кГц флеш,uart,tim9. Ток потребления 22 мка.
Время пробуждения 32 мкс.


## Stop mode with RTC, Stop mode without RTC
Совсем не подходит.

## Standby mode with RTC, Standby mode without RTC
Совсем не подходит.

## Время стабилизации генераторов
HSI 3.7 мкс(typ), 6 мкс (max)  
LSI 200 мкс (max)

Время включения:
MSI range 0 30 мкс
MSI range 5 5  мкс

Время стабилизации:
MSI range 0 40 мкс
MSI range 5 2  мкс

## Токи потребления в различный режимах Run mode.
MSI = 65  кГц 50  мкА
MSI = 4.2 МГц 900 мкА
HSI = 16  Мгц 4 ма