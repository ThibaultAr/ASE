Arloing Thibault
Dubois Yann

#TP3

##Avec yield en cascade

Quand ni ping, ni pong ne s'arrête.
```
$ ./pingpong
A1B2C1A2B1C2A1B2C1A2B1C2A1B2C1A2B1C2A1B2C1A2B1C2A1B2C1A2B1C2A1B2C1A2B1C2A1B2C1A2B1C2A1B2C1A2B1C2A1B2C1A2B1C2A1B2C1A2B1C2A1B2C1A2B1C2A1B2C1A2B1C2A1B2C1A2B1C2A1B2
```

Quand pong s'arrête, mais pas ping.
```
$ ./pingpong
A1B2CA
A process has ended
BCABCABCABCABC
```

Quand les deux s'arrêtent.

```
A1B2C
A process has ended
hello world
```
##Après avoir codé start_schedule

Quand ni ping, ni pong ne s'arrête.
```
$ ./pingpong
ABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABC1212121212121212121212
```

Quand pong s'arrête, mais pas ping.
```
$ ./pingpong
ABCABCA12CABCABCA
```

Quand les deux s'arrêtent
```
$ ./pingpong
ABC12
A process has ended
hello world
```

##Synchronisation entre contexte

```
Produit l'objet 1
Met l'objet 1 à l'indice 0
Produit l'objet 2
Met l'objet 2 à l'indice 1
Produit l'objet 3
Retire l'objet 1 à l'indice 0
Utilise l'objet 1
Retire l'objet 2 à l'indice 1
Utilise l'objet 2
Met l'objet 3 à l'indice 0
Produit l'objet 2
Met l'objet 2 à l'indice 1
Produit l'objet 3
Retire l'objet 3 à l'indice 0
Utilise l'objet 3
Retire l'objet 2 à l'indice 1
Utilise l'objet 2
Met l'objet 3 à l'indice 0
Produit l'objet 2
Met l'objet 2 à l'indice 1
```
