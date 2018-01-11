var app = angular.module("app.auth");

app.factory("svAuth", ['$http', function($http) {

  return {
    auth: function(userData) {
      return $http.post("/api/auth", userData);
    }
  }
}]);
