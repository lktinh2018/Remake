var app = angular.module("app.main");

app.factory("svAssistant", ['$http', function($http) {

  return {
    getRespone: function(command) {
      return $http.get("/api/assistant/" + command);
    }
  }
}]);
