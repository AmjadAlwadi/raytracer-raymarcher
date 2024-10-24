#include <iostream>
#include <string>

#include "camera/camera.h"
#include "camera/dofcamera.h"

#include "scene/simplescene.h"
#include "renderer/customdofrenderer.h"

#include "primitive/box.h"
#include "primitive/infiniteplane.h"
#include "primitive/objmodel.h"
#include "primitive/sphere.h"

#include "shader/brdfshader.h"

#include "shader/lambertshader.h"
#include "shader/mirrorshader.h"
#include "shader/phongshader.h"
#include "shader/cooktorranceshader.h"

#include "light/ambientlight.h"
#include "light/pointlight.h"
#include "light/spotlight.h"


#include "scene/fastscene.h"

#include "shader/materialshader.h"


int main() {

    int pixelsX = 1000;
    int pixelsY = 1000;


    FastScene scene;


  // Add shaders
  auto mirror = std::make_shared<MirrorShader>();
  auto white = std::make_shared<LambertShader>(Color(0.9f, 0.9f, 0.9f));
  auto red = std::make_shared<LambertShader>(Color(1.0f, 0.3f, 0.2f));
  auto blue = std::make_shared<LambertShader>(Color(0.2f, 0.3f, 1.0f));
  auto orange = std::make_shared<PhongShader>(Color(1.0f, 0.64f, 0.0f), 1.0f, Color(1.0f, 1.0f, 1.0f), 1.0f, 25.0f);
  auto gold= std::make_shared<CookTorranceShader>(Color(0.83f, 0.69f, 0.22f), Color(1.0f, 1.0f, 0.0f), 1.2f, 0.2f);
  auto blueMetallic = std::make_shared<BrdfShader>("D:/Cg/group_12/data/blue-metallic-paint.binary", Color(7.0f, 7.0f, 7.0f));
  auto darkRed = std::make_shared<BrdfShader>("D:/Cg/group_12/data/dark-red-paint.binary", Color(7.0f, 7.0f, 7.0f));


  scene.add(std::make_shared<InfinitePlane>(Vector3d(0.0f, +5.0f, 0.0f), Vector3d(0.0f, -1.0f, 0.0f), orange));
  scene.add(std::make_shared<InfinitePlane>(Vector3d(0.0f, -5.0f, 0.0f), Vector3d(0.0f, +1.0f, 0.0f), white));
  scene.add(std::make_shared<InfinitePlane>(Vector3d(+5.0f, 0.0f, 0.0f), Vector3d(-1.0f, 0.0f, 0.0f), blue));
  scene.add(std::make_shared<InfinitePlane>(Vector3d(-5.0f, 0.0f, 0.0f), Vector3d(+1.0f, 0.0f, 0.0f), red));


  scene.add(std::make_shared<Sphere>(Vector3d(-3.0f, 0.0f, 0.0f), 1.0f, blueMetallic));
  scene.add(std::make_shared<Sphere>(Vector3d(0.0f, 2.0f, 0.0f), 1.0f, orange));
  scene.add(std::make_shared<Sphere>(Vector3d(3.0f, 0.0f, 0.0f), 1.0f, darkRed));
  scene.add(std::make_shared<Sphere>(Vector3d(0.0f, 0.0f, 10), 1.0f, gold));




  // Add ambient light
  scene.add(std::make_shared<AmbientLight>(0.15f));
  scene.add(std::make_shared<PointLight>(Vector3d(0.0f, 4.0f, -4.0f), 15.0f));
  scene.add(std::make_shared<PointLight>(Vector3d(0.0f, 4.0f, 4.0f), 15.0f));


  // Set up the camera
  DofCamera camera;
  camera.setFovAngle(90.0f);
  camera.setPosition(Vector3d(0.0f, 0.0f, -10.0f));
  camera.setForwardDirection(Vector3d(0.0f, 0.0f, 1.0f));
  camera.setUpDirection(Vector3d(0.0f, 1.0f, 0.0f));
  camera.setStrength(600);
  camera.setFocalDistance(11.f);
  camera.number_pixels_x = pixelsX;


// build the tree
scene.buildTree();
CustomDofRenderer cr;
cr.setSuperSamplingFactor(30);
cr.renderImage(scene, camera, pixelsX, pixelsY).save("D:/Cg/Base edition/base/out/build/x64-Debug/result_super_duper.png");






  return 0;
}
