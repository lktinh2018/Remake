void initDNSServer() {
  dnsServer.start(53, "*", apIP);
}

