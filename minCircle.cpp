#include "minCircle.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <assert.h> 
#include "anomaly_detection_util.h"

using namespace std;


float distance(const Point& a, const Point& b){ 
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2)); 
}

bool PointInCircle(const Circle& c, const Point& p){ 
    //if the distance between center and point greater then the raduis, the p is outside
    return distance(c.center, p) <= c.radius; 
} 

Point getCenter(float ax, float ay, float bx, float by){ 
    //by the circumCircle equation:
    float A = (ax * ax) + (ay * ay); 
    float B = (bx * bx) + (by * by); 
    float C = (ax * by) - (ay * bx); 
    float X = ((by * A) - (ay * B)) / (2*C);
    float Y = ((ax * B) - (bx * A)) / (2*C);
    return Point(X,Y);
} 

Circle CircleBy2Points(const Point& A, const Point& B){
    // Set the center to be the midpoint of A and B 
    Point C = { (A.x + B.x) / 2, (A.y + B.y) / 2 }; 
    // Set the radius to be half the distance AB 
    float raduis =  distance(A, B) / 2;
    return Circle(C, raduis);
}

Circle CircleBy3Points(const Point& A, const Point& B,const Point& C){ 
    // get center by the circumcenter equation (method)
    Point Center = getCenter(B.x - A.x, B.y - A.y, C.x - A.x, C.y - A.y); 
    Center.x += A.x; 
    Center.y += A.y; 
    float radius = distance(Center, A);
    return Circle(Center, radius);
    
    //Eli's equations:
	// Point mAB((A.x+B.x)/2 , (A.y+B.y)/2); // mid point of line AB
	// float slopAB = (B.y - A.y) / (B.x - A.x); // the slop of AB
	// float pSlopAB = - 1/slopAB; // the perpendicular slop of AB
	// Point mBC((B.x+C.x)/2 , (B.y+C.y)/2); // mid point of line BC
	// float slopBC = (C.y - B.y) / (C.x - B.x); // the slop of BC
	// float pSlopBC = - 1/slopBC; // the perpendicular slop of BC
	// float x = (- pSlopBC*mBC.x + mBC.y + pSlopAB*mAB.x - mAB.y) / (pSlopAB - pSlopBC);
	// float y = pSlopAB * (x - mAB.x) + mAB.y;
	// Point center(x,y);
	// float R=distance(center,A);
	// return Circle(center,R);
} 

bool CircleCheck(const Circle& c, const vector<Point>& Bdr){ 
    for (const Point& p : Bdr) 
        if (!PointInCircle(c, p)){
            return false; 
        }
        return true; 
}

Circle trivialCircle(vector<Point>& Bdr){ 
    if (Bdr.empty()) { 
        return Circle(Point(0,0),0); 
    }else if (Bdr.size() == 1) { 
        //return Circle(Point(Bdr[0].x,Bdr[0].y),0); 
        return Circle(Bdr[0],0);
    }else if (Bdr.size() == 2) { 
        return CircleBy2Points(Bdr[0], Bdr[1]); 
    }

    //check if the smallest circle determined by 2 points
    for (int i = 0; i < 3; i++) { 
        for (int j = i + 1; j < 3; j++) { 
            Circle c = CircleBy2Points(Bdr[i], Bdr[j]); 
            if (CircleCheck(c, Bdr)){
                return c;
            }
        }
    }
    //check if the smallest circle determined by 2 points, Eli's way
    // Circle c = CircleBy2Points(Bdr[0],Bdr[1]);
	// if(distance(Bdr[2],c.center)<=c.radius)
	// 	return c;
	// c=CircleBy2Points(Bdr[0],Bdr[2]);
	// if(distance(Bdr[1],c.center)<=c.radius)
	// 	return c;
	// c=CircleBy2Points(Bdr[1],Bdr[2]);
	// if(distance(Bdr[0],c.center)<=c.radius)
	// 	return c;
    //else, return the circumCenter of 3 points
    return CircleBy3Points(Bdr[0], Bdr[1], Bdr[2]); 
}

Circle welzlAlg(Point** p, vector<Point> Bdr, int n){ 
    // Base case when all points processed or Bdr vector size is 3 
    if (n == 0 || Bdr.size() == 3) { 
        return trivialCircle(Bdr); 
    } 
    // a random point from the array
     int idx = rand() % n;
    Point randomP(p[idx]->x,p[idx]->y);
    swap(p[idx], p[n - 1]);
    // set of points by dicrease point p from the P array -  P - {p} 
    Circle d = welzlAlg(p, Bdr, n - 1); 
    if (PointInCircle(d, randomP)){ 
        return d; 
    } 
    // Otherwise, must be on the boundary of the minimum enclosing circle 
    Bdr.push_back(randomP); 
    // Return the minimum circle for P - {p} and R U {p} 
    return welzlAlg(p, Bdr, n - 1); 
}

Circle findMinCircle(Point** points,size_t size){
    vector<Point> Boundery = {};//vector for the boundery points
    return welzlAlg(points, Boundery, size); 
}