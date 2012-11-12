#ifndef CAMERA_H
#define CAMERA_H

#include "Ray.h"
#include <vecmath.h>
#include <float.h>
#include <cmath>


class Camera
{
public:
	//generate rays for each screen-space coordinate
	virtual Ray generateRay( const Vector2f& point ) = 0 ; 
	
	virtual float getTMin() const = 0 ; 
	virtual ~Camera(){}
protected:
	Vector3f center; 
	Vector3f direction;
	Vector3f up;
	Vector3f horizontal;

};

///TODO: Implement Perspective camera
///Fill in functions and add more fields if necessary
class PerspectiveCamera: public Camera
{
public:
	PerspectiveCamera(const Vector3f& center, const Vector3f& direction,const Vector3f& up , float angle){
		this->center = center;
		this->direction = direction.normalized();
		this->up = up.normalized();
		this->angle = angle;
		horizontal = Vector3f::cross(direction,up);
	}

	virtual Ray generateRay( const Vector2f& point){
		float distance = 1.0/tan(angle/2.0);
		Vector3f ray_direction = (direction*distance+point[0]*horizontal+point[1]*up).normalized();
		return Ray(center,ray_direction);
	}

	virtual float getTMin() const { 
		return 0.0f;
	}

private:
	
	Vector3f direction;
	Vector3f up;
	Vector3f center;
	Vector3f horizontal;
	float angle;
};

#endif //CAMERA_H
