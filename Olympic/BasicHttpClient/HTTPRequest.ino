String HTTPRequest(String url) {
      HTTPClient http;
      USE_SERIAL.print("[HTTP] Begin...\n");
      //Config URL
      //http.begin("https://192.168.1.12/test.html", "7a 9c f4 db 40 d3 62 5a 6e 21 bc 5c cc 66 c8 3e a1 45 59 38");
      http.begin(url);

      USE_SERIAL.print("[HTTP] GET...\n");
      int httpCode = http.GET();
      if(httpCode > 0) {
          USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);

        //File found at server
        if(httpCode == HTTP_CODE_OK) {
            String payload = http.getString();
            return payload;
        }
      } else {
          USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
          return "ERROR";
      }

      http.end();
}

