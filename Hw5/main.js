var app = require('express')();
var http = require('http').Server(app);
var io = require('socket.io')(http);
var port = process.env.PORT || 1337;


var messageId = 0;
var chatName;
var Name = [];
var NameId = 0;
var NameRepeat = false;

app.get ('/', function (req, res) {
	res.sendFile (__dirname + "/Hw5_1.html");
});

app.get ('/change', function (req, res) {
	let name = req.query.name;
	for(let i=0;i<Name.length;i++){
		if(name == Name[i]){
			NameRepeat = true;
		}
	}
	
	if(NameRepeat != true){
		Name[NameId] = name;
		NameId++;
		res.sendFile (__dirname + '/Hw5_2.html');
	} else {
		res.sendFile (__dirname + "/Hw5_1.html");
	}
});

/*
app.listen (3000, function () {
	console.log ('server started on port 1337');
}) ;
*/

//index-chat.js
io.on('connection', function(socket){  // connection is same as connect
	//新增訊息
	socket.on('chat message', function(add_chatName,msg){		
		if(msg != ""){
			io.emit('chat message',add_chatName,msg);
			chatName = add_chatName;
		}
	});
	
	//刪除訊息
	socket.on('delete_message', function(delete_chatName){
		if(delete_chatName == chatName){
			io.emit('delete_message',delete_chatName);
			chatName=null;
		}
	});
	
	//連線訊息
	socket.on('connect_info', function(connect_name){
		io.emit('connect_info',connect_name);
		console.log ("System: '" + connect_name + "' is online.");
		chatName = null;
	});
	
	socket.on('disconnect_info', function(disconnect_name){
		io.emit('disconnect_info',disconnect_name);
		console.log ("System: '" + disconnect_name + "' is offline.");
		chatName = null;
		for(let i=0;i<Name.length;i++){
			if(disconnect_name == Name[i]){
				Name[i] = "";
			}
		}
	});
	
	//連線名稱重複
	socket.on('connect_repeat', function(){
		if(NameRepeat){
			io.emit('connect_repeat',NameRepeat);
			NameRepeat = false;
		}
	});
});

http.listen(port, function(){
	console.log('server started on port:' + port);
});


