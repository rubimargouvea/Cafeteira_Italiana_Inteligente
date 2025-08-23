# Cafeteira_Italiana_Inteligente
Este arquivo serve para a criação de uma cafeteira inteligente, utilizando a Alexa como principal método de controle do dispositivo. Para fazer o link entre a automação e a Alexa, foi utilizado o Sirinc Pro, sendo responsável pela comunicação e controle dos dispositivos.

Para o correto funcionamento do sistema, é necessário a criação do dispositivo no Sirinc Pro, com prévio cadastro do usuário, só após a criação é gerado os dados de "APP_KEY", "APP_SECRET" e "DEVICE_ID", linhas 24, 25 e 26, respectivamente, que serão substituídos no código "main.ino".
Além dos dados acima citados é necessário a inclusão da rede WI-FI e senha, linhas 32 e 33. 
Quando concluída esta etapa será necessário a compilação dos códigos "main.ino" e "Cafeteira.h".

OBSERVAÇÃO IMPORTANTE: Os dois códigos devem ser colocados na mesma pasta para que a IDE do Arduino consiga encontrar no momento da compilação.
