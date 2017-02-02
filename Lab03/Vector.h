#ifndef VECTOR_H
#define VECTOR_H
#pragma once

class Vector 
{
	private:
		double xVal;
		double yVal;
	public:
		Vector();
		Vector(double x, double y);
		Vector(double r, float Theta);
		
		double getX();
		void setX(double x);

		double getY();
		void setY(double y);

		double getMagnitude();
		float getAngle();
		void print();

		//Task 3
		bool operator==(Vector v);
		void operator*(double scalar);
		void operator+(Vector v);
		void operator-(Vector v);
	
};
#endif
