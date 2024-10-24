#ifndef CUSTOMDOFRENDERER_H
#define CUSTOMDOFRENDERER_H

#include "renderer/renderer.h"
#include "camera/perspectivecamera.h"
#include <atomic>

class CustomDofRenderer : public Renderer {
  static void renderThread(const Scene *scene, Camera* camera, Texture *image, int width, int widthStep,
                           int widthOffset, int height, int heightStep, int heightOffset, std::atomic<int> *k,
                           int const stepSize, int superSamplingFactor);

public:
  // Constructor / Destructor
    CustomDofRenderer() = default;
  ~CustomDofRenderer() override = default;

  // Get
  int superSamplingFactor() { return this->superSamplingFactor_; }

  // Set
  void setSuperSamplingFactor(int factor) { this->superSamplingFactor_ = factor; }

  // Render functions
  Texture renderImage(Scene const &scene, Camera &camera, int width, int height) override;

  float strength = 100;

private:
  int superSamplingFactor_ = 2;
  
};

#endif
