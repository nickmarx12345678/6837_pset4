#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Object3D.h"
#include <vecmath.h>
#include <cmath>
#include <iostream>

using namespace std;
///TODO: implement this class.
///Add more fields as necessary,
///but do not remove hasTex, normals or texCoords
///they are filled in by other components
class Triangle: public Object3D
{
public:
	Triangle();
        ///@param a b c are three vertex positions of the triangle
	Triangle( const Vector3f& a, const Vector3f& b, const Vector3f& c, Material* m):Object3D(m){
		hasTex = false;
		this->a = a;
		this->b = b;
		this->c = c;
	}

	virtual bool intersect( const Ray& ray,  Hit& hit , float tmin){
		Vector3f n = Vector3f::cross(b-a, c-a);
		n = n.normalized();
		float dnm = Vector3f::dot(ray.getDirection(), n);
		if (!dnm) {
			return false;
		}
		
		float num = Vector3f::dot(a-ray.getOrigin(),n);
		float t = num/dnm;
		
		if (t<hit.getT() && t>tmin) {
			Vector3f point = ray.pointAtParameter(t);
			Vector3f v_1 = Vector3f::cross(b-a,point-a);
			Vector3f v_2 = Vector3f::cross(c-b,point-b);
			float test = Vector3f::dot(v_1,v_2);
			if ( test<0 ) {
				return false;
			}
			Vector3f v_3 = Vector3f::cross(a-c,point-c);
			test = Vector3f::dot(v_2,v_3);
			if ( test<0 ) {
				return false;
			} else {
				hit.set(t,this->material,n);
				return true;
			}
		}
		return false;
	}
	bool hasTex;
	Vector3f normals[3];
	Vector2f texCoords[3];
protected:
	Vector3f a;
	Vector3f b;
	Vector3f c;
};

#endif //TRIANGLE_H
