#include <WiFi.h> 
#include <WebServer.h>
//#define LOCAL_SSID "Sau Banh "
//#define LOCAL_PASS "0989759499"
#define LOCAL_SSID "Van Tiennn"
#define LOCAL_PASS "nguyenvantienn"

#define BLYNK_TEMPLATE_ID           "TMPL-Fb8IWXf"
#define BLYNK_DEVICE_NAME           "IOT DACS"
#define BLYNK_AUTH_TOKEN            "YDFKqnzLuXLkO3pWcmqafGhAQQ7ZfyU8"
#define BLYNK_PRINT Serial
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Van Tiennn";
char pass[] = "nguyenvantienn";
WidgetLED led1_connect(V0);
WidgetLED led2_connect(V2);
unsigned long times=millis();

#define PIN_LED_27 27     //On board LED
#define PIN_LED_26 26     //On board LED

String LED_27_State = "off";
String LED_26_State = "off";
String header;
WiFiServer server(80);

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;
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
  }else{
    LED_26_State = "on";
  }
  digitalWrite(PIN_LED_26, p); 
}
BLYNK_WRITE(V3){
  Serial.println("v3 connect");
  int p = param.asInt();
  if (p == 0){
    LED_27_State = "off";
  }else{
    LED_27_State = "on";
  }
  digitalWrite(PIN_LED_27, p); 
}

