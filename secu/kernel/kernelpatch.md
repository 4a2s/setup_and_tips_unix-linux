canonical a dev un outils pour patcher le kernel celui-ci s'appelle : canonical livepatch
celui-ci fonctionne avec un compte ubuntu pro[https://ubuntu.com/pro/subscribe](gratuit jusqu'à 5 machhines)

install :
on commence par lié la machine au compte ubuntu pro
```
sudo pro attach
```
ensuite on active l'option
```
sudo pro enable livepatch
```
on verifie le status 
```
sudo canonical-livepatch status
```