WiFiServer server(23);
WiFiClient serverClient;

void initTelnet() {
  server.begin();
  server.setNoDelay(true);
}

void handleTelnet() {
  if (server.hasClient()) {
    serverClient = server.available();
  }
  else if (!serverClient && !serverClient.connected())
    serverClient.stop();

  while (serverClient.available()) {
    char clientToken = serverClient.read();

    if (clientToken >= '0' && clientToken <= '9') {      
      uint8_t displayStateIndex = clientToken - '0';
      if (displayStateIndex < nDisplayStates)
        currentDisplayState = displayStates[displayStateIndex];
    }
    else
      switch (clientToken) {
        case 'n':{
          displayStateIndex = (displayStateIndex + 1) % nDisplayStates;
          currentDisplayState = displayStates[displayStateIndex];
        }
        case 'b':
          {
            uint8_t b = serverClient.read() - '0';
            DisplayState::brightness = map(b, 0, 9, 0, 255);            
          }
          break;
        case 'r':
          ESP.reset();
          break;
      }
  }
}


void printDebugMessage(String message) {
  if (serverClient != NULL)
    if (serverClient.connected())
      serverClient.println(message);
}
