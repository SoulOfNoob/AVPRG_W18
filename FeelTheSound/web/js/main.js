var socket = new WebSocket("ws://localhost:12345");

socket.onopen = function() {
	console.log('socket connected');
	new QWebChannel(socket, function(channel) {
		// make dialog object accessible globally
		transmitter = channel.objects.transmitter;
		transmitter.sendJSON.connect(function(payload) {
				var payload = JSON.parse(payload);
				console.log(payload);
		});
	});
}

socket.onerror = function() {
	console.log('socket Error');
};

socket.onclose = function() {
	console.log('socket Closed');
};

setInterval(function(){
	console.log('send request');
	if (! transmitter ) { return; }
	transmitter.getJSON();
}, 1000);
