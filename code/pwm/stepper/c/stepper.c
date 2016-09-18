#include <stdio.h>

void disp_err( int err_no )
{
	if( err_no == 0 ) return ;
	
	printf( "ERROR : " );
	switch( err_no )
	{
	case -1 : printf( "DELTA TIME IS LESS THAN OR EQUAL TO ZERO" ); break;
	case -2 : printf( "DELTA DISTANCE IS LESS THAN ZERO"         ); break;
	case -3 : printf( "DELTA TIME IS LESS THAN DELTA DISTANCE"   ); break;
					 
	default : printf( "UNKNOWN" ); break;
	}
	printf( "\n" );
	
}

// dt : delta time
// dd : delta distance
int stepper(int dt, int dd ) {
	
	int err = ( dt > dd ? dt : -dd ) / 2; 
	int e2;
	int lp;

	if ( 0 >= dt ) return -1;
	if ( 0 >  dd ) return -2;
	if ( dt < dd ) return -3;
		
	for(lp =0;lp<dt;lp++){

		printf( "CALL INTERVAL = %02d", lp );
		
		e2 = err;
		if (e2 >-dt) { err -= dd; }
		if (e2 < dd) { err += dt; printf( " Pulse" ); }
		
		printf("\n" );
	}
	  
	  return 0;
}

int test1( int delta_time, int delta_distance )
{
	int ret;
	
	printf( "\n" );
	printf( "delta_time = %d delta_distance = %d\n", delta_time, delta_distance );
	printf( "--------------------------------------\n" );
	ret = stepper(delta_time, delta_distance);
	disp_err( ret );
	printf( "\n" );
}

int main( int argc, char **argv )
{
	
	test1(  0,  0 );
	test1(  1,  0 );
	test1(  1,  1 );
	test1( 10,  0 );
	test1( 10,  1 );
	test1( 10,  3 );
	test1( 10,  5 );
	test1( 10,  9 );
	test1( 10, 10 );
	test1( 10, 11 );
	test1( -1,  3 );
	test1( 10, -3 );
	
}
