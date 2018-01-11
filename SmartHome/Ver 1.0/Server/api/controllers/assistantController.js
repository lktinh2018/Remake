var firebase = require("firebase");
module.exports = function(app) {
  //Authenticate user
  app.get("/api/assistant/:command", function(req, res) {
    var command = req.params.command;
    firebase.database().ref('/assistant/' + command).once('value').then(function(snapshot) {
      var assistant = snapshot.val();
      if( assistant == undefined) {
        res.json({done: false, respone:"I don't know"});
      } else {
        res.json({done: true, respone:assistant.respone});
      }
    });
  });

}
