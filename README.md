# Cafeteira_Italiana_Inteligente
Este arquivo serve para a criação de uma cafeteira inteligente, utilizando a Alexa como principal método de controle do dispositivo. Para fazer o link entre a automação e a Alexa, foi utilizado o Sinric Pro, sendo responsável pela comunicação e controle dos dispositivos.

Para o correto funcionamento do sistema, é necessário a criação do dispositivo no Sinric Pro,acesse https://sinric.pro/ e cadastre-se, só após a criação é gerado os dados de "APP_KEY", "APP_SECRET" e "DEVICE_ID", linhas 24, 25 e 26, respectivamente, que serão substituídos no código "main.ino".
Além dos dados acima citados é necessário a inclusão da rede WI-FI e senha, linhas 32 e 33. 
Quando concluída esta etapa será necessário o upload para a ESP32 dos códigos "main.ino" e "Cafeteira.h". Após estes passos seguir o manual no item "6. Configuração e Conexão com a Alexa".

OBSERVAÇÃO IMPORTANTE: Os dois códigos devem ser colocados na mesma pasta para que a IDE do Arduino consiga encontrar no momento da compilação.
