# Automatizando um Bom Ar com Alexa (4Fun)

Para realizar esse projeto levei em consideração informações vindas dos seguintes links

[Blog Eletrogate](https://blog.eletrogate.com/automacao-residencial-com-alexa-amazon-e-nodemcu/)
[Repositório SINRIC](https://github.com/sinricpro/esp8266-esp32-sdk/tree/master/examples)

Eu segui os passos descritos no artigo da Eletrogate, criando uma conta e um elemento de switch que é o necessário para fazer esse projeto.

### O que é necessário?

Para o projeto é necessário um Bom-ar (No meu caso estou usando um air wick freshmatic) e alguns componentes eletrônicos.

![alt text](https://github.com/varellalexandre/bom_ar/blob/master/bom_ar.jpg?raw=true "Imagem do Bom Ar")

##### Detalhe eletrônico

![alt text](https://github.com/varellalexandre/bom_ar/blob/master/circuit.png?raw=true "Imagem do Circuito")

O circuito detalha como deverá funcionar o switch. Alguns pontos são importantes de ser levados em consideração

###### Como funciona um transistor?

O transistor tem 2 funções principais, a primeira é atuar como switch (interruptor), enquanto a segunda está voltada para amplificar a corrente recebida. Ele deve ser conectado a 3 elementos, um coletor, a base e o emissor. O papel da base é funcionar como switch, caso o transistor receba corrente na base, ele permitirá que flua corrente entre o coletor e emissor. Caso contrário ele não permitirá o fluxo da corrente. 

###### Porque não usar apenas do pino digital para ligar o motor?

O motor do bom ar utilizado é de 3V até 5V, por isso que a fonte do motor está sendo a própria fonte do microcontrolador. Porém ele não pode ser ligado direto no pino de GPIO por conta da corrente máxima ser 12mA [ESP8266](https://tttapa.github.io/ESP8266/Chap04%20-%20Microcontroller.html). O motor que é similar ao "Motor Solar Mini 300" apresenta uma corrente necessária de 58 mA, o que impossibilita o funcionamento.

###### O que devo considerar no cálculo?

O transistor quando o GPIO estiver ligado não deve amplificar a corrente a ponto de danificar a placa, tendo em vista que a energia utilizada é do próprio NodeMCU. Então, para realizar o cálculo avalie corretamente o resistor e o beta para não causar nenhum dano. No circuito que montei, coloquei o motor antes do transistor pois ele não receberia a corrente amplificada.

###### Como montar?

Eu apenas desliguei as pilhas conectadas ao CI do bom ar, e também desconectei o CI do motor.Em seguida testei com a ligação da imagem acima, o código bom_ar.ino foi o que eu passei para o microcontrolador. 

###### O que o código faz?

Similar ao código do Blog Eletrogate que citei acima, eu fiz uma alteração para poder funcionar corretamente o motor. O que queremos é que o motor ligue por uma fração de tempo e desligue depois desse tempo. Independente do sinal que mandarmos para o interruptor. O motor volta a posição inicial pela construção da peça. A pressão do aerosol empurra de volta o pino. Então basta acionar o motor por um intervalo de tempo e depois cortar seu funcionamento.


### Vídeo de Funcionamento

[![Vídeo do Funcionamento](http://img.youtube.com/vi/suouxLn4nFc/0.jpg)](http://www.youtube.com/watch?v=suouxLn4nFc "Vídeo Funcionamento")
