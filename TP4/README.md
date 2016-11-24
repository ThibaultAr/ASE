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

---

- Créer une nouveau volume
- Création d'un nouveau volume dans un emplacement où il existe déjà un volume

```
$ ./vm
> new
Taille (en secteurs):
16
Indice cylindre:
0
Indice secteur:
0
> new
Taille (en secteurs):
16
Indice cylindre:
0
Indice secteur:
1
Impossible de creer un volume ici : il existe deja un volume a cette emplacement
```

# Fonctionnement final
```
$ ./vm
> new
Taille (en secteurs):
64
Indice cylindre:
1
Indice secteur:
1
> quit
mbr sauve
[0]

$ ./mknfs
[0]

$ ./if_nfile < lorem.txt
1
[0]

$ ./if_pfile 1
Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.
[0]

$ ./if_nfile < lorem.txt
4
[0]

$ ./if_pfile 4
Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.
Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.
Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.
Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.
[0]

$ ./if_nfile
12
k[0]

$ ./if_pfile 12
k[0]

$ ./if_cfile 12
14
[0]

$ ./if_pfile 14
k[0]

$ ./if_dfile 14
[0]

$ ./if_pfile 14
[0]

$ ./if_dfile 1
[0]

$ ./if_dfile 4
[0]

$ ./if_pfile 1
[0]

$ ./if_pfile 4
[0]

```
