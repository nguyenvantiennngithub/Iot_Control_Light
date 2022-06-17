#include <WiFi.h>
#include <WebServer.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "Web.h"
//#define LOCAL_SSID "Sau Banh "
//#define LOCAL_PASS "0989759499"

//#define LOCAL_SSID "Van Tiennn"
//#define LOCAL_PASS "nguyenvantienn"

#define LOCAL_SSID "saubanh"
#define LOCAL_PASS "tu1den20"

//char ssid[] = "Van Tiennn";
//char pass[] = "nguyenvantienn";

char ssid[] = "saubanh";
char pass[] = "tu1den20";

#define BLYNK_TEMPLATE_ID           "TMPL-Fb8IWXf"
#define BLYNK_DEVICE_NAME           "IOT DACS"
#define BLYNK_AUTH_TOKEN            "YDFKqnzLuXLkO3pWcmqafGhAQQ7ZfyU8"
#define BLYNK_PRINT Serial
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
char auth[] = BLYNK_AUTH_TOKEN;
WidgetLED led1_connect(V0);
WidgetLED led2_connect(V2);
unsigned long times=millis();

#define PIN_LED_27 27     //On board LED
#define PIN_LED_26 26     //On board LED

String LED_27_State = "off";
String LED_26_State = "off";
String header;

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

void notifyClients(String message) {
  ws.textAll(String(message));
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    data[len] = 0;
    if (strcmp((char*)data, "/26/on") == 0) {
      Serial.println("GPIO 26 on");
      LED_26_State = "on";
      digitalWrite(PIN_LED_26, HIGH);
      notifyClients("/26/on");
    }
    if (strcmp((char*)data, "/26/off") == 0) {
      Serial.println("GPIO 26 off");
      LED_26_State = "off";
      digitalWrite(PIN_LED_26, LOW);
      notifyClients("/26/off");
    }

    if (strcmp((char*)data, "/27/on") == 0) {
      Serial.println("GPIO 27 on");
      LED_27_State = "on";
      digitalWrite(PIN_LED_27, HIGH);
      notifyClients("/27/on");
    }
    if (strcmp((char*)data, "/27/off") == 0) {
      Serial.println("GPIO 27 off");
      LED_27_State = "off";
      digitalWrite(PIN_LED_27, LOW);
      notifyClients("/27/off");
    }
  }
}
void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      break;
    case WS_EVT_DATA:
      Serial.printf("handleWebSocketMessage #%u\n", client->id());
      handleWebSocketMessage(arg, data, len);
      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
  }
}

void initWebSocket() {
  ws.onEvent(onEvent);
  server.addHandler(&ws);
}

String processor(const String& var){
  Serial.println(var);
  return "ON";
}
void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  Serial.println("hello");
  delay(100);
  pinMode(PIN_LED_27, OUTPUT);
  pinMode(PIN_LED_26, OUTPUT);
  
  digitalWrite(PIN_LED_27, LOW);
  digitalWrite(PIN_LED_26, LOW);
 
  Serial.println("connected");
  WiFi.begin(LOCAL_SSID, LOCAL_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("IP Wifi address: "); Serial.println(WiFi.localIP());


  initWebSocket();
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", PAGE_MAIN, processor);
  });
 
  server.begin();
}
BLYNK_CONNECTED() {
  // Request the latest state from the server
  Blynk.syncVirtual(V1,V3);
}
BLYNK_WRITE(V1){
  Serial.println("v1 connect");
  int p = param.asInt();
  if (p == 0){
    LED_26_State = "off";
    Serial.println("/26/off");
    notifyClients("/26/off");
  }else{
    LED_26_State = "on";
    Serial.println("/26/on");
    notifyClients("/26/on");
  }
  digitalWrite(PIN_LED_26, p); 
}
BLYNK_WRITE(V3){
  Serial.println("v3 connect");
  int p = param.asInt();
  if (p == 0){
    LED_27_State = "off";
    Serial.println("/27/off");
    notifyClients("/27/off");
  }else{
    LED_27_State = "on";
    Serial.println("/27/on");
    notifyClients("/27/on");
  }

  digitalWrite(PIN_LED_27, p); 
}

void loop() {
  ws.cleanupClients();
  Blynk.run();
  if(millis()-times>1000){
    if (led1_connect.getValue()){
      led1_connect.off();
    }else {
      led1_connect.on();
    }
    if (led2_connect.getValue()){
      led2_connect.off();
    }else {
      led2_connect.on();
    }
    times=millis();
  }
 
}
