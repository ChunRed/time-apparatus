#include <WiFi.h>
#include <SocketIoClient.h>

const char* ssid = "ipta_office";
const char* password = "ipta78802";
const char* host = "192.168.0.126";
const int port = 3000;

int heartbeat = 0;

SocketIoClient socket;

void setup() {
  Serial.begin(115200);

  delay(10);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  socket.on("connect", [](const char* payload, size_t len) {
    Serial.println("Connected to server.");
    socket.emit("esp32_message", "\"hi from esp\"");
    socket.loop();
  });


  socket.on("esp32_message", [](const char* payload, size_t len) {
    heartbeat = atol(payload);
    Serial.println(heartbeat);
  });

  socket.begin(host, port);
}


void loop() {
  socket.loop();
}
