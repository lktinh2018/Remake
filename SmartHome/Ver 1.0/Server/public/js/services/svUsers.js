var app = angular.module("app.users");

app.factory("svUsers", ['$http', function($http) {
  
  return {
    create: function(userData) {
      return $http.post("/api/user", userData);
    }
  }
}]);
