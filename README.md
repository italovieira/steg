#### Projeto de ITP/PTP sobre esteganografia.

O código foi feito utilizando a convenção de código que pode ser vista
[aqui](https://gist.github.com/davidzchen/9188090).

O repositório para este projeto pode ser encontrado em:
http://gitlab.com/italovieira/steg.

Para uma fácil compilação utilize o Makefile.

##### Exemplo de utilização:

Encode:

```shell
./steg -e boy.bmp < sample.pdf
```

Decode:

```shell
./steg -d boy.bmp
```
