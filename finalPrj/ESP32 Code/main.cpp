#include <WiFi.h>
#include <WebServer.h>
#include "webpages.h"
#define apSSID "SMOP"
#define apPassword "12345678"
#define NUM_SENSORS 6

IPAddress serverIP(192, 168, 1, 100);
WebServer atmegaServer(80);
WebServer server(80);

int sensorReadings[NUM_SENSORS] = {0, 0, 0, 0, 0, 0};
bool flag =  false;

void handleRoot() {
  // Serve the configuration page
  String page = "<!DOCTYPE html><html lang='en'><head> <meta charset='UTF-8'> <meta name='viewport' content='width=device-width, initial-scale=1.0'> <title>Wi-Fi Setup</title> <style> body { font-family: Arial, sans-serif; background-color: #1a1a1a; color: #fff; margin: 0; padding: 0; } .container { width: 80%; margin: 0 auto; padding: 50px 0; } .form-container { border: 2px solid #444; border-radius: 10px; padding: 20px; margin-bottom: 20px; background-color: #333; } h1 { font-size: 36px; text-align: center; margin-bottom: 30px; } .form-container h2 { font-size: 24px; margin-bottom: 20px; } .form-group { margin-bottom: 20px; } label { font-size: 20px; margin-bottom: 5px; display: block; } input[type='text'], input[type='password'] { width: calc(100\% - 24px); padding: 10px 12px; border: none; border-bottom: 2px solid #eaeaea; background-color: transparent; color: #fff; font-size: 16px; transition: border-bottom-color 0.3s ease; } input[type='text']:focus, input[type='password']:focus { outline: none; border-bottom-color: #eaeaea; } .button-container { text-align: center; /* Center button */ } input[type='submit'] { background-color: #4CAF50; color: #fff; padding: 12px 20px; border: none; border-radius: 4px; cursor: pointer; font-size: 18px; transition: background-color 0.3s ease; } input[type='submit']:hover { background-color: #45a049; } </style></head><body> <div class='container'> <h1>Wi-Fi Setup</h1> <div class='form-container'> <form action='/connect' method='POST'> <div class='form-group'> <label for='ssid'>SSID:</label> <input type='text' name='ssid' id='ssid' required /> </div> <div class='form-group'> <label for='password'>Password:</label> <input type='password' name='password' id='password' required /> </div> <div class='form-group button-container'> <input type='submit' value='Connect' /> </div> </form> </div> </div></body></html>";
  server.send(200, "text/html", page);
}

void parseSensorReadings(const char* data) {
  char* token;
  int index = 0;
  // Tokenize the received data using ","
  token = strtok((char*)data, ",");
  while (token != NULL && index < NUM_SENSORS) {
    sensorReadings[index++] = atoi(token);
    token = strtok(NULL, ",");
  }
  if (index == NUM_SENSORS) {
    // All sensor readings parsed successfully
    Serial.println("patch recieved:");
    for(int i = 0; i < 6; i++){
      Serial.println(sensorReadings[i]);
    }
  }
}

void readFromATmega32(){
  static char receivedData[50];
  static int dataIndex = 0;
  char delimiter = '#';
  char receivedChar;

  while (Serial2.available()) {
    receivedChar = Serial2.read();
    Serial.println(receivedChar);

    if (receivedChar == delimiter) {
      Serial.println("HERE");

      receivedData[dataIndex] = '\0';
      parseSensorReadings(receivedData);

      dataIndex = 0;
    } else if (receivedChar == '*'){
      dataIndex = 0; 
    }else {
      receivedData[dataIndex++] = receivedChar;

      if (dataIndex >= sizeof(receivedData)) {
        dataIndex = 0;
      }
    }

    atmegaServer.handleClient();
  }
}


