# Поле чудес


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

Пример необходимых функций для клиента:
1) Видеть оставшееся количество попыток
2) Видеть использованные буквы
3) Видеть оставшиеся буквы
4) Сдаться(!)
