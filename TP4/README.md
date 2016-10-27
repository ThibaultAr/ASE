#MBR

##Fonctionnement de vm

- Ajout d'un volume
- Quitter en sauvegardant
- Ré exécuter vm
- Lister les volumes

```
$ ./vm
\> new
Taille (en secteurs):
16
Indice cylindre:
0
Indice secteur:
0
\> quit
mbr sauve
[0]
$ ./vm
\> list
1 volumes
(0, 0)	16	->	(1, 0)	base
```

---

- Lister les volumes
- Créer un volume
- Lister les volumes
- Supprimer un volume
- Lister un volume

```
$ ./vm
> list
0 volumes
> new
Taille (en secteurs):
16
Indice cylindre:
0
Indice secteur:
0
> list
1 volumes
(0, 0)	16	->	(1, 0)	base
> del
Volume a supprimer :
0
> list
0 volumes
```
