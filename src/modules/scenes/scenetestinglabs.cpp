#include "scenetestinglabs.h"
#include "dro/rendering/gl/renderer2d.h"


SceneTestingLabs::SceneTestingLabs(QWidget *parent) : QWidget{parent}
{
  ConstructWidgets();
  setWindowTitle("Testing Labs");
  setFocusPolicy(Qt::StrongFocus);
  setAttribute(Qt::WA_DeleteOnClose, true );


  m_Viewport->setFocusPolicy(Qt::StrongFocus);
  m_Viewport->setUpdatesEnabled(true);

  connect(m_Viewport, &GLViewportWidget::GLInitialize, this, &SceneTestingLabs::ViewportLoaded);
  connect(m_Viewport, &GLViewportWidget::FrameComplete, this, &SceneTestingLabs::ViewportUpdate);




}

void SceneTestingLabs::ConstructWidgets()
{
  this->resize(960, 544);
  m_Viewport = new GLViewportWidget(this);  m_Viewport->move(0, 0);
  m_Viewport->resize(960, 544);
  m_Viewport->show();
}

void SceneTestingLabs::ViewportLoaded()
{
  m_NovelLayer = new NovelLayer();
}

void SceneTestingLabs::ViewportUpdate()
{
  if(m_NovelLayer != nullptr)
  {
    m_NovelLayer->OnUpdate();
  }
  //m_Viewport->update();
}