void loop() {
  WiFiClient client = server.available();   
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
  

  //Serial.println("New Client.");         
  String currentLine = "";              
  currentTime = millis();
  previousTime = currentTime;
    while ((client.connected() && currentTime - previousTime <= timeoutTime)) { 
      currentTime = millis();   
     
      if (client.available()) {             
        char c = client.read();             
        Serial.write(c);                 
        header += c;
        if (c == '\n') {                   
          if (currentLine.length() == 0) {
          
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on and off 26
            if (header.indexOf("GET /26/on") >= 0) {
              Serial.println("GPIO 26 on");
              LED_26_State = "on";
              digitalWrite(PIN_LED_26, HIGH);
            } else if (header.indexOf("GET /26/off") >= 0) {
              Serial.println("GPIO 26 off");
              LED_26_State = "off";
              digitalWrite(PIN_LED_26, LOW);
            } 

            // turns the GPIOs on and off 27
            if (header.indexOf("GET /27/on") >= 0) {
              Serial.println("GPIO 27 on");
              LED_27_State = "on";
              digitalWrite(PIN_LED_27, HIGH);
            } else if (header.indexOf("GET /27/off") >= 0) {
              Serial.println("GPIO 27 off");
              LED_27_State = "off";
              digitalWrite(PIN_LED_27, LOW);
            } 
            
            // Display the HTML web page
            client.println("<!DOCTYPE html>");
client.println("<html lang=\"en\">");
client.println("    <head>");
client.println("        <meta charset=\"UTF-8\" />");
client.println("        <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\" />");
client.println("        <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\" />");
client.println("        <link rel=\"stylesheet\" href=\"./style.css\" />");
client.println("        <title>Đồ Án Cơ Sở</title>");
client.println("        <link rel=\"shortcut icon\" href=\"./led.png\" type=\"image/x-icon\" />");
client.println("        <link");
client.println("            href=\"https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/css/bootstrap.min.css\"");
client.println("            rel=\"stylesheet\"");
client.println("            integrity=\"sha384-EVSTQN3/azprG1Anm3QDgpJLIm9Nao0Yz1ztcQTwFspd3yD65VohhpuuCOmLASjC\"");
client.println("            crossorigin=\"anonymous\"");
client.println("        />");
client.println("        <script");
client.println("            src=\"https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/js/bootstrap.bundle.min.js\"");
client.println("            integrity=\"sha384-MrcW6ZMFYlzcLA8Nl+NtUVF0sA7MsXsP1UyJoMp4YLEuNSfAP+JcXn/tWtIaxVXM\"");
client.println("            crossorigin=\"anonymous\"");
client.println("        ></script>");
client.println("        <script");
client.println("            src=\"https://code.jquery.com/jquery-3.6.0.min.js\"");
client.println("            integrity=\"sha256-/xUj+3OJU5yExlq6GSYGSHk7tPXikynS7ogEvDej/m4=\"");
client.println("            crossorigin=\"anonymous\"");
client.println("        ></script>");
client.println("    </head>");
client.println("    <body>");
client.println("        <div id=\"main\">");
client.println("            <!-- đèn trạng thái đang tắt  -->");
client.println("            <div class=\"content-led\" id=\"led1\">");
client.println("                <div class=\"img-led\">");
if (LED_26_State == "off"){
  client.println("                  <div class=\"img\">");
}else{
  client.println("                  <div class=\"img on\">");
}

client.println("                        <img class=\"led\" src=\"https://res.cloudinary.com/vantiennn/image/upload/v1653213936/led_vujitx.png\" alt=\"\" />");
client.println("                    </div>");

if (LED_26_State == "off"){
  client.println("                    <h3 class=\"status-led\">OFF</h3>");
}else{
  client.println("                    <h3 class=\"status-led\">ON</h3>");
}

client.println("                    <h3 class=\"dics\">LED 1</h3>");
client.println("                </div>");
client.println("                <div class=\"body-setting\">");
client.println("                    <div class=\"btn-setting-led\">");
client.println("                        <h3 class=\"btn-title-setting\">Cài đặt hẹn giờ:</h3>");
client.println("                        <button");
client.println("                            class=\"btn\"");
client.println("                            data-bs-target=\"#led1TimeOnModel\"");
client.println("                            data-bs-toggle=\"modal\"");
client.println("                        >");
client.println("                            Hẹn giờ bật");
client.println("                        </button>");
client.println("                        <button");
client.println("                            class=\"btn\"");
client.println("                            data-bs-target=\"#led1TimeOffModel\"");
client.println("                            data-bs-toggle=\"modal\"");
client.println("                        >");
client.println("                            Hẹn giờ tắt");
client.println("                        </button>");
client.println("                    </div>");
client.println("");
client.println("                    <div class=\"body-setting-timer\" id=\"led1Counter\"></div>");
client.println("                </div>");
client.println("            </div>");
client.println("");
client.println("            <!-- đèn trạng thái đang tắt  -->");
client.println("            <div class=\"content-led\" id=\"led2\">");
client.println("                <div class=\"img-led\">");
client.println("                    <div class=\"img\">");
client.println("                        <img class=\"led\" src=\"https://res.cloudinary.com/vantiennn/image/upload/v1653213936/led_vujitx.png\" alt=\"\" />");
client.println("                    </div>");
client.println("                    <h3 class=\"status-led\">OFF</h3>");
client.println("                    <h3 class=\"dics\">LED 2</h3>");
client.println("                </div>");
client.println("                <div class=\"body-setting\">");
client.println("                    <div class=\"btn-setting-led\">");
client.println("                        <h3 class=\"btn-title-setting\">Cài đặt hẹn giờ:</h3>");
client.println("                        <button");
client.println("                            class=\"btn\"");
client.println("                            data-bs-target=\"#led2TimeOnModel\"");
client.println("                            data-bs-toggle=\"modal\"");
client.println("                        >");
client.println("                            Hẹn giờ bật");
client.println("                        </button>");
client.println("                        <button");
client.println("                            class=\"btn\"");
client.println("                            data-bs-target=\"#led2TimeOffModel\"");
client.println("                            data-bs-toggle=\"modal\"");
client.println("                        >");
client.println("                            Hẹn giờ tắt");
client.println("                        </button>");
client.println("                    </div>");
client.println("");
client.println("                    <div class=\"body-setting-timer\" id=\"led2Counter\"></div>");
client.println("                </div>");
client.println("            </div>");
client.println("        </div>");
client.println("");
client.println("        <!-- Modal Off 1-->");
client.println("        <div");
client.println("            class=\"modal fade\"");
client.println("            id=\"led1TimeOffModel\"");
client.println("            data-bs-backdrop=\"static\"");
client.println("            data-bs-keyboard=\"false\"");
client.println("            tabindex=\"-1\"");
client.println("            aria-labelledby=\"led1TimeOffModelLabel\"");
client.println("            aria-hidden=\"true\"");
client.println("        >");
client.println("            <div class=\"modal-dialog\">");
client.println("                <div class=\"modal-content\">");
client.println("                    <div class=\"modal-header\">");
client.println("                        <h5 class=\"modal-title\">Hẹn giờ tắt đèn 1</h5>");
client.println("                        <button");
client.println("                            type=\"button\"");
client.println("                            class=\"btn-close\"");
client.println("                            data-bs-dismiss=\"modal\"");
client.println("                            aria-label=\"Close\"");
client.println("                        ></button>");
client.println("                    </div>");
client.println("                    <div class=\"modal-body\">");
client.println("                        <label>Nhập thời gian tắt: </label>");
client.println("                        <input");
client.println("                            type=\"datetime-local\"");
client.println("                            class=\"ledDateOff\"");
client.println("                            id=\"led1DateOff\"");
client.println("                        />");
client.println("                    </div>");
client.println("                    <div class=\"modal-footer\">");
client.println("                        <button");
client.println("                            type=\"button\"");
client.println("                            class=\"btn btn-secondary ledBtnCloseOff\"");
client.println("                            data-bs-dismiss=\"modal\"");
client.println("                            id=\"led1BtnCloseOff\"");
client.println("                        >");
client.println("                            Close");
client.println("                        </button>");
client.println("                        <button");
client.println("                            type=\"button\"");
client.println("                            id=\"led1BtnSubmitOff\"");
client.println("                            class=\"btn btn-primary ledBtnSubmitOff\"");
client.println("                        >");
client.println("                            Save changes");
client.println("                        </button>");
client.println("                    </div>");
client.println("                </div>");
client.println("            </div>");
client.println("        </div>");
client.println("");
client.println("        <!-- Modal On 1-->");
client.println("        <div");
client.println("            class=\"modal fade\"");
client.println("            id=\"led1TimeOnModel\"");
client.println("            data-bs-backdrop=\"static\"");
client.println("            data-bs-keyboard=\"false\"");
client.println("            tabindex=\"-1\"");
client.println("            aria-labelledby=\"led1TimeOnModelLabel\"");
client.println("            aria-hidden=\"true\"");
client.println("        >");
client.println("            <div class=\"modal-dialog\">");
client.println("                <div class=\"modal-content\">");
client.println("                    <div class=\"modal-header\">");
client.println("                        <h5 class=\"modal-title\">Hẹn giờ bật đèn 1</h5>");
client.println("                        <button");
client.println("                            type=\"button\"");
client.println("                            class=\"btn-close\"");
client.println("                            data-bs-dismiss=\"modal\"");
client.println("                            aria-label=\"Close\"");
client.println("                        ></button>");
client.println("                    </div>");
client.println("                    <div class=\"modal-body\">");
client.println("                        <label>Nhập thời gian tắt: </label>");
client.println("                        <input");
client.println("                            type=\"datetime-local\"");
client.println("                            id=\"led1DateOn\"");
client.println("                            class=\"ledDateOn\"");
client.println("                        />");
client.println("                    </div>");
client.println("                    <div class=\"modal-footer\">");
client.println("                        <button");
client.println("                            type=\"button\"");
client.println("                            class=\"btn btn-secondary ledBtnCloseOn\"");
client.println("                            data-bs-dismiss=\"modal\"");
client.println("                            id=\"led1BtnCloseOn\"");
client.println("                        >");
client.println("                            Close");
client.println("                        </button>");
client.println("                        <button");
client.println("                            type=\"button\"");
client.println("                            id=\"led1BtnSubmitOn\"");
client.println("                            class=\"btn btn-primary ledBtnSubmitOn\"");
client.println("                        >");
client.println("                            Save changes");
client.println("                        </button>");
client.println("                    </div>");
client.println("                </div>");
client.println("            </div>");
client.println("        </div>");
client.println("");
client.println("        <!-- Modal Off 2-->");
client.println("        <div");
client.println("            class=\"modal fade\"");
client.println("            id=\"led2TimeOffModel\"");
client.println("            data-bs-backdrop=\"static\"");
client.println("            data-bs-keyboard=\"false\"");
client.println("            tabindex=\"-2\"");
client.println("            aria-labelledby=\"led2TimeOffModelLabel\"");
client.println("            aria-hidden=\"true\"");
client.println("        >");
client.println("            <div class=\"modal-dialog\">");
client.println("                <div class=\"modal-content\">");
client.println("                    <div class=\"modal-header\">");
client.println("                        <h5 class=\"modal-title\">Hẹn giờ tắt đèn 2</h5>");
client.println("                        <button");
client.println("                            type=\"button\"");
client.println("                            class=\"btn-close\"");
client.println("                            data-bs-dismiss=\"modal\"");
client.println("                            aria-label=\"Close\"");
client.println("                        ></button>");
client.println("                    </div>");
client.println("                    <div class=\"modal-body\">");
client.println("                        <label>Nhập thời gian tắt: </label>");
client.println("                        <input");
client.println("                            type=\"datetime-local\"");
client.println("                            class=\"ledDateOff\"");
client.println("                            id=\"led2DateOff\"");
client.println("                        />");
client.println("                    </div>");
client.println("                    <div class=\"modal-footer\">");
client.println("                        <button");
client.println("                            type=\"button\"");
client.println("                            class=\"btn btn-secondary ledBtnCloseOff\"");
client.println("                            data-bs-dismiss=\"modal\"");
client.println("                            id=\"led2BtnCloseOff\"");
client.println("                        >");
client.println("                            Close");
client.println("                        </button>");
client.println("                        <button");
client.println("                            type=\"button\"");
client.println("                            id=\"led2BtnSubmitOff\"");
client.println("                            class=\"btn btn-primary ledBtnSubmitOff\"");
client.println("                        >");
client.println("                            Save changes");
client.println("                        </button>");
client.println("                    </div>");
client.println("                </div>");
client.println("            </div>");
client.println("        </div>");
client.println("");
client.println("        <!-- Modal On 2-->");
client.println("        <div");
client.println("            class=\"modal fade\"");
client.println("            id=\"led2TimeOnModel\"");
client.println("            data-bs-backdrop=\"static\"");
client.println("            data-bs-keyboard=\"false\"");
client.println("            tabindex=\"-2\"");
client.println("            aria-labelledby=\"led2TimeOnModelLabel\"");
client.println("            aria-hidden=\"true\"");
client.println("        >");
client.println("            <div class=\"modal-dialog\">");
client.println("                <div class=\"modal-content\">");
client.println("                    <div class=\"modal-header\">");
client.println("                        <h5 class=\"modal-title\">Hẹn giờ bật đèn 2</h5>");
client.println("                        <button");
client.println("                            type=\"button\"");
client.println("                            class=\"btn-close\"");
client.println("                            data-bs-dismiss=\"modal\"");
client.println("                            aria-label=\"Close\"");
client.println("                        ></button>");
client.println("                    </div>");
client.println("                    <div class=\"modal-body\">");
client.println("                        <label>Nhập thời gian tắt: </label>");
client.println("                        <input");
client.println("                            type=\"datetime-local\"");
client.println("                            id=\"led2DateOn\"");
client.println("                            class=\"ledDateOn\"");
client.println("                        />");
client.println("                    </div>");
client.println("                    <div class=\"modal-footer\">");
client.println("                        <button");
client.println("                            type=\"button\"");
client.println("                            class=\"btn btn-secondary ledBtnCloseOn\"");
client.println("                            data-bs-dismiss=\"modal\"");
client.println("                            id=\"led2BtnCloseOn\"");
client.println("                        >");
client.println("                            Close");
client.println("                        </button>");
client.println("                        <button");
client.println("                            type=\"button\"");
client.println("                            id=\"led2BtnSubmitOn\"");
client.println("                            class=\"btn btn-primary ledBtnSubmitOn\"");
client.println("                        >");
client.println("                            Save changes");
client.println("                        </button>");
client.println("                    </div>");
client.println("                </div>");
client.println("            </div>");
client.println("        </div>");
client.println("<style>");
    client.println("* {");
client.println("    padding: 0;");
client.println("    margin: 0;");
client.println("    box-sizing: border-box;");
client.println("}");

client.println("html {");
client.println("    font-family: cursive;");
client.println("}");

client.println("body {");
client.println("    height: 100vh;");
client.println("    display: flex;");
client.println("    align-items: center;");
client.println("    justify-content: center;");
client.println("    background-color: #37343a !important;");
client.println("}");


client.println(".content-led {");
client.println("    background-color: rgb(74, 83, 78);");
client.println("    display: flex;");
client.println("    width: 500px;");
client.println("    margin: 10px 0;");
client.println("    border-radius: 15px;");
client.println("    overflow: hidden;");
client.println("    flex-wrap: wrap;");
client.println("}");

client.println(".img-led {");
client.println("    cursor: pointer;");
client.println("    background-color: #444345;");
client.println("    display: flex;");
client.println("    justify-content: center;");
client.println("    align-items: center;");
client.println("    height: 250px;");
client.println("    min-width: 250px;");
client.println("    position: relative;");
client.println("    overflow: hidden;");
client.println("}");

client.println(".on {");
client.println("    filter: drop-shadow(0 0 85px #ffef30) drop-shadow(0 0 25px #ffef30)");
client.println("        drop-shadow(600px 600px 600px #ffef30) drop-shadow(0 0 85px #ffef30);");
client.println("}");

client.println(".led {");
client.println("    width: 200px;");
client.println("}");

client.println(".status-led {");
client.println("    position: absolute;");
client.println("    top: 7px;");
client.println("    right: 10px;");
client.println("}");

client.println(".btn {");
client.println("    margin-top: 25px;");
client.println("    margin-left: 5px;");
client.println("    font-size: 18px;");
client.println("    background-color: #37343a !important;");
client.println("    border: none;");
client.println("    color: #cbcbcf !important;");
client.println("    padding: 10px;");
client.println("    border-radius: 10px;");
client.println("    cursor: pointer;");
client.println("}");

client.println(".btn:hover {");
client.println("    background-color: #ccc;");
client.println("    color: #37343a;");
client.println("}");

client.println(".dics {");
client.println("    position: absolute;");
client.println("    bottom: 6px;");
client.println("    left: 10px;");
client.println("}");

client.println(".body-setting {");
client.println("    display: flex;");
client.println("    flex-direction: column;");
client.println("    border-radius: 50px;");
client.println("}");

client.println(".body-setting-timer {");
client.println("    width: 100%;");
client.println("    height: 100px;");
client.println("    background-color: #ccc;");
client.println("    margin-left: 7px;");
client.println("    margin-top: 35px;");
client.println("    border: 3px solid #000;");
client.println("    border-radius: 5px;");
client.println("    overflow: auto;");
client.println("}");

client.println(".btn-title-setting {");
client.println("    margin-left: 10px;");
client.println("    font-size: 25px;");
client.println("}");

client.println(".content-setting {");
client.println("    display: flex;");
client.println("    height: 30px;");
client.println("    width: 100%;");
client.println("}");

client.println(".title-setting {");
client.println("    line-height: 30px;");
client.println("    font-size: 16px;");
client.println("    margin-left: 5px;");
client.println("}");

client.println(".countdown {");
client.println("    line-height: 30px;");

client.println("}");

client.println("@media (max-width: 46.1875em) {");
client.println("    .content-led {");
client.println("        display: block;");
client.println("        height: 350px;");
client.println("        width: 300px;");
client.println("    }");

client.println("    .img-led {");
client.println("        height: 150px;");
client.println("        min-width: 150px;");
client.println("    }");

client.println("    .on {");
client.println("        filter: drop-shadow(0 0 10px #ffef30) drop-shadow(0 0 14px #ffef30)");
client.println("            drop-shadow(75px 75px 75px #ffef30) drop-shadow(0 0 25px #ffef30);");
client.println("    }");

client.println("    .btn-title-setting {");
client.println("        text-align: center;");
client.println("    }");

client.println("    .btn {");
client.println("        margin-top: 10px;");
client.println("    }");

client.println("    .led {");
client.println("        width: 150px;");
client.println("    }");

client.println("    .body-setting-timer {");
client.println("        width: 280px;");
client.println("        height: 100px;");
client.println("        margin: 8px auto;");
client.println("    }");

client.println("    .btn-setting-led {");
client.println("        text-align: center;");
client.println("    }");

client.println("    .title-setting {");
client.println("        margin-left: 30px;");
client.println("        margin-right: 8px;");
client.println("    }");
client.println("}");

client.println("</style>");
client.println("<script>");
client.println("window.addEventListener(\"DOMContentLoaded\", () => {");
client.println("    const led1Port = 26;");
client.println("    const led2Port = 27;");
client.println("    function ajaxTurnOn(port) {");
client.println("    console.log(`/${port}/on`)");
client.println("        $.ajax({");
client.println("            url: `/${port}/on`,");
client.println("            method: \"GET\",");
client.println("        });");
client.println("    }");
client.println("    function ajaxTurnOff(port) {");
client.println("    console.log(`/${port}/off`)");
client.println("        $.ajax({");
client.println("            url: `/${port}/off`,");
client.println("            method: \"GET\",");
client.println("        });");
client.println("    }");

client.println("    function convertTimestampToCustom(time) {");
client.println("        const result = {");
client.println("            days: 0,");
client.println("            hours: 0,");
client.println("            minutes: 0,");
client.println("            seconds: 0,");
client.println("        };");

client.println("        result.days = Math.floor(time / (1000 * 60 * 60 * 24));");
client.println("        result.hours = Math.floor((time / (1000 * 60 * 60)) % 24);");
client.println("        result.minutes = Math.floor((time / (1000 * 60)) % 60);");
client.println("        result.seconds = Math.floor((time / 1000) % 60);");
client.println("        var string = \"\";");
client.println("        if (result.days > 0) string += result.days + \"d \";");
client.println("        if (result.hours > 0) string += result.hours + \"h \";");
client.println("        if (result.minutes > 0) string += result.minutes + \"m \";");
client.println("        if (result.seconds >= 0) string += result.seconds + \"s \";");

client.println("        return string;");
client.println("    }");
client.println("    function itemCounter(id, type, timestamp, timeOut, timeInterval) {");
client.println("        console.log(timeOut, timeInterval);");
client.println("        return `");
client.println("            <div class=\"content-setting\" id=\"${id}\" data-id=\"${id}\" data-timeout=\"${timeOut}\" data-timeinterval=\"${timeInterval}\">");
client.println("                <h3 class=\"title-setting\">${type}:</h3>");
client.println("                <p class=\"countdown timmer\">${convertTimestampToCustom(");
client.println("                    timestamp");
client.println("                )}</p>");
client.println("                <span class=\"cancel-timmer\" style=\"    display: block;");
client.println("                margin: auto 0;");
client.println("                margin-left: auto;");
client.println("                margin-right: 8px;");
client.println("                font-size: 18px;");
client.println("                cursor: pointer;\">X</span>");
client.println("            </div>`;");
client.println("    }");

client.println("    function handleCancelTimmer(counterContainer, timeout, timeInterval) {");
client.println("        const couterContainerEle = document.querySelector(counterContainer);");

client.println("        couterContainerEle.querySelector(\".cancel-timmer\").onclick =");
client.println("            function () {");
client.println("                this.parentElement.remove();");
client.println("                clearTimeout(timeout);");
client.println("                clearInterval(timeInterval);");
client.println("            };");
client.println("    }");

client.println("    function handleCancelAllTimmer() {");
client.println("        const counterContainerEle = document.querySelectorAll(\".cancel-timmer\");");
client.println("        for (let i = 0; i < counterContainerEle.length; i++) {");
client.println("            const counterItemEle = counterContainerEle[i];");
client.println("            counterItemEle.onclick = function () {");
client.println("                const parentEle = this.parentElement;");
client.println("                const timeOut = parentEle.getAttribute(\"data-timeout\");");
client.println("                const timeInterval =");
client.println("                    parentEle.getAttribute(\"data-timeinterval\");");
client.println("                clearTimeout(timeOut);");
client.println("                clearInterval(timeInterval);");
client.println("                parentEle.remove();");
client.println("            };");
client.println("        }");
client.println("    }");

client.println("    function handleToggleLed(parent, port) {");
client.println("        const toggleEle = document.querySelector(parent);");
client.println("        const imageEle = toggleEle.querySelector(\".img\");");
client.println("        const statusEle = toggleEle.querySelector(\".status-led\");");
client.println("        console.log({ toggle1Ele, imageEle, statusEle });");
client.println("        imageEle.classList.toggle(\"on\");");
client.println("        if (statusEle.textContent === \"ON\") {");
client.println("            statusEle.textContent = \"OFF\";");
client.println("            ajaxTurnOff(port);");
client.println("        } else {");
client.println("            statusEle.textContent = \"ON\";");
client.println("            ajaxTurnOn(port);");
client.println("        }");
client.println("    }");

client.println("    function handleTurnOffLed(parent, port) {");
client.println("        const toggleEle = document.querySelector(parent);");
client.println("        const imageEle = toggleEle.querySelector(\".img\");");
client.println("        const statusEle = toggleEle.querySelector(\".status-led\");");
client.println("        console.log({ toggle1Ele, imageEle, statusEle });");
client.println("        imageEle.classList.remove(\"on\");");
client.println("        statusEle.textContent = \"OFF\";");
client.println("        ajaxTurnOff(port);");
client.println("    }");
client.println("    function handleTurnOnLed(parent, port) {");
client.println("        const toggleEle = document.querySelector(parent);");
client.println("        const imageEle = toggleEle.querySelector(\".img\");");
client.println("        const statusEle = toggleEle.querySelector(\".status-led\");");
client.println("        console.log({ toggle1Ele, imageEle, statusEle });");
client.println("        imageEle.classList.add(\"on\");");
client.println("        statusEle.textContent = \"ON\";");
client.println("        ajaxTurnOn(port);");
client.println("    }");

client.println("    function handleModelOffClick(parent, modelParent, counterParent, port) {");
client.println("        const modelOff = document.querySelector(modelParent);");
client.println("        const dateOff = modelOff.querySelector(\".ledDateOff\");");
client.println("        const btnCloseOff = modelOff.querySelector(\".ledBtnCloseOff\");");
client.println("        const counter = document.querySelector(counterParent);");
client.println("        console.log({ modelOff, dateOff, btnCloseOff, counter });");
client.println("        const now = new Date();");
client.println("        if (!dateOff.value) {");
client.println("            alert(\"Bạn chưa chọn thời gian hẹn giờ.\");");
client.println("            return;");
client.println("        }");

client.println("        const timer = new Date(dateOff.value);");
client.println("        const timestamp = timer - now;");
client.println("        if (timestamp <= 0) {");
client.println("            alert(\"Bạn cần đặt thời gian lớn hơn hiện tại\");");
client.println("            return;");
client.println("        }");

client.println("        var tempTime = setTimeout(function () {");
client.println("            btnCloseOff.click();");
client.println("            var timeout = setTimeout(function (e) {");
client.println("                handleTurnOffLed(parent, port);");
client.println("                document.querySelector(\"#timer-\" + timeout).remove();");
client.println("                clearInterval(timeInterval);");
client.println("            }, timestamp);");

client.println("            const timeInterval = setInterval(function () {");
client.println("                newTimeStamp -= 1000;");
client.println("                const timerContainerEle = document.querySelector(");
client.println("                    \"#timer-\" + timeout");
client.println("                );");
client.println("                timerContainerEle.querySelector(\".timmer\").textContent =");
client.println("                    convertTimestampToCustom(newTimeStamp);");
client.println("            }, 1000);");
client.println("            var newTimeStamp = timestamp;");
client.println("            counter.innerHTML =");
client.println("                counter.innerHTML +");
client.println("                itemCounter(");
client.println("                    \"timer-\" + timeout,");
client.println("                    \"Tắt sau\",");
client.println("                    newTimeStamp,");
client.println("                    timeout,");
client.println("                    timeInterval");
client.println("                );");
client.println("            handleCancelAllTimmer();");
client.println("        }, timestamp % 1000);");
client.println("    }");
client.println("    function handleModelOnClick(parent, modelParent, counterParent, port) {");
client.println("        const modelOn = document.querySelector(modelParent);");
client.println("        const dateOn = modelOn.querySelector(\".ledDateOn\");");
client.println("        const btnCloseOn = modelOn.querySelector(\".ledBtnCloseOn\");");
client.println("        const counter = document.querySelector(counterParent);");
client.println("        console.log({ modelOn, dateOn, btnCloseOn, counter });");
client.println("        const now = new Date();");
client.println("        if (!dateOn.value) {");
client.println("            alert(\"Bạn chưa chọn thời gian hẹn giờ.\");");
client.println("            return;");
client.println("        }");

client.println("        const timer = new Date(dateOn.value);");
client.println("        const timestamp = timer - now;");
client.println("        if (timestamp <= 0) {");
client.println("            alert(\"Bạn cần đặt thời gian lớn hơn hiện tại\");");
client.println("            return;");
client.println("        }");

client.println("        var tempTime = setTimeout(function () {");
client.println("            btnCloseOn.click();");
client.println("            var timeout = setTimeout(function (e) {");
client.println("                handleTurnOnLed(parent, port);");
client.println("                document.querySelector(\"#timer-\" + timeout).remove();");
client.println("                clearInterval(timeInterval);");
client.println("            }, timestamp);");

client.println("            var newTimeStamp = timestamp;");

client.println("            const timeInterval = setInterval(function () {");
client.println("                newTimeStamp -= 1000;");
client.println("                const timerContainerEle = document.querySelector(");
client.println("                    \"#timer-\" + timeout");
client.println("                );");
client.println("                timerContainerEle.querySelector(\".timmer\").textContent =");
client.println("                    convertTimestampToCustom(newTimeStamp);");
client.println("            }, 1000);");
client.println("            counter.innerHTML =");
client.println("                counter.innerHTML +");
client.println("                itemCounter(");
client.println("                    \"timer-\" + timeout,");
client.println("                    \"Bật sau\",");
client.println("                    newTimeStamp,");
client.println("                    timeout,");
client.println("                    timeInterval");
client.println("                );");
client.println("            handleCancelAllTimmer();");
client.println("        }, timestamp % 1000);");
client.println("    }");
client.println("    const light1Ele = document.querySelector(\"#led1\");");
client.println("    const toggle1Ele = light1Ele.querySelector(\".img-led\");");
client.println("    const btnSubmit1Off = document.querySelector(\"#led1BtnSubmitOff\");");
client.println("    const btnSubmit1On = document.querySelector(\"#led1BtnSubmitOn\");");
client.println("    toggle1Ele.onclick = function () {");
client.println("        handleToggleLed(\"#led1\", led1Port);");
client.println("    };");
client.println("    btnSubmit1Off.onclick = function () {");
client.println("        handleModelOffClick(");
client.println("            \"#led1\",");
client.println("            \"#led1TimeOffModel\",");
client.println("            \"#led1Counter\",");
client.println("            led1Port");
client.println("        );");
client.println("    };");
client.println("    btnSubmit1On.onclick = function () {");
client.println("        handleModelOnClick(");
client.println("            \"#led1\",");
client.println("            \"#led1TimeOnModel\",");
client.println("            \"#led1Counter\",");
client.println("            led1Port");
client.println("        );");
client.println("    };");

client.println("    const light2Ele = document.querySelector(\"#led2\");");
client.println("    const toggle2Ele = light2Ele.querySelector(\".img-led\");");
client.println("    const btnSubmit2Off = document.querySelector(\"#led2BtnSubmitOff\");");
client.println("    const btnSubmit2On = document.querySelector(\"#led2BtnSubmitOn\");");
client.println("    toggle2Ele.onclick = function () {");
client.println("        handleToggleLed(\"#led2\", led2Port);");
client.println("    };");
client.println("    btnSubmit2Off.onclick = function () {");
client.println("        handleModelOffClick(");
client.println("            \"#led2\",");
client.println("            \"#led2TimeOffModel\",");
client.println("            \"#led2Counter\",");
client.println("            led2Port");
client.println("        );");
client.println("    };");
client.println("    btnSubmit2On.onclick = function () {");
client.println("        handleModelOnClick(");
client.println("            \"#led2\",");
client.println("            \"#led2TimeOnModel\",");
client.println("            \"#led2Counter\",");
client.println("            led2Port");
client.println("        );");
client.println("    };");
client.println("});");
client.println("</script>");

client.println("    </body>");
client.println("    <script src=\"./script.js\"></script>");
client.println("</html>");


            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    //Serial.println("Client disconnected.");
    //Serial.println("");
}
