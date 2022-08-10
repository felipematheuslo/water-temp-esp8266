//https://blogmasterwalkershop.com.br/arduino/como-usar-com-arduino-termistor-ntc-10k-sensor-de-temperatura/

#include <Thermistor.h>
Thermistor temp(0);
int temperature;

#include <UniversalTelegramBot.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#define botToken "TELEGRAM BOT TOKEN"
WiFiClientSecure client;
UniversalTelegramBot bot(botToken, client);
char ssid[] = "WIFI SSID";
char password[] = "WIFI PASSWORD";
long checkTelegramDueTime;
int checkTelegramDelay = 1000;

void setup() {
  Serial.begin(9600);
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);
}

void handleNewMessages(int numNewMessages) {
  for (int i=0; i<numNewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    String text = bot.messages[i].text;

    String from_name = bot.messages[i].from_name;
    if (from_name == "") from_name = "Guest";

    if (text == "/temp") {
      temperature = temp.getTemp();
      Serial.print("Temperatura: ");
      Serial.print(temperature);
      Serial.println("ºC");
      bot.sendMessage(chat_id, "Temperatura da água: " + (String)temperature + "ºC");
    }

    if (text == "/start") {
      String welcome = "Comandos disponíveis:\n\n";
      welcome += "/temp : Mostra a temperatura da água quente\n";
      bot.sendMessage(chat_id, welcome, "Markdown");
    }
  }
}

// the loop routine runs over and over again forever:
void loop() {  
  int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
  while(numNewMessages) {
    Serial.println("Bot recieved a message");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
  }
}
