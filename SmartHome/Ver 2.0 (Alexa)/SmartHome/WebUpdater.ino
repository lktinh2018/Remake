void initWebUpdater() {
  httpUpdater.setup(&httpServer, update_path, update_username, update_password);
  httpServer.begin();
}

void loopWebUpdater() {
  httpServer.handleClient();
}

