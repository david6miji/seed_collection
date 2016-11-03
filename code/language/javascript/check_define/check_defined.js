console.log( "when no defined" );
if ( typeof objName === "undefined" )  {
	console.log( "No defined" );
} else {
	console.log( "OK defined" );
}

console.log( "when objName is defined as object " );
var objName = {};
if ( typeof objName === "undefined" )  {
	console.log( "No defined" );
} else {
	console.log( "OK defined" );
}

console.log( "when objName is null" );
objName = null;
if ( typeof objName === "undefined" )  {
	console.log( "No defined" );
} else {
	console.log( "OK defined" );
}

console.log( "when objName is deleted" );
delete objName;
if ( typeof objName === "undefined" )  {
	console.log( "No defined" );
} else {
	console.log( "OK defined" );
}

var objName = {};
console.log( "when property of objName is undefined" );

if ( typeof objName.aaa === "undefined" )  {
	console.log( "No defined" );
} else {
	console.log( "OK defined" );
}

console.log( "when property of objName is defined" );
objName.aaa = {};
if ( typeof objName.aaa === "undefined" )  {
	console.log( "No defined" );
} else {
	console.log( "OK defined" );
}

console.log( "when property of objName is null" );
objName.aaa = null;
if ( typeof objName.aaa === "undefined" )  {
	console.log( "No defined" );
} else {
	console.log( "OK defined" );
}

console.log( "when property of objName is deleted" );
delete objName.aaa;
if ( typeof objName.aaa === "undefined" )  {
	console.log( "No defined" );
} else {
	console.log( "OK defined" );
}