void handleMainSys() {
  String page = "<!DOCTYPE html><html lang=\"en\"><head> <meta charset=\"UTF-8\"> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"> <title>Sensor Readings</title> <style> body { font-family: Arial, sans-serif; background-color: #1a1a1a; color: #fff; margin: 0; padding: 0; } .container { width: 80%; margin: 0 auto; padding: 50px 0; } .sensor { border: 2px solid #444; border-radius: 10px; padding: 20px; margin-bottom: 20px; background-color: #333; text-align: center; /* Center text */ } h1 { font-size: 36px; text-align: center; margin-bottom: 30px; } .sensor h2 { font-size: 24px; margin-bottom: 20px; } .reading { font-size: 20px; margin-bottom: 10px; } .value { font-size: 28px; font-weight: bold; } .fire { color: red; font-weight: bold; } .high-moisture, .high-light { color: green; font-weight: bold; } .optimal { color: green; font-weight: bold; } .low-moisture, .low-light { color: red; font-weight: bold; } </style></head><body> <div class=\"container\"> <h1>Sensor Readings</h1> <div class=\"sensor\"> <h2>DHT11 Temperature and Humidity Sensor</h2> <div class=\"reading\"> Temperature: <span class=\"value\">";
  page += String(sensorReadings[0]);
  page += "</span> &deg;C </div> <div class=\"reading\"> Humidity: <span class=\"value\">";
  page += String(sensorReadings[1]);
  page += "</span> % </div> </div> <div class=\"sensor\"> <h2>Flame Sensor</h2> <div class=\"reading flame-status\">";

  // Set text and styling for the flame sensor
  page += sensorReadings[2] == 0 ? "<span class=\"optimal\">Optimal</span>" : "<span class=\"fire\">Fire Detected</span>";
  page += "</div> </div> <div class=\"sensor\"> <h2>Moisture Sensor</h2> <div class=\"reading moisture-status\"> Moisture Percentage: <span class=\"";
  page += sensorReadings[3] >= 50 ? "high-moisture" : "low-moisture";
  page += "\">";
  page += String(sensorReadings[3]);
  page += " %</span> </div> </div> <div class=\"sensor\"> <h2>Gas Sensor</h2> <div class=\"reading gas-status\">";

  // Set text and styling for the gas sensor
  page += sensorReadings[4] == 0 ? "<span class=\"optimal\">Optimal</span>" : "<span class=\"fire\">Gas Leak Detected</span>";
  page += "</div> </div> <div class=\"sensor\"> <h2>LDR (Light Dependent Resistor)</h2> <div class=\"reading light-intensity\"> Light Intensity Percentage: <span class=\"";
  page += sensorReadings[5] >= 50 ? "high-light" : "low-light";
  page += "\">";
  page += String(sensorReadings[5]);
  page += " %</span> </div> </div> </div><script>";

  // JavaScript code to dynamically update styling for moisture and light
  page += "var moistureValue = " + String(sensorReadings[3]) + ";";
  page += "var lightValue = " + String(sensorReadings[5]) + ";";
  page += "var moistureElement = document.querySelector('.moisture-status span');";
  page += "moistureElement.classList.toggle('low-moisture', moistureValue < 30);";
  page += "moistureElement.classList.toggle('high-moisture', moistureValue >= 30);";
  page += "var lightElement = document.querySelector('.light-intensity span');";
  page += "lightElement.classList.toggle('low-light', lightValue < 50);";
  page += "lightElement.classList.toggle('high-light', lightValue >= 50);";

  // Auto-refresh page every 1.5 seconds
  page += "setInterval(function(){window.location.reload(true);}, 1500);";
  page += "</script></body></html>";

  atmegaServer.send(200, "text/html", page);
}

void handleConnect() {
  String ssid = server.arg("ssid");
  String password = server.arg("password");
  // Connect to the user's network
  WiFi.begin(ssid.c_str(), password.c_str());
  Serial.print("Connecting to ");
  Serial.println(ssid);
  // Wait for connection to establish
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connected to WiFi");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  // Close the access point
  WiFi.softAPdisconnect(true);

  server.close();
  flag = true;
  atmegaServer.on("/", handleMainSys);
  atmegaServer.begin();
  Serial.println("ATmega32 message server started");
  
}

void setup() {
  Serial.begin(9600); // Serial communication with PC
  Serial2.begin(9600);  // Serial communication with ATmega32
  // Set up ESP32 as an access point 
  WiFi.softAP(apSSID, apPassword);
  // Print IP address of the access point
  Serial.println("Access Point IP address:");
  Serial.println(WiFi.softAPIP());
  // Route for serving the configuration page
  server.on("/", handleRoot);
  server.on("/connect", handleConnect);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
  atmegaServer.handleClient();
  if(flag){
  readFromATmega32();
  }
  //Serial.println("still here y a3m yaseen y atyeb");
}
