# Temperatura da água do reservatório pelo Telegram

## Projeto
O objetivo do projeto é utilizar um ESP8266 para consultar remotamente a temperatura da água de um reservatório de água quente doméstico, ligado a placas de aquecimento solar. Um _bot_ do telegram informa a temperatura da água quando um comando é enviado por mensagem.

### Materiais utilizados
- ESP 8266
- Termistor de 10kΩ
- Resistor de 10kΩ

### Funcionamento

O termistor foi conectado a uma porta analógica do ESP 8266 através de um divisor de tensão com o resistor para aferimento da temperatura, feita pela biblioteca <Thermistor.h>. 

Um _bot_ do Telegram foi configurado e era acessado pela biblioteca <UniversalTelegramBot.h>. Sempre que o comando `/temp` era recebido por mensagem, a leitura da temperatura era efetuada pelo microcontrolador e enviada por mensagem ao usuário.
