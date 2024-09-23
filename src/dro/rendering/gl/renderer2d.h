#ifndef RENDERER2D_H
#define RENDERER2D_H

#include <dro/rendering/dro_texture.h>
#include <dro/rendering/viewport_entity.h>
#include <dro/rendering/viewport_camera.h>


class Renderer2D
{
public:
  static void Init();
  static void ClearViewport();
  static void DrawQuad(DROTexture *texture, QRect rect);
  static ViewportCamera *GetInterfaceCamera();

};

#endif // RENDERER2D_H
