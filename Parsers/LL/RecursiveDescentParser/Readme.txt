Это пример парсера рекурсивного спуска для следующей грамматики:

stmt →  expr | E (epsilon)
expr → term | term + expr
term →  fact | fact * term
fact → NUM | ( expr )
Где терминал символами являются символы NUM ( ) + *
Все остальные символы нонтерминал.