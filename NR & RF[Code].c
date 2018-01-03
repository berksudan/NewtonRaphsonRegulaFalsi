#include <stdio.h>
double quarticPolynomial(int[], double);
double 	difQuarticPolynomial(int[], double);
double absVal(double);

int main(){
	int i;
	int query;		// Stands for the choice user makes.
	int a[5]; 		// Holds the coefficients of the quartic polynomial.
	int maxIt; 		// Maximum iteration.
	double epsilon; 	// Epsilon value.
	double xLin, xRin;	// Represents the initial xLeft and xRight.
	double xL, yL; 		// Represents the current xLeft and yLeft.
	double xR, yR; 		// Represents the current xRight and yRight.
	double xM, yM; 		// Represents the current xMiddle and yMiddle.
	double xN, yN;		// X and Y points for Newton Raphson Method. 


	printf("Enter the coefficients of quartic polynomial.\n");
	for(i=4;i>=0;i--){
		printf("a%d: ",i);
		scanf("%d",&a[i]);
	}

	printf("Your polynomial is: ");
	for(i=4;i > 0;i--){
			printf("%d*x^%d + ",a[i],i);
	}
	printf("%d\n",	a[0]);

	printf("Enter the epsilon value: ");
	scanf("%lf",&epsilon);
	printf("Enter the maximum iteration: ");
	scanf("%d",&maxIt);

	i=1;
	yM = epsilon + 1; // Default value of epsilon.

	printf("1.\tFind root with Regula Falsi Method.\n");
	printf("2.\tFind root with Newton Raphson Method.\n");
	printf("Enter your choice (1 or 2): ");
	scanf("%d",&query);

	if(query != 1 && query != 2){
		printf("Wrong selection. Exiting now...\n");
		return -1;
	}

	if(query == 1){
		printf("Estimate xLeft and xRight as initial values.\n");
		printf("    (yRight = P(xRight) and yLeft = P(xLeft) signs must be opposite)\n");

		yL = 0;
		yR = 0;

		printf("xLeft: ");
		scanf("%lf",&xL);
		printf("xRight: ");
		scanf("%lf",&xR);

		yL = quarticPolynomial(a,xL);
		yR = quarticPolynomial(a,xR);
		while(yL*yR > 0){
			printf("Please enter the values again: (yL: %lf, yR: %lf)\n",yL,yR);
			printf("xLeft: ");
			scanf("%lf",&xL);
			printf("xRight: ");
			scanf("%lf",&xR);

			yL = quarticPolynomial(a,xL);
			yR = quarticPolynomial(a,xR);
		}
		xLin = xL;
		xRin = xR;

		while( (absVal(yM) > epsilon) && (i <= maxIt) ){
			xM = (xL*yR - xR*yL)/(yR - yL);
			yM = quarticPolynomial(a,xM);
			if( yL*yM < 0){
				xR = xM;
				yR = quarticPolynomial(a,xR);
				yM = yR;		
			}
			else if( yR*yM < 0){
				xL = xM;
				yL = quarticPolynomial(a,xL);
				yM = yL;		
			}
			printf("%d..\txM:%lf\tyM:%lf\txL:%lf\t",i,xM,yM,xL);
			printf("yL:%lf\txR:%lf\tyR:%lf\n",yL,xR,yR);
			i++;
		}
		printf("Regula Falsi Method used successfully.\n");
		if(i == (maxIt+1))
			printf("Program reached the maximum number of iteration.\n");	

		printf("\nRoot is approximately Xi: %lf and f(Xi): %lf between %.2lf and %.2lf \n\n",xM,yM,xLin,xRin);
	}
	else if(query == 2){
			printf("Please enter the x0 value to estimate the root of the polynomial: ");
			scanf("%lf",&xN);
		yN = quarticPolynomial(a,xN);
		while( (absVal(yN)> epsilon) && (i <= maxIt)){
			printf("%d..\txN: %lf\tyN: %lf\n",i,xN,yN);
			xN = xN - ( quarticPolynomial(a,xN)/difQuarticPolynomial(a, xN) );
			yN = quarticPolynomial(a,xN);
			i++;
		}
		printf("\nNewton Raphson Method used successfully.\n");
		if(i == (maxIt+1))
			printf("Program reached the maximum number of iteration.\n");			
		printf("\nComputed root is Xi:%lf and f(Xi): %lf\n\n",xN,yN);

	}

	return 0;
}

double quarticPolynomial(int a[], double x){	// Returns the value of P(x) when x and coefficients are given.
	return ( (a[4]*x*x*x*x) + (a[3]*x*x*x) + (a[2]*x*x) + a[1]*x + a[0] );
}

double difQuarticPolynomial(int a[], double x){	// Returns the value of P'(x) when x and coefficients are given.
	return (4*(a[4]*x*x*x) + (3*a[3]*x*x*x) + (2*a[2]*x) + a[1]);
}

double absVal(double x){
	return (x > 0)? x : -x; 
}
