#include <WiFi.h>
#include <HTTPClient.h> //Biblioteca para acessar como cliente
#define USE_SERIAL Serial //variavel para usar a Porta Serial de uma maneira diferente

// ======================================================= dht inclusoes e funcoes
#include "DHTesp.h" // Click here to get the library: http://librarymanager/All#DHTesp
#include <Ticker.h>

float sensor_temp = 0;
float sensor_humid = 0;

#ifndef ESP32
#pragma message(THIS EXAMPLE IS FOR ESP32 ONLY!)
#error Select ESP32 board.
#endif

DHTesp dht;

void tempTask(void *pvParameters);
bool getTemperature();
void triggerGetTemp();

/** Task handle for the light value read task */
TaskHandle_t tempTaskHandle = NULL;
/** Ticker for temperature reading */
Ticker tempTicker;
/** Flag if task should run */
bool tasksEnabled = false;
/** Pin number for DHT11 data pin */
int dhtPin = 27;

bool initTemp() {
  byte resultValue = 0;
  // Initialize temperature sensor
  dht.setup(dhtPin, DHTesp::DHT11);
  Serial.println("DHT initiated");

  // Start task to get temperature
  xTaskCreatePinnedToCore(
      tempTask,                       /* Function to implement the task */
      "tempTask ",                    /* Name of the task */
      4000,                           /* Stack size in words */
      NULL,                           /* Task input parameter */
      5,                              /* Priority of the task */
      &tempTaskHandle,                /* Task handle. */
      1);                             /* Core where the task should run */

  if (tempTaskHandle == NULL) {
    Serial.println("Failed to start task for temperature update");
    return false;
  } else {
    // Start update of environment data every 20 seconds
    tempTicker.attach(20, triggerGetTemp);
  }
  return true;
}

void triggerGetTemp() {
  if (tempTaskHandle != NULL) {
     xTaskResumeFromISR(tempTaskHandle);
  }
}

void tempTask(void *pvParameters) {
  Serial.println("tempTask loop started");
  while (1) // tempTask loop
  {
    if (tasksEnabled) {
      // Get temperature values
      getTemperature();
    }
    // Got sleep again
    vTaskSuspend(NULL);
  }
}


bool getTemperature() {
  // Reading temperature for humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (it's a very slow sensor)
  TempAndHumidity newValues = dht.getTempAndHumidity();
  // Check if any reads failed and exit early (to try again).
  if (dht.getStatus() != 0) {
    Serial.println("DHT11 error status: " + String(dht.getStatusString()));
    return false;
  }

  sensor_temp = newValues.temperature;
  sensor_humid = newValues.humidity;
  return true;
}


// =========================================================

void setup() {

  USE_SERIAL.begin(115200); //inicia a serial
  USE_SERIAL.flush();//limpa a serial 
  
  //ALTERAR ESTA LINHA  **********************  ALTERAR ESTA LINHA **************************  ALTERAR ESTA LINHA **************  ALTERAR ESTA LINHA 
  WiFi.begin("M2M", "senai2410");

  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(">>>>>>>> CONECTOU!!!!!!!!!");
  
  //================= DHT
  initTemp();
  // Signal end of setup() to tasks
  tasksEnabled = true;
}

void loop() {

  
  
  //SE O wIfI ESTÁ CONECTADO
  if ((WiFi.status() == WL_CONNECTED)) {
    HTTPClient http; //Cria o objeto ou variável http do tipo cliente
    USE_SERIAL.print("[HTTP] iniciado ...\n");
    //URL que vai enviar os dados ao Servidor (página Web recebe_por_get.php)
    
    if (!tasksEnabled) {
      // Wait 2 seconds to let system settle down
      delay(2000);
      // Enable task that will read values from the DHT sensor
      tasksEnabled = true;
      if (tempTaskHandle != NULL) {
        vTaskResume(tempTaskHandle);
      }
    }
    yield();    
    
    String minhaURL = "http://";
    
    //***ALTERAR ESTA LINHA  ***************  ALTERAR ESTA LINHA *************************************  ALTERAR ESTA LINHA ***************  ALTERAR ESTA LINHA **************
    //Obtenha o IP da máquina com o XAMPP
    minhaURL.concat("192.168.0.50"); //Aqui vai o IP do site (maquina com o XAMPP instalado para receber os dados)

    
    minhaURL.concat("/project_final/recebe_dados_get.php?sensor_temp=");
    minhaURL.concat(String(sensor_temp)); //concatenando os dados que desejo enviar
    minhaURL.concat("&sensor_humid="); //concatenando dados da variavel
    minhaURL.concat(String(sensor_humid)); //concatenando os dados que desejo enviar

    Serial.println(minhaURL);
    
    //URL utilizada: http://IP da máquina que tem o XAMPP instalado e rodando/AulaInsert/recebe_por_get.php?nm=Jose&em=Jose@etec.com&st=www.etec.sp.gov.br&co=Apenas%20um%20coment%C3%A1rio&sx=masculino
    http.begin(minhaURL);
    
    
    USE_SERIAL.print("[HTTP] realizando a requisição para a página Web recebe_por_get.php ...\n");
    // começa a  conexão com o WebService e obtem o código HTTP de resposta
    int httpCode = http.GET();
    //Se o httpCode foi respondido como positivo
    if (httpCode > 0) {
      USE_SERIAL.printf("[HTTP] Encontrou o Servidor. \n");
      USE_SERIAL.printf("[HTTP] GET... codigo recebido: %d\n", httpCode);
      //Se Existe a PÁGINA no endereço URL o código é 200
      if (httpCode == HTTP_CODE_OK) {
        String resutadoDaPaginaWeb = http.getString();//armazena o resultado do Servidor
        USE_SERIAL.println("===============================================");
        USE_SERIAL.println(".......... Resulado Recebido da página ........");
        USE_SERIAL.println(resutadoDaPaginaWeb);
        USE_SERIAL.println("********* Final do Conteudo recebido **********");
        
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
