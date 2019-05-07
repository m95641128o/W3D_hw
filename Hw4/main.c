#include "GraphicsGems.h"
#include <stdio.h>
#include <stdlib.h>  // for atof
#include <math.h>

boolean Check_Intersect(Box2 *R, Point2 *C, double Rad)
{
	double Rad2;

	Rad2 = Rad * Rad;
	/* Translate coordinates, placing C at the origin. */
	R->max.x -= C->x;  R->max.y -= C->y;
	R->min.x -= C->x;  R->min.y -= C->y;

	if (R->max.x < 0) 			/* R to left of circle center */
		if (R->max.y < 0) 		/* R in lower left corner */
				return ((R->max.x * R->max.x + R->max.y * R->max.y) < Rad2);
		else if (R->min.y > 0) 	/* R in upper left corner */
				return ((R->max.x * R->max.x + R->min.y * R->min.y) < Rad2);
		else 					/* R due West of circle */
				return(ABS(R->max.x) < Rad);
	else if (R->min.x > 0)  	/* R to right of circle center */
		if (R->max.y < 0) 	/* R in lower right corner */
					return ((R->min.x * R->min.x + R->max.y * R->max.y) < Rad2);
		else if (R->min.y > 0)  	/* R in upper right corner */
				return ((R->min.x * R->min.x + R->min.y * R->min.y) < Rad2);
		else 				/* R due East of circle */
				return (R->min.x < Rad);
	else				/* R on circle vertical centerline */
		if (R->max.y < 0) 	/* R due South of circle */
				return (ABS(R->max.y) < Rad);
		else if (R->min.y > 0)  	/* R due North of circle */
				return (R->min.y < Rad);
		else 				/* R contains circle centerpoint */
				return(TRUE);
}

int main(int argc, char *argv[]) {
	int result;
	Box2 R;
	Point2 C;
	
	double cirX = atof (argv[1]);
	double cirY = atof (argv[2]);
	double recX = atof (argv[3]);
	double recY = atof (argv[4]);
	double Rad = atof (argv[5]);
	
	R.max.x = recX+15.0;
	R.max.y = recY+5.0;
	R.min.x = recX-15.0;
	R.min.y = recY-5.0;
	
	C.x = cirX;
	C.y = cirY;
	
	result = Check_Intersect(&R, &C, Rad);
	
	printf("%lf %lf %lf %lf %lf %d \n", cirX,cirY,recX,recY,Rad,result);
	
	exit(0);
}

