pour mettre l'empreinte digitale dans le terminal, il faut editer le fichier : 
```
sudo nano /etc/pam.d/common-auth
```

et ajouter la ligne toute en haut :
```
auth    sufficient  pam_fprintd.so
```
