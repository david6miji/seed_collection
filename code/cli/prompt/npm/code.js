var prompt = require("prompt");


prompt.message 		= ">> ";
prompt.delimiter 	= "";
prompt.colors 		= false;

prompt.start();

var field_username = {
				name : 'username',
				description : 'enter user name : ',
				required: true
			};

var field_password = {
				name : 'password',
				description : 'enter password : ',
				required: true,
				hidden: true,
			};
			
prompt.get([field_username, field_password], function (err, result) {
    console.log('Command-line input received:');
    console.log('  username : ' + result.username );
    console.log('  password : ' + result.password );
	prompt.stop();
});

