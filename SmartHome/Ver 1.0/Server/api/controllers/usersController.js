var firebase = require("firebase");
var bodyParser = require("body-parser");
var jwt = require("jsonwebtoken");

module.exports = function(app) {

  //Create new user
  app.post("/api/user", function(req, res) {
    var username       = req.body.username
    var userInformation = {
      password        : req.body.password,
      email           : req.body.email,
      phone           : req.body.phone,
      secretquestion  : req.body.secretquestion,
      answerquestion  : req.body.answerquestion,
      mac             : req.body.mac
    };
    firebase.database().ref('/auth/' + req.body.mac).once('value').then(function(snapshot) {
      var auth = snapshot.val();
      if( auth == undefined) {
         res.json({done:false, notification:"Wrong MAC !!!"});
      } else if(auth.activated == false)
          res.json({done:false, notification:"Your device isn't activated !!!"});
        else {
          var updates = {};
          updates[username] = userInformation;
          firebase.database().ref('/users/').update(updates, function(err) {
            if(err)
              res.json({done:false});
            else
              res.json({done:true, notification:"Please try again later !"});
        });
       }
    });
  });

  //Authenticate user
  app.post("/api/auth", function(req, res) {
    var username = req.body.username;
    var password = req.body.password;
    firebase.database().ref('/users/' + username).once('value').then(function(snapshot) {
      var userData = snapshot.val();
      if( userData != undefined && userData.password == password) {

        var token = jwt.sign({
            username: username
        }, 'superSecret', { expiresIn: 60 * 60 });

        res.cookie("token" , token).send({success:true});
      } else {
        res.json({success:false});
      }
    });
  });

}
