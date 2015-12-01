/*
 * Assignment 3, CMPUT 201, FALL 2015
 * 
 * Student Name: Diedre Santos do Carmo
 * Student ID: 1484008
 * 
 * 
 * Code given by assignment page for line intersection
 */

#include "intersec.h"

bool lineIntersection(double Ax, double Ay, double Bx, double By, double Cx, double Cy, double Dx, double Dy, double *X, double *Y) {

	double  distAB, theCos, theSin, newX, ABpos ;

	//  Fail if either line is undefined.
	if (((Ax==Bx) && (Ay==By)) || ((Cx==Dx) && (Cy==Dy))) return NO;

	//  (1) Translate the system so that point A is on the origin.
	Bx -= Ax; 
	By -= Ay;
	Cx -= Ax; 
	Cy -= Ay;
	Dx -= Ax; 
	Dy -= Ay;

	//  Discover the length of segment A-B.
	distAB=sqrt(Bx*Bx+By*By);

	//  (2) Rotate the system so that point B is on the positive X axis.
	theCos = Bx/distAB;
	theSin = By/distAB;
	newX = Cx*theCos+Cy*theSin;
	Cy = Cy*theCos-Cx*theSin; 
	Cx = newX;
	newX = Dx*theCos+Dy*theSin;
	Dy  = Dy*theCos-Dx*theSin; 
	Dx=newX;

	//  Fail if the lines are parallel.
	if (Cy==Dy) return NO;

	//  (3) Discover the position of the intersection point along line A-B.
	ABpos=Dx+(Cx-Dx)*Dy/(Dy-Cy);

	//  (4) Apply the discovered position to line A-B in the original coordinate system.
	*X=Ax+ABpos*theCos;
	*Y=Ay+ABpos*theSin;

	//  Success.
	return YES; 
}

