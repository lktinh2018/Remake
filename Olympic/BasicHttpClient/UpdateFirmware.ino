boolean checkCurrentFirmware(String newFirmware) {
  String currentVersion = "";
  String currentPatch   = "";
  String currentMinor   = "";
  
  int index1, index2, index3;
  //Current Version
  index1 = currentFirmware.indexOf('.');
  currentVersion = currentFirmware.substring(0, index1);
  //Current Patch
  index2 = currentFirmware.indexOf('.', index1+1);
  currentPatch = currentFirmware.substring(index1+1, index2);
  //Current Minor
  index3 = currentFirmware.indexOf('.', index2+1);
  currentMinor = currentFirmware.substring(index2+1, index3);

  String newVersion, newPatch, newMinor;
  //New Version
  index1 = newFirmware.indexOf('.');
  newVersion = newFirmware.substring(0, index1);
  //New Patch
  index2 = newFirmware.indexOf('.', index1+1);
  newPatch = newFirmware.substring(index1+1, index2);
  //New Minor
  index3 = newFirmware.indexOf('.', index2+1);
  newMinor = newFirmware.substring(index2+1, index3);

  if(newVersion.toInt() > currentVersion.toInt()) {
    return true;
  }
  else {
    if(newPatch.toInt() > currentPatch.toInt()) {
      return true;
    }
    else {
      if(newMinor.toInt() > currentMinor.toInt()) {
        return true;
      }
      else {
        return false;
      }
    }
  }   
}

void updateFirmware() {
  t_httpUpdate_return ret = ESPhttpUpdate.update("http://192.168.60.180/firmware.bin");
  //t_httpUpdate_return  ret = ESPhttpUpdate.update("https://server/file.bin");

  switch(ret) {
      case HTTP_UPDATE_FAILED:
          USE_SERIAL.printf("HTTP_UPDATE_FAILD Error (%d): %s", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
          break;
  
      case HTTP_UPDATE_NO_UPDATES:
          USE_SERIAL.println("HTTP_UPDATE_NO_UPDATES");
          break;
  
      case HTTP_UPDATE_OK:
          USE_SERIAL.println("HTTP_UPDATE_OK");
          break;
  }
}

