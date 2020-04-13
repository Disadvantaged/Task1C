# Поле чудес

**Задание**

Реализуйте игру “Поле чудес” между “клиентом” и “сервером”.

При подключении клиента, сервер присылает строку вида “****”, где * - неизвестная буква. Клиент угадывает буквы через стандартный ввод-вывод. Количество попыток угадать фиксировано. Сервер проверяет букву и возвращает клиенту слово с открытыми буквами.

Например:  
Клиент подключился к серверу  
Сервер отправляет слово “****” и общее число попыток - 5.  
Клиент пишет “а”  
Сервер отвечает “*а*а”  
Клиент пишет “п”  
Сервер отвечает “*а*а”  
Клиент пишет “м”  
Сервер отвечает “мама”  
Слово угадано.  

Подумайте, какие функции могут быть полезны и удобны для клиентов. Как реагировать серверу, если слово угадано или попытки кончились?

**Решения** 

* Клиенту будет удобно:
1) Видеть оставшееся количество попыток
2) Видеть оставшиеся/использованные буквы (например, в мобильной версии на клавиатуре затемнять уже использованные буквы)
3) В течение игры получать очков за отгаданные слова
4) Иметь возможность получить подсказку при наличии достаточного количества очков
5) Иметь возможность сдаться
6) Иметь возможность выбрать режим игры: один игрок или игра с соперниками

* Каждый игрок может иметь "звание" : от новичка до гуру. Если игрок угадывает определенное количество слов, его рейтинг повышается. 

* Если попытки кончились, сервер сообщает об этом игроку, и тот выбывает из игры. Если текущая игра была не одиночной, остальные 
игроки могут продолжить угадывать буквы. 

Итого, общие правила игры:
Клиент может выбрать, он играет один или с кем-то. Во втором случае он может создать новую игру, и передать код игры соперникам, чтобы они тоже подключились. Можно начать игру со случайными соперниками.
В течение игры игроки по очереди отгадывают буквы. Использованные буквы зачеркиваются/затемняются на клавиатуре у каждого игрока. Каждый игрок видит оставшееся у него количество попыток. Если у игрока заканчиваются попытки, он выбывает из игры. За каждую верную букву игрок получает какое-то количество очков, за неверную - теряет. В процессе игры игрок может взять подсказку, если обладает необходимым количеством очков. Выигрывает тот, кто последним назвал верную букву(т.е. отгадал слово). За каждую победу повышается рейтинг игрока, и в какой-то момент он получает новые звания (например ученик, студент, мыслитель, гуру и т.д.). Помимо этого, игрок может сдаться, но в этом случае его рейтинг понизится.

Система подсказок может быть простая: допустим, за условные 10 очков игроку открывается нужная буква. А можно сделать ее многоуровневой: например, открыть букву стоит 100 очков, а за 20 очков игрок увидит список из 10 букв, среди которых есть нужная.

Максимальное число участников в одной игре должно кореллировать с количеством попыток. 
