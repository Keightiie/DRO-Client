#include "viewport_entity.h"

#include <QtMath>
#include <dro/rendering/gl/dro_shader.h>
#include <dro/rendering/gl/renderer2d.h>

ViewportEntity::ViewportEntity()
{
}

void ViewportEntity::SetShader(QOpenGLShaderProgram *material)
{
  m_Shader = material;
}

void ViewportEntity::SetCamera(ViewportCamera * camera)
{
  m_CameraTarget = camera;

  if(m_Shader != nullptr)
  {
    m_Shader->bind();
    m_Shader->setUniformValue("u_ViewProjection", m_CameraTarget->GetMatrix());
  }
}

void ViewportEntity::LoadVerticies(QVector<DROVertexData> verticies)
{
  m_Buffer = new DROVertexBuffer(verticies);
}

void ViewportEntity::Draw()
{
  QMatrix4x4 l_Transform;

  //m_Scale = {1.0f, 1.0f, 1.0f};
  QVector3D m_PivotAdjusted = {m_Scale.x() / 2, m_PivotPoint.y(), m_PivotPoint.z()};
  l_Transform.translate(m_Transform);
  l_Transform.translate(m_PivotAdjusted);
  l_Transform.rotate(QQuaternion::fromEulerAngles(m_Rotation));
  l_Transform.translate(-m_PivotAdjusted);
  l_Transform.scale(m_Scale);

  if(m_Shader != nullptr)
  {
    m_Shader->bind();
    m_Shader->setUniformValue("u_Transform", l_Transform);
  }

  m_Buffer->Draw(m_Shader);
}

void ViewportEntity::SetPosition(QVector3D position)
{
  m_Transform = position;
}

void ViewportEntity::SetRotation(QVector3D rotation)
{
  m_Rotation = rotation;
}

void ViewportEntity::SetScale(QVector3D scale)
{
  m_Scale = scale;
}

///
/// Player Entity Functions
///

PlayerEntity::PlayerEntity()
{
  QVector<DROVertexData> l_verticies =
      {
          {{ 0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
          {{ 1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
          {{ 1.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
          {{ 1.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
          {{ 0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},
          {{ 0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}}
      };

  SetShader(DROShader::GetShader("UserInterface"));
  SetCamera(Renderer2D::GetInterfaceCamera());
  LoadVerticies(l_verticies);


  m_Animator = ViewportAnimator::LoadAnimation("glFLING");

  m_PerspectiveAnimCam = new ViewportCamera();

  m_PerspectiveAnimCam->SetProjection(960.0f / 544.0f, 53.1f);
  m_PerspectiveAnimCam->SetPosition({-480.0f, -272.0f, -544.0f});
  SetCamera(m_PerspectiveAnimCam);

}

void PlayerEntity::Draw()
{
  if(m_Texture == nullptr) return;
  m_Texture->Bind();

  ViewportEntity::Draw();
}

void PlayerEntity::OnUpdate(float deltaTime)
{
  m_Texture->UpdateDelay((int)deltaTime);
  m_Animator->OnUpdate((int)deltaTime);

  SetPosition(m_Animator->GetVec3("position"));
  SetRotation(m_Animator->GetVec3("rotation"));
  SetScale(m_Animator->GetVec3("scale"));
}

void PlayerEntity::SetCharacter(QString character, QString emote)
{
  if(m_Texture != nullptr)
  {
    delete m_Texture;
  }
  m_Texture = DROTexture::Create(character);

  m_Animator->SetRelative("position", {(float)m_Texture->GetXValue(), 0, 0});
  m_Animator->SetRelative("scale", {(float)m_Texture->GetWidth(), (float)m_Texture->GetHeight(), 1});
  m_Animator->Restart();
}
