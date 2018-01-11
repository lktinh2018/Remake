// alert(screen.width);
// alert(screen.height);

var app = angular.module("app.main", ['ngCookies']);

app.controller('mainController', ['$scope','$timeout', '$cookies', 'svAssistant', function($scope, $timeout, $cookies, svAssistant) {

  var socketServer = "192.168.1.193:3000";
  var socket = io(socketServer);

  socket.on("UPDATE_STATUS", function(data) {
    console.log(data);
  });


  $scope.loading = false;
  $scope.processControl = function(event, val) {
    var device = event.target.id[3];
    var token = $cookies.get('token');
    socket.emit("CONTROL", {"device": device, "value": val,  "token": token });
  };


  //Text to speech function
  function speak(text, callback) {
    var u = new SpeechSynthesisUtterance();
    u.text    = text;
    u.lang    = 'en-US';
    u.volume  = 1;
    u.rate    = 1;
    u.onend = function () {
        if (callback) {
            callback();
        }
    };
    u.onerror = function (e) {
        if (callback) {
            callback(e);
        }
    };
    speechSynthesis.speak(u);
  }


  //Init recognition
  if (window.hasOwnProperty('webkitSpeechRecognition')) {
    var recognition = new webkitSpeechRecognition();
    recognition.continuous = false
    recognition.interimResults = false;
    recognition.lang = 'en-us';

    recognition.onresult = function(e) {
      var res = e.results[0][0].transcript;
      recognition.stop();
      processRecognition(res);
    };

    recognition.onend = function() {
      if($scope.activatedVoice)
        recognition.start();
    }

    recognition.onerror = function(e) {
      recognition.stop();
    }
  }


  //Function for process data recognition
  function processRecognition(data) {
    svAssistant.getRespone(data).then(function(res) {
      if(res.data.done) {
        speak(res.data.respone);
      }
      var token = $cookies.get('token');
      if(data.localeCompare("turn on the light") == 0) {
        $scope.btnval2 = true;
        socket.emit("CONTROL", {"device": 2, "value": true,  "token": token });
      }
      else if(data.localeCompare("turn off the light") == 0) {
        $scope.btnval2 = false;
        socket.emit("CONTROL", {"device": 2, "value": false,  "token": token });
      }

    });
  }

  $scope.activatedVoice = false;
  $scope.voiceClass = 'fa fa-microphone-slash';
  $scope.voice = function() {
    if (window.hasOwnProperty('webkitSpeechRecognition')) {
      if($scope.activatedVoice) {
        $scope.voiceClass = 'fa fa-microphone-slash';
        $scope.activatedVoice = false;
        recognition.stop();
        $scope.loading = false;
        speak("Voice isn't activated !");
      } else {
        $scope.voiceClass = 'fa fa-microphone';
        $scope.activatedVoice = true;
        $timeout( function() {
          recognition.start();
          $scope.loading = true;
        }, 1000);
        speak("Voice's activated !");
      }
    } else {
      swal("Fail!", "Your browser doesn't support voice recognition", "error");
    }
  };

  //Function close or open sidebar
  $scope.openedSideBar = true;
  $scope.btnSideBarClass = "icon-arrow-left";
  $scope.sideBar = function() {
    if($scope.openedSideBar) {
      document.getElementsByClassName("nav").style.width = "0";
      document.getElementsByClassName("article").style.marginLeft = "0%";
      document.getElementsByClassName("article").style.width = "100%";
      $scope.btnSideBarClass = "icon-arrow-right";
      $scope.openedSideBar = false;
    } else {
      document.getElementsByClassName("article").style.marginLeft = "180px";
      document.getElementsByClassName("nav").style.width = "170px";
      document.getElementsByClassName("nav").style.display = "block";
      document.getElementsByClassName("article").style.width = "85%";
      $scope.btnSideBarClass = "icon-arrow-left";
      $scope.openedSideBar = true;
    }
  }
}]);
