#ifndef SPHERE_H
#define SPHERE_H

#include "Object3D.h"
#include <vecmath.h>
#include <cmath>

#include <iostream>
using namespace std;
///TODO:
///Implement functions and add more fields as necessary
class Sphere: public Object3D
{
public:
	Sphere(){ 
		this->ctr = Vector3f(0,0,0);
		this->rad = 1.0;
	}

	Sphere( Vector3f center , float radius , Material* material ):Object3D(material){
		this->ctr = center;
		this->rad = radius;
	}
	

	~Sphere(){}

	virtual bool intersect( const Ray& r , Hit& h , float tmin){
		Vector3f diff = r.getOrigin() - ctr;
		float a = Vector3f::dot(r.getDirection(),r.getDirection());
		float b = 2*Vector3f::dot(r.getDirection(), diff);
		float c = Vector3f::dot(diff,diff) - (rad*rad);
		
		//evaluate quadratic equation disc, negative == miss, positive == hit
		if ( b*b-4*a*c<0 )
		{
			return false;
		} else {
			float t = h.getT();
			float disc = sqrt(b*b-4*a*c);
			float t_1 = (-b+disc)/(2*a);
			float t_2 = (-b-disc)/(2*a);
			
			
			if ( (t_1<t && t_1>=tmin) || (t_2<t && t_2>=tmin) )
			//new closest intersection, chose correct side
			{			
				if ( t_1 < t_2 )
				{
					Vector3f N = (r.pointAtParameter(t_1)-ctr).normalized();
					h.set(t_1,this->material,N);
					return true;
				} else {
					Vector3f N = (r.pointAtParameter(t_2)-ctr).normalized();
					h.set(t_2,this->material,N);
					return true;
				}
			}
			//falls through, not closer than best or not farther than min
			return false;
		}
	}

protected:
	Vector3f ctr;
	float rad;

};


#endif
