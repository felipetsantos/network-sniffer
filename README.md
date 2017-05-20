# Instruções compilação
Para compilar é necessário executar o seguinte comando:
```
gcc -o tb1 tb1.c
```
# Instruções para excução
Para executar o programa é necessário ter permissão de root. 
```
sudo ./tb1
```
Ao executar o comando acima, o programa vai listar as interfaces de rede e solicitar que seja digitado o número da oṕção que representa a interface de rede que o sniffer vai capturar os pacotes. 

Executar o comando abaixo para rodar o programa e salvar o resultado em um arquivo de texto:
```
sudo ./tb1 3 >> resultado.txt
```

Onde o parametro "3" é o número da interface de rede. Para descobrir o número da interface de rede é necessário rodar o programa no primeiro formato pois a ordem em que o programa mostra as interfaces é diferente da ordem que o comando `ifconfig` apresenta.