

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

// Wifi network station credentials
#define WIFI_SSID "xxxxxxxxxxxxxx"
#define WIFI_PASSWORD "xxxxxxxxxxxxxx"
// Telegram BOT Token (Get from Botfather)
#define BOT_TOKEN "xxxxxxxisikan bot token disinixxxxxxx"

#define RELAY1_PIN 12
#define RELAY2_PIN 14
#define RELAY3_PIN 27
#define RELAY4_PIN 26
const unsigned long BOT_MTBS = 1000;  // mean time between scan messages

WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);
unsigned long bot_lasttime;  // last time messages' scan has been done

void handleNewMessages(int numNewMessages) {
  for (int i = 0; i < numNewMessages; i++) {
    String chat_id = bot.messages[i].chat_id;
    String text = bot.messages[i].text;

    String from_name = bot.messages[i].from_name;
    if (from_name == "")
      from_name = "Guest";
    if (text == "/start") {
      String welcome = "Welcome to Universal Arduino Telegram Bot Channel, " + from_name + ".\n";
      welcome += "Apa yang bisa di bantu !!!\n";
      bot.sendMessage(chat_id, welcome);
    } else if (text == "relay1on") {
      digitalWrite(RELAY1_PIN, LOW);
      String welcome = "Relay 1 turned ON.\n";
      bot.sendMessage(chat_id, welcome);
    } else if (text == "relay1off") {
      digitalWrite(RELAY1_PIN, HIGH);
      String welcome = "Relay 1 turned OFF.\n";
      bot.sendMessage(chat_id, welcome);
    } else if (text == "relay2on") {
      digitalWrite(RELAY2_PIN, LOW);
      String welcome = "Relay 2 turned ON.\n";
      bot.sendMessage(chat_id, welcome);
    } else if (text == "relay2off") {
      digitalWrite(RELAY2_PIN, HIGH);
      String welcome = "Relay 2 turned OFF.\n";
      bot.sendMessage(chat_id, welcome);
    } else if (text == "relay3on") {
      digitalWrite(RELAY3_PIN, LOW);
      String welcome = "Relay 3 turned ON.\n";
      bot.sendMessage(chat_id, welcome);
    } else if (text == "relay3off") {
      digitalWrite(RELAY3_PIN, HIGH);
      String welcome = "Relay 3 turned OFF.\n";
      bot.sendMessage(chat_id, welcome);
    } else if (text == "relay4on") {
      digitalWrite(RELAY4_PIN, LOW);
      String welcome = "Relay 4 turned ON.\n";
      bot.sendMessage(chat_id, welcome);
    } else if (text == "relay4off") {
      digitalWrite(RELAY4_PIN, HIGH);
      String welcome = "Relay 4 turned OFF.\n";
      bot.sendMessage(chat_id, welcome);
    } else if (text == "nyalasemua") {
      digitalWrite(RELAY1_PIN, LOW);
      digitalWrite(RELAY2_PIN, LOW);
      digitalWrite(RELAY3_PIN, LOW);
      digitalWrite(RELAY4_PIN, LOW);
      String welcome = "Relay Nyala Semua.\n";
      bot.sendMessage(chat_id, welcome);
    } else if (text == "matisemua") {
      digitalWrite(RELAY1_PIN, HIGH);
      digitalWrite(RELAY2_PIN, HIGH);
      digitalWrite(RELAY3_PIN, HIGH);
      digitalWrite(RELAY4_PIN, HIGH);
      String welcome = "Relay Mati Semua.\n";
      bot.sendMessage(chat_id, welcome);
    }
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println();

  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(RELAY2_PIN, OUTPUT);
  pinMode(RELAY3_PIN, OUTPUT);
  pinMode(RELAY4_PIN, OUTPUT);

  digitalWrite(RELAY1_PIN, HIGH);
  digitalWrite(RELAY2_PIN, HIGH);
  digitalWrite(RELAY3_PIN, HIGH);
  digitalWrite(RELAY4_PIN, HIGH);
  // attempt to connect to Wifi network:
  Serial.print("Connecting to Wifi SSID ");
  Serial.print(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT);  // Add root certificate for api.telegram.org
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.print("\nWiFi connected. IP address: ");
  Serial.println(WiFi.localIP());

  Serial.print("Retrieving time: ");
  configTime(0, 0, "pool.ntp.org");  // get UTC time via NTP
  time_t now = time(nullptr);
  while (now < 24 * 3600) {
    Serial.print(".");
    delay(100);
    now = time(nullptr);
  }
  Serial.println(now);
}

void loop() {
  if (millis() - bot_lasttime > BOT_MTBS) {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while (numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    bot_lasttime = millis();
  }
}
