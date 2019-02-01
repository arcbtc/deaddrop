#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>


 
const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<body>

<h1>The Welsh Cakes are in the 2nd plant pot to the right as you walk out the main entrance :)</h1>
</body>
</html>
)=====";


 
WebServer server(80);

int counter = 0;

void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page

}

void setup(void){
  Serial.begin(115200);

   
   int numofnet = WiFi.scanNetworks();
   
 while(counter == 0){

   for(int i =0; i < numofnet; i++){
      
      if (WiFi.SSID(i) == "COSTACOSTAWIFI"){
        Serial.println(WiFi.SSID(i));
          
        WiFi.mode(WIFI_AP);
        WiFi.softAP("Welsh Cakes", "drophoundgang");
        Serial.println("Wait 100 ms for AP_START...");
        delay(100);
  
        Serial.println("Set softAPConfig");
        IPAddress Ip(192, 168, 1, 1);
        IPAddress NMask(255, 255, 255, 0);
        WiFi.softAPConfig(Ip, Ip, NMask);
        server.on("/", handleRoot);      //This is display page
 
        server.begin();                  //Start server
        Serial.println("HTTP server started");
        counter++;

      }
      else{
      }

   }
   if (counter == 0){
      esp_sleep_enable_timer_wakeup(10000000);
      esp_deep_sleep_start();
   }
   else{
    }


   }
}

void loop(void){
  if (counter == 120000){
     esp_sleep_enable_timer_wakeup(10000000);
     esp_deep_sleep_start();
  }
  else {
  server.handleClient();
  delay(1);
  counter++;
  }
}
