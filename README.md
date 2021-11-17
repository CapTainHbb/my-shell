# my-shell
simple linux shell created by captainhb

this linux shell supports following commands:

*cat

*rm

*mv

*clear

*tail

*head

*cp

*cd

*ls

*lsdir (list only directories)

*rename (usage: rename oldname newname)

also you can use pipelining!:

```
command1 > command2
```
to install this shell simple type:
```
make
```
to remove installed files:
```
make clean
```
example:
```
please enter a command>(/) ls

bin   cdrom  etc   lib    lib64   lost+found  mnt   root  sbin  srv  tmp  var

boot  dev    home  lib32  libx32  media       proc  run   snap  sys  usr
```
