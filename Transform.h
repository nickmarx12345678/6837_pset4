#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <vecmath.h>
#include "Object3D.h"
///TODO implement this class
///So that the intersect function first transforms the ray
///Add more fields as necessary
class Transform: public Object3D
{
public: 
	Transform(){}
	Transform( const Matrix4f& m, Object3D* obj ):o(obj){
		this->mtx = m;
		this->o = obj;
	}
	~Transform(){
	}
	virtual bool intersect( const Ray& r , Hit& h , float tmin){
		Matrix4f inverse = mtx.inverse();
		Vector4f origin = inverse*Vector4f(r.getOrigin(),1);
		Vector4f direction  = inverse*Vector4f(r.getDirection(),0);
		Ray ray_i = Ray(Vector3f(origin[0],origin[1],origin[2]),Vector3f(direction[0],direction[1],direction[2]));
		
		Hit hit = Hit(h);
		
		if (o->intersect(ray_i, hit, tmin))
		{
			Vector4f n = (inverse.transposed())*Vector4f(hit.getNormal(),0);
			h.set(hit.getT(), hit.getMaterial(), Vector3f(n[0],n[1],n[2]).normalized());
			return true;
		}
		return false;
	}

	protected:
	Object3D* o; //un-transformed object
	Matrix4f mtx; 
	
};

#endif //TRANSFORM_H
