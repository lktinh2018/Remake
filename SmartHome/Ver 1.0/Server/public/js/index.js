function addMember() {
  window.open('addmember.ejs', '_self');
}

var app = angular.module("app.auth", []);

app.controller("authController",['$scope', '$window', '$http', 'svAuth', function($scope, $window, $http, svAuth) {

  $scope.login = function() {

    var user = {
      username : $scope.username,
      password : $scope.password
    }

    svAuth.auth(user).then(function (res) {
      if(res.data.success) {
        $window.location.href = "/main.ejs";
      }
      else {
        swal("Fail", "Please check your username and password", "error")
      }
    });
  }

}]);
