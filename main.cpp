#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>

#include "SceneParser.h"
#include "Image.h"
#include "Camera.h"
#include <string.h>

using namespace std;

float clampedDepth ( float depthInput, float depthMin , float depthMax)
{
	if ( depthInput < depthMin )
		return depthMin;
	if ( depthInput>depthMax )
		return depthMax;
	return depthInput;
}

#include "bitmap_image.hpp"
int main( int argc, char* argv[] )
{
	// Fill in your implementation here.

  // This loop loops over each of the input arguments.
  // argNum is initialized to 1 because the first
  // "argument" provided to the program is actually the
  // name of the executable (in our case, "a4").

	//initialize command line inps
	char *in_file = NULL;
	char *out_file = NULL;
	int height = 200; int width = 200;
	
	//parse command line args
	for (int i=1; i<argc; i++) {
		if (!strcmp(argv[i], "-input")) {
			in_file = argv[++i];
			cout << "Input file: " << in_file << "\n";
		}
		else if (!strcmp(argv[i],"-size")) {
			width = atoi(argv[++i]);
			height = atoi(argv[++i]);
			cout << "width: " << width << "\n";
			cout << "height: " << height << "\n";
		}
		else if (!strcmp(argv[i], "-output")) {
			out_file = argv[++i];
			cout << "output file: " << out_file << "\n";
		}
	}
	
	
	SceneParser parser = SceneParser(in_file);
	
	Camera* camera = parser.getCamera();
	Group* group = parser.getGroup();
	Vector3f ambientLight = parser.getAmbientLight();
	
	Image image(width, height);
	image.SetAllPixels(parser.getBackgroundColor());
	
	for (int i=0; i<width; i++) {
		for (int j=0; j<height; j++) {
			Hit hit = Hit();
			
			float x = (1.0+2.0*(i-(width-1.0))/(width-1.0))*(float)width/(float)height;
			float y = 1.0+2.0*(j-(height-1.0))/(height-1.0);
			
			Ray ray = camera->generateRay(Vector2f(x,y));
			
			//ray intersect with surface
			if (group->intersect(ray,hit,camera->getTMin())){
				
				Material* material = hit.getMaterial();
				Vector3f colour = ambientLight*material->getDiffuseColor();				
				
				for (int k=0; k<parser.getNumLights(); k++) {
					//Add diffuse shading
					Vector3f position = ray.pointAtParameter(hit.getT());
					Light* l = parser.getLight(k);
					
					Vector3f light_vec; Vector3f light_col;
					l->getIllumination(position,light_vec,light_col);
					
					
					colour = colour + clampedDepth(Vector3f::dot(light_vec,hit.getNormal()),0.0,1.0)*light_col*material->getDiffuseColor();
				}
				
				image.SetPixel(i,j,colour);

			}
		}
	}
    
	// First, parse the scene using SceneParser.
	// Then loop over each pixel in the image, shooting a ray
	// through that pixel and finding its intersection with
	// the scene.  Write the color at the intersection to that
	// pixel in your output image.




	///TODO: below demonstrates how to use the provided Image class
	///Should be removed when you start
	Vector3f pixelColor (1.0f,0,0);
	
	image.SaveImage(out_file);
	return 0;
}

