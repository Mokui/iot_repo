var W1Temp = require('w1temp');

W1Temp.setGpioPower(13);
W1Temp.setGpioData(6);
W1Temp.getSensorsUids().then(function (sensorsUids) {
	  console.log(sensorsUids);
});

W1Temp.getSensor('28-00000636a3e3').then(function (sensor) {
	  var temp = sensor.getTemperature();
	  console.log('Actual temp:', temp, '°C');
	  sensor.on('change', function (temp) {
		      console.log('Temp changed:', temp, '°C');
		    });

});
