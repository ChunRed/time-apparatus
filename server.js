var app = require('express')();
var http = require('http').Server(app);
var io = require('socket.io')(http);

var userId = 0;


io.on('connection', function (socket) {
    socket.userId = userId++;
    console.log('a user connected, user id: ' + socket.userId);

    socket.on('esp32_message', function (msg) {
        console.log('message from user#' + socket.userId + ": " + msg);
    });

    socket.on('web_message', function (msg) {
        console.log(msg);
        io.emit("esp32_message", msg);
    });
});



http.listen(3000, function () {
    console.log('listening on *:3000');
});


// setInterval(function () {
//     io.emit("esp32_message", 12345);
// }, 1000);

