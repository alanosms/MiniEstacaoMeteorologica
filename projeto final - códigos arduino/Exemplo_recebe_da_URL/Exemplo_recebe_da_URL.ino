#include <WiFi.h>
#include <HTTPClient.h> //Biblioteca para acessar como cliente
#define USE_SERIAL Serial //variavel para usar a Porta Serial de uma maneira diferente

#include <LiquidCrystal.h>
 
// Create An LCD Object. Signals: [ RS, EN, D4, D5, D6, D7 ]
LiquidCrystal My_LCD(13, 12, 14, 27, 26, 25);

void setup() {

  USE_SERIAL.begin(115200); //inicia a serial
  USE_SERIAL.flush();//limpa a serial 

  // Initialize The LCD. Parameters: [ Columns, Rows ]
  My_LCD.begin(16, 2);
  // Clears The LCD Display
  My_LCD.clear();
  My_LCD.print("Mini Estacao 1.0");
  My_LCD.setCursor(0,1); 
  My_LCD.print("By Andre");
  
  //ALTERAR ESTA LINHA  **********************  ALTERAR ESTA LINHA **************************  ALTERAR ESTA LINHA **************  ALTERAR ESTA LINHA 
  WiFi.begin("M2M", "senai2410");

  
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(">>>>>>>> CONECTOU!!!!!!!!!");
  My_LCD.clear();
}

void loop() {
  //SE O wIfI ESTÁ CONECTADO
  if ((WiFi.status() == WL_CONNECTED)) {
    HTTPClient http; //Cria o objeto ou variável http do tipo HTTPcliente
    
    //URL que vai enviar os dados ao Servidor (página Web dados_para_esp32.php)
    String minhaURL = "http://";
    
    //***ALTERAR ESTA LINHA  ***************  ALTERAR ESTA LINHA *************************************  ALTERAR ESTA LINHA ***************  ALTERAR ESTA LINHA **************
    //Obtenha o IP da máquina com o XAMPP instalado
    minhaURL.concat("192.168.0.50"); //Aqui vai o IP do site (maquina com o XAMPP instalado para receber os dados)

    
    minhaURL.concat("/project_final/dados_para_esp32.php");
    
    
    //URL utilizada: http://IP da máquina que tem o XAMPP instalado e rodando/AulaInsert/dadosParaESP32.php
    http.begin(minhaURL);
    
    
    USE_SERIAL.print("[HTTP] realizando a requisição para a página Web dados_para_esp32.php ...\n");
    My_LCD.clear();
    // começa a  conexão com o WebService e obtem o código HTTP de resposta
    int httpCode = http.GET();
    //Se o httpCode foi respondido como positivo
    if (httpCode > 0) {
      USE_SERIAL.printf("[HTTP] Encontrou o Servidor. \n");
      USE_SERIAL.printf("[HTTP] GET... codigo recebido: %d\n", httpCode);
      //Se Existe a PÁGINA no endereço URL o código é 200
      if (httpCode == HTTP_CODE_OK) {
        String resutadoDaPaginaWeb = http.getString();//armazena o resultado da página, o que veio do servidor, experimente outras URL
        USE_SERIAL.println("===============================================");
        USE_SERIAL.println(".......... Resulado Recebido da página ........");
        USE_SERIAL.println(resutadoDaPaginaWeb);
        USE_SERIAL.println("********* Final do Conteudo recebido **********");
        String valores = resutadoDaPaginaWeb;
        valores.trim();
        My_LCD.print("Data:");
        My_LCD.setCursor(0,1); 
        for (int i = 0; i <= 9; i++) {
            My_LCD.print(valores[i]);
            delay(200);
        }
        delay(1500);
        My_LCD.clear();
        My_LCD.print("Horario:");
        My_LCD.setCursor(0,1);
        for (int i = 11; i <= 18; i++) {
            My_LCD.print(valores[i]);
            delay(200);
        } 
        delay(1500);
        My_LCD.clear();
        My_LCD.print("Temperat./Humid.");
        My_LCD.setCursor(0,1);
        for (int i = 20; i <= 27; i++) {
            My_LCD.print(valores[i]);
            delay(200);
        } 
        delay(1500);
        
      }
    } else {
      //erro se a página não for encontrada
      USE_SERIAL.printf("[HTTP] erro: %s\n", http.errorToString(httpCode).c_str());

    }
    http.end();
  }
  else
  {
    //se não conectar no WiFI não faz nada
    USE_SERIAL.printf("[HTTP] Sem conexão Wi-Fi, reinicie o ESP32 ou verifique o nome e senha da Rede WiFi \r\n");
  }

  delay(10000); //aguarda 10 segundos para enviar novamente...
}
