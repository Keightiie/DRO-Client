#include "scenetestinglabs.h"
#include <aoimagedisplay.h>
#include "neo/viewport/neo_renderer.h"
#include "neo/readers/models/obj_model_reader.h"


SceneTestingLabs::SceneTestingLabs(QWidget *parent) : QWidget{parent}
{
  ConstructWidgets();
  setWindowTitle("Testing Labs");
  setFocusPolicy(Qt::StrongFocus);
  setAttribute(Qt::WA_DeleteOnClose, true );
}

void SceneTestingLabs::ConstructWidgets()
{
  NeoRenderer *l_NeoViewport = new NeoRenderer();
  l_NeoViewport->resize(960, 544);
  l_NeoViewport->show();

  l_NeoViewport->TranslateTransform(QVector3D(-1, -1,  3));
  l_NeoViewport->TranslateRotation(QVector3D(0, 90,  0));

  ObjModelReader *l_ModelReader = new ObjModelReader("base/models/backgrounds/DR1-1 Trial Grounds", "model.obj");
  l_NeoViewport->LoadSceneObject(l_ModelReader->GenerateSceneObject());
}

void SceneTestingLabs::OnPlayAnimationClicked()
{

}
