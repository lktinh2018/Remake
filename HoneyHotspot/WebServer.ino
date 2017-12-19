void initWebServer() {
  //Set URL 
  server.on("/", handleIndex);
  server.onNotFound([]() {
    server.send(200, "text/html", responseHTML);
  });
  server.begin();
  Serial.println("\nHTTP Server Started");
}

void handleIndex() {
  server.send(200, "text/plain", "Hello World");
}

