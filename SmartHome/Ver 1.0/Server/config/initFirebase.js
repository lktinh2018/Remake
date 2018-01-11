var firebase = require("firebase");

var firebaseConfig = {
  "apiKey": "AIzaSyB65CH4Wft2bZlz5k3j9FXcgTFZQfB99tU",
  "authDomain": "smarthome-21afd.firebaseapp.com",
  "databaseURL": "https://smarthome-21afd.firebaseio.com",
  "projectId": "smarthome-21afd",
  "storageBucket": "smarthome-21afd.appspot.com",
  "messagingSenderId": "577675946039"
}

module.exports = function() {
  firebase.initializeApp(firebaseConfig);
}
