var express = require("express");
var app = express();
var jwt = require("jsonwebtoken");
var serverSocket = require("http").Server(app);
var io = require("socket.io")(serverSocket);
var firebase = require("firebase");

module.exports = function(broker) {
  serverSocket.listen(3000, function() {
    console.log("Socket server listen on port", 3000);
  });

  io.on("connection", function(socket) {
    console.log("Some body just connect to server");
    //Get token from cookie
    var cookies = socket.handshake.headers['cookie'];
    var cookieArray = cookies.split(";");
    for(i=0; i<cookieArray.length; i++) {
      if(cookieArray[i].search("token") != -1) {
        var token = cookieArray[i].slice(cookieArray[i].search("token")+6, cookieArray[i].length);
        break;
      }
    }

    //Decoded token and get username
    jwt.verify(token, "superSecret", function(err, decoded) {
      //Get MAC address by username
      firebase.database().ref('/users/' + decoded.username).once('value').then(function(snapshot) {
        var macAddress = snapshot.val().mac;
        //Get status device by MAC address
        firebase.database().ref('/devices/' + macAddress).once('value').then(function(snapshot) {
          var status = snapshot.val().status;
          //Join to room with id=MacAddress
          socket.join(macAddress);
          socket.emit("UPDATE_STATUS", status);
        });
      });
    });

    //CONTROL event
    socket.on("CONTROL", function(data) {
      jwt.verify(data.token, "superSecret", function(err, decoded) {
        if (err)
          return res.json({success: false, message: 'Failed to authenticate token.'});
        else {
          var buffer = "{ \"event\":\"CONTROL\",\"device\":" +  data.device + ", \"value\":" + data.value + "}";
          //Get MAC address by username
          firebase.database().ref('/users/' + decoded.username).once('value').then(function(snapshot) {
            var macAddress = snapshot.val().mac;

            //Write status device to database
            firebase.database().ref('/devices/' + macAddress).once('value').then(function(snapshot) {
              var status = snapshot.val().status;
              status[data.device-1] = !status[data.device-1];
              var updates = {};
              updates["status"] = status;
              firebase.database().ref('/devices/' + macAddress).update(updates);
              io.to(macAddress).emit("UPDATE_STATUS", status);

            });

            //Message content
            var message = {
              topic: macAddress,
              payload: buffer,
              qos: 0, // 0, 1, or 2
              retain: false // or true
            };

            //Publish to client
            broker.publish(message, function() {
              console.log('Publish Successful!');
            });

          });
        }
      });
    });

    //Disconnect event
    socket.on("disconnect", function() {
      console.log("Some body just dissconected");
    });

  });

}
