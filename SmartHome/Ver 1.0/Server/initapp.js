module.exports = function() {
  var express = require("express");
  var app = express();
  var bodyParser = require("body-parser");
  var cookieParser = require('cookie-parser');
  app.use("/assets", express.static(__dirname + "/public"));

  app.use(bodyParser.json());
  app.use(bodyParser.urlencoded({ extended: true }));

  app.use(cookieParser());

  app.set("view engine", "ejs");
  return app;
}
