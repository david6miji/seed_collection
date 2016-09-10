var fs = require('fs');
var os = require('os');

var check_path = os.homedir() + "/gulp-env/";

var isFileExists = function ( path ){

	try {
		fs.accessSync(path, fs.F_OK);
		return true;
	} catch (e) {
//		console.log( e );
		return false;
	}
	return false;
}

if( isFileExists( check_path ) ) {
	console.log( "found ", check_path );
} else {
	console.log( "no found ", check_path );
}

fs.access( check_path, fs.F_OK, function(err) {
    if (!err) {
        console.log( "found ", check_path );
    } else {
        console.log( "no found ", check_path );
    }
});

console.log( 'run end...' );

