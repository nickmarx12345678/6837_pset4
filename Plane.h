#ifndef PLANE_H
#define PLANE_H

#include "Object3D.h"
#include <vecmath.h>
#include <cmath>
using namespace std;
///TODO: Implement Plane representing an infinite plane
///choose your representation , add more fields and fill in the functions
class Plane: public Object3D
{
public:
	Plane(){}
	
	Plane( const Vector3f& normal , float d , Material* m):Object3D(m){
		this->normal = normal;
		this->d = d;
	}
	~Plane(){}
	virtual bool intersect( const Ray& r , Hit& h , float tmin){
		float dnm = Vector3f::dot(r.getDirection(), normal);
		//ray and plane are parallel or do not intersect
		if (dnm == 0){
			return false;
		} else {
			float num = Vector3f::dot(normal*d-r.getOrigin(), normal);
			float t = num/dnm;
			
			//closest intersect we've seen but not too close
			if (t<h.getT() && t>tmin) {
				h.set(t,this->material, normal);
				return true;
			} else {
				return false;
			}
		}
	}

protected:
	
	float d;
	Vector3f normal;
};
#endif //PLANE_H
		

