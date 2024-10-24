#include "camera/dofcamera.h"
#include <random>

DofCamera::DofCamera() : forwardDirection(0, 0, 1), upDirection(0, 1, 0), rightDirection(1, 0, 0) { setFovAngle(70); }





uint32_t pcg_hash(uint32_t input)
{
	uint32_t state = input * 747796405u + 2891336453u;
	uint32_t word = ((state >> ((state >> 28u) + 4u)) ^ state) * 277803737u;
	return (word >> 22u) ^ word;
}


float randomFloat(uint32_t& state) {
	state = pcg_hash(state);
	return  (float)state / (float)std::numeric_limits<uint32_t>::max();
}





Vector2d DofCamera::random_point_in_circle(uint32_t& state) {

	// Generate a random number and normalize it to the range [0, 1)
	float random_number = randomFloat(state);

	float random_number_sqrt = sqrt(randomFloat(state));

	float angle = random_number * 2 * PI;

	Vector2d point_on_circle = Vector2d(cos(angle), sin(angle));

	return point_on_circle * random_number_sqrt;

}



Ray DofCamera::createRay(float x, float y, uint32_t& state){

	

	//Vector2d defocusJitter = random_point_in_circle(state) * defocusStrength / (float)this->number_pixels_x;

	// Calculate the direction of the ray without considering the focal distance
	Vector3d rayDirection =  x * this->rightDirection + y * this->upDirection + focus * this->forwardDirection;

	rayDirection = normalized(rayDirection);

	// Calculate the point on the focal plane that this ray should focus on
   // It's the point where the ray intersects the focal plane
	Vector3d focalPoint = this->position + (rayDirection * this->focalDistance); //+ defocusJitter.u * this->rightDirection + defocusJitter.v * this->upDirection;

	Vector2d jitter =  random_point_in_circle(state) * strength / (float) this->number_pixels_x;

	Vector3d rayOrigin = this->position + this->rightDirection * jitter.u + this->upDirection * jitter.v;

	// Adjust the ray's direction to point towards the focal point
	// This simulates the effect of the camera focusing at a certain distance
	Vector3d adjustedRayDirection = focalPoint - rayOrigin;


	// Normalize the adjusted direction
	adjustedRayDirection = normalized(adjustedRayDirection);

	// Create the ray with the adjusted direction
	return Ray(rayOrigin, adjustedRayDirection);

}