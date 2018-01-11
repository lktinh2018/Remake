var initFirebase        = require("./config/initFirebase");

var initWebServer       = require("./webserver.js");
var initSocketServer    = require("./socketServer.js");
var initBroker          = require("./broker.js");

var usersController     = require("./api/controllers/usersController");
var assistantController = require("./api/controllers/assistantController");

var initApp = require("./initapp.js");

var app = initApp();

initFirebase();

usersController(app);
assistantController(app);

initWebServer(app);
var broker = initBroker();
initSocketServer(broker);
