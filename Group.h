#ifndef GROUP_H
#define GROUP_H


#include "Object3D.h"
#include "Ray.h"
#include "Hit.h"
#include <iostream>

using  namespace std;

///TODO: 
///Implement Group
///Add data structure to store a list of Object* 
class Group:public Object3D
{
public:

  Group(){
	  n_objects = 0;
  }
	
	Group( int num_objects ){
	  n_objects = num_objects;
	  objects = new Object3D*[num_objects];
  }

  ~Group(){
   
  }

  virtual bool intersect( const Ray& r , Hit& h , float tmin ) {
	  bool output = false;
	  for (int i=0; i<n_objects; i++) {
		  if (objects[i]->intersect(r,h,tmin)) {
			  output = true;
		  }
	  }
	  return output;
  }
	
  void addObject( int index , Object3D* obj ){
	  objects[index] = obj;
  }

  int getGroupSize(){ 
	  return n_objects;
  }

 private:
	
	int n_objects;
	Object3D** objects;

};

#endif
	
