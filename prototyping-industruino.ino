
#include <Arduino.h>
#include <SPI.h>

#include <ArduinoHttpServer.h>

/* Maximum size of http requests. See also: https://github.com/QuickSander/ArduinoHttpServer */
const size_t HTTP_STREAM_REQUEST_SIZE = 1024;

const int HTTP_PORT = 80;

// -------------------------------------------------------------------------------------------
// -- LCD 
#include <UC1701.h>

static UC1701 lcd;
const int PIN_LCD_BACKLIGHT = 26; 
static const byte glyph_fullbar[] = { B11111111, B11111111, B11111111, B11111111, B11111111 };

// -------------------------------------------------------------------------------------------
// -- Ethernet 

#include <Ethernet2.h>
#include <Dhcp.h>
#include <util.h>
#include <Dns.h>
#include <EthernetClient.h>
#include <EthernetServer.h>

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};

int NETWORK_INFO_DELAY_SECS = 10;

void setup_networking( bool b_lcd = true) {

  digitalWrite(4, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(10, LOW);
  
  if ( b_lcd) {
    lcd.setCursor(0,0); 
    lcd.print("Connecting...");
  }
  
  int r = Ethernet.begin(mac);
  if ( r == 0) {
    if ( b_lcd) {
      lcd.setCursor(0,0); 
      lcd.print("DHCP error, no IP.");  

      lcd.setCursor(0,1); lcd.print("MAC"); 
      for ( int i = 0; i < 6; i++) {
        lcd.setCursor(25+(i*15),1); lcd.print(mac[i],HEX);
        lcd.setCursor(25+(i*15)+10,1); lcd.print(":");
      }
      lcd.setCursor(110,1); lcd.print(" ");
    }
  } else {
    if ( b_lcd) {
      lcd.setCursor(0,0); 
      lcd.clearLine();
  
      lcd.setCursor(0,0); lcd.print("MAC"); 
      for ( int i = 0; i < 6; i++) {
        lcd.setCursor(25+(i*15),0); lcd.print(mac[i],HEX);
        lcd.setCursor(25+(i*15)+10,0); lcd.print(":");
      }
      lcd.setCursor(110,0); lcd.print(" ");
      
      lcd.setCursor(0,1); lcd.print("IP "); 
      lcd.setCursor(25,1); 
      lcd.print(Ethernet.localIP());
  
      lcd.setCursor(0,2); lcd.print("SUB"); 
      lcd.setCursor(25,2);
      lcd.print(Ethernet.subnetMask());
    
      lcd.setCursor(0,3); lcd.print("GW"); 
      lcd.setCursor(25,3);
      lcd.print(Ethernet.gatewayIP());
    
      lcd.setCursor(0,4); lcd.print("DNS"); 
      lcd.setCursor(25,4);
      lcd.print(Ethernet.dnsServerIP());
    }
  }  

  if ( b_lcd) {
    // show a simple progress bar
    for ( int i = 0; i < 25*5; i++) {

      // check ENTER button, if pressed quit info screen
      if ( digitalRead(24) == 0)
        break;

      lcd.setCursor(i, 7);
      lcd.write(0);
      delay((NETWORK_INFO_DELAY_SECS*1000)/(25*5));
    }
  
    lcd.clear();
    // use display otherwise
  }
}

// -------------------------------------------------------------------------------------------
// -- HTTP

EthernetServer server(HTTP_PORT);

void setup_http() {
  server.begin();

  lcd.setCursor(0,0);
  lcd.print("HTTP active...");
}

void http_process_request(EthernetClient& client, ArduinoHttpServer::StreamHttpRequest<HTTP_STREAM_REQUEST_SIZE>& httpRequest) {
  const String & uri = httpRequest.getResource().toString();

  lcd.setCursor(0,1);
  lcd.clearLine();
  switch(httpRequest.getMethod()) {
  case ArduinoHttpServer::MethodGet:
    lcd.print("GET");
    break;
  case ArduinoHttpServer::MethodPut:
    lcd.print("PUT");
    break;
  case ArduinoHttpServer::MethodPost:
    lcd.print("POST");
    break;
  case ArduinoHttpServer::MethodHead:
    lcd.print("HEAD");
    break;
  }
  
  lcd.setCursor(0,2);
  lcd.clearLine();
  lcd.print(uri);
  
  lcd.setCursor(0,3);
  lcd.clearLine();
  const char *b = httpRequest.getBody();
  if ( b && strlen(b) > 0) {
   lcd.print(b);
  }
  
  ArduinoHttpServer::StreamHttpReply httpReply(client, "text/plain");
  httpReply.send("OK");
}

void http_loop() {
  EthernetClient client(server.available());
  if ( client) {
    if ( client.connected()) {
      ArduinoHttpServer::StreamHttpRequest<HTTP_STREAM_REQUEST_SIZE> httpRequest(client);
      
      if (httpRequest.readRequest()) {
        http_process_request(client, httpRequest);
      } else {
        ArduinoHttpServer::StreamHttpErrorReply httpReply(client, httpRequest.getContentType());
        httpReply.send(httpRequest.getErrorDescrition());
      }
      client.stop();
    }
  }
}

// -------------------------------------------------------------------------------------------


void setup() {
  SerialUSB.begin(115200);

  pinMode(24,INPUT);      // Button

  // Ethernet module default chip select setup
  pinMode(4, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(10, OUTPUT);

  lcd.begin();
  analogWrite(PIN_LCD_BACKLIGHT, 255);
  lcd.createChar(0, glyph_fullbar);
  
  lcd.clear();

  setup_networking();

  setup_http();
}

void loop() {
  http_loop();
}

