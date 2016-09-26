#Compilation

Pour compiler, executer la commande `make compile`

#Execution

Pour lancer le programme de multiplication des entier, executer la commande `make execNumbers`

Pour lancer le programme *display_stack*, executer la commande `make displayStack`

#Resultats pour try_mul

```
$ make execNumbers
./try_mul
A list of int, please
1 2 3
product = 6
```

```
$ make execNumbers
./try_mul
A list of int, please
1 2 3 0 4
product = 0
```

```
$ make execNumbers
./try_mul
A list of int, please
4 3 1
product = 12
```

```
$ make execNumbers
./try_mul
A list of int, please

product = 1
```

#Resultats pour display_stack


```
$ make displayStack
./display_stack
func: main              esp : 0xffa47710         ebp : 0xffa47728
func: nothing_to_do     esp : 0xffa476f0         ebp : 0xffa47708
func: useless_cpt       esp : 0xffa476e0         ebp : 0xffa476f8
param : 0xffa47700
func: useless_cpt       esp : 0xffa476b0         ebp : 0xffa476c8
param : 0xffa476d0
func: useless_cpt       esp : 0xffa47680         ebp : 0xffa47698
param : 0xffa476a0
func: useless_cpt       esp : 0xffa47650         ebp : 0xffa47668
param : 0xffa47670
func: main              esp : 0xffa47710         ebp : 0xffa47728
```

Ici l'on peut voir que lorsque l'on rentre dans la fonction *nothing_to_do*, les adresses de **esp** et **ebp** ne sont plus les mêmes que celles de la fonction main. Ceci montre que la fenêtre courant à changé et que l'on a empilé le contexte correspondant à la fonction *nothing_to_do*. Ensuite, dans la fonction main, nous executons *useless_cpt* on peut voir queles adresses de **esp** et **ebp** ont encore changés pour la même raison que si dessus. Lorsque l'on appelle récursivement *useless_cpt* on peut voir que les adresses de **esp** et **ebp** change de nouveau, car l'on empile un deuxième contexte correspondant à un autre *useless_cpt*, on a donc une pile avec comme:<br/>
|&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|<br/>
| useless_cpt |<br/>
|&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|<br/>
 \-------------<br/>
|&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|<br/>
| useless_cpt |<br/>
|&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|<br/>
\-------------<br/>
|&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|<br/>
|&nbsp;&nbsp;&nbsp;&nbsp;main &nbsp;&nbsp;&nbsp;&nbsp;|<br/>
|&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|<br/>
 \-------------<br/>

On peut aussi noter que l'addresses du paramètre de *useless_cpt* n'est plus la même non plus, simplement car ce ne sont pas les mêmes paramètres. Chaque contexte de *useless_cpt* possède sont propre paramètre, respectivement:
|&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|<br/>
| useless_cpt |<br/>
|&nbsp;&nbsp;&nbsp;&nbsp;param&nbsp;&nbsp;&nbsp;&nbsp;| <- ici<br/>
 \-------------<br/>
|&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|<br/>
| useless_cpt |<br/>
|&nbsp;&nbsp;&nbsp;&nbsp;param&nbsp;&nbsp;&nbsp;&nbsp;| <- et ici<br/>
\-------------<br/>
|&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|<br/>
|&nbsp;&nbsp;&nbsp;&nbsp;main &nbsp;&nbsp;&nbsp;&nbsp;|<br/>
|&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|<br/>
 \-------------<br/>

Après tous les appels à *useless_cpt*, on les dépiles un à un jusqu'à ce que le premier appel se termine et on retourne dans *main*. Voilà pourquoi les addresses de *main* à la dernière ligne sont les mêmes que celles de la première ligne.
