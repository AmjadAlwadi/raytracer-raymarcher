#include "camera/perspectivecamera.h"

PerspectiveCamera::PerspectiveCamera() {

	this->forwardDirection = Vector3d(0, 0, 1);
	this->upDirection = Vector3d(0, 1, 0);
	this->rightDirection = Vector3d(1, 0, 0);
	setFovAngle(70);

}



Vector2d random_point_in_circle() {

	// Generate a random number and normalize it to the range [0, 1)
	float random_number = static_cast<float>(std::rand()) / RAND_MAX;

	// Generate a random number and normalize it to the range [0, 1)
	float random_number_sqrt = sqrt(static_cast<float>(std::rand()) / RAND_MAX);

	float angle = random_number * 2 * PI;

	Vector2d point_on_circle = Vector2d(cos(angle), sin(angle));

	return point_on_circle * random_number_sqrt;

}



Ray PerspectiveCamera::createRay(float x, float y, uint32_t& state) {

	// Calculate the direction of the ray without considering the focal distance
	Vector3d rayDirection = x * this->rightDirection + y * this->upDirection + focus * this->forwardDirection;

	rayDirection = normalized(rayDirection);

	// Calculate the point on the focal plane that this ray should focus on
   // It's the point where the ray intersects the focal plane
	Vector3d focalPoint = this->position + (rayDirection * this->focalDistance);

	Vector2d jitter = random_point_in_circle() * strength;

	Vector3d rayOrigin = this->position + this->rightDirection * jitter.u + this->upDirection * jitter.v;

	// Adjust the ray's direction to point towards the focal point
	// This simulates the effect of the camera focusing at a certain distance
	Vector3d adjustedRayDirection = focalPoint - rayOrigin;


	// Normalize the adjusted direction
	adjustedRayDirection = normalized(adjustedRayDirection);

	// Create the ray with the adjusted direction
	return Ray(rayOrigin, adjustedRayDirection);

}
