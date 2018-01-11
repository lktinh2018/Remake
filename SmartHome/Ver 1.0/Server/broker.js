var mosca = require('mosca');

// var ascoltatore = {
//   type: 'mqtt',
//   json: false,
//   mqtt: require('mqtt'),
//   host: '127.0.0.1',
//   port: 1883
// };

var settings = {
  port: 8883,
  //backend: ascoltatore
};

module.exports = function() {
  var broker = new mosca.Server(settings);

  broker.on('clientConnected', function(client) {
      console.log('Client connected', client.id);
  });

  broker.on('published', function(packet, client) {
    console.log('Published', packet.payload.toString("utf8"));
  });

  broker.on('ready', function() {
    console.log('Mosca server is running on port 8883');
  });
  return broker;
}
