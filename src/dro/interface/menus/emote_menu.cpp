#include "emote_menu.h"

static bool s_sizeDoubled = false;
static bool s_renderSprites = false;

#include "aoapplication.h"
#include "courtroom.h"
#include "modules/managers/character_manager.h"
#include "dro/interface/courtroom_layout.h"
#include "dro/param/actor_repository.h"

using namespace dro;

EmoteMenu::EmoteMenu(EmotionSelector *parent) : QMenu(parent)
{
  m_EmotionSelector = parent;

  m_presetsMenu = new QMenu(tr("Offsets"), this);
  p_ResetOffsetsAction = new QAction(tr("Reset (Center)"), this);
  addMenu(m_presetsMenu);
  m_presetsMenu->addAction(p_ResetOffsetsAction);

  m_layersMenu = new QMenu(tr("Layers"), this);
  addMenu(m_layersMenu);
  addSeparator();

  QMenu *buttonsMenu = addMenu(tr("Buttons"));
  p_SizeAction = buttonsMenu->addAction(tr("Resize"));
  p_RenderAction = buttonsMenu->addAction(tr("Use Sprite Images"));
  p_makerAction = buttonsMenu->addAction(tr("Button Maker"));

  connect(p_SizeAction, &QAction::triggered, this, &EmoteMenu::OnDoubleSizeTriggered);
  connect(p_RenderAction, &QAction::triggered, this, &EmoteMenu::OnRealtimeTriggered);
  connect(p_ResetOffsetsAction, &QAction::triggered, this, &EmoteMenu::OnOffsetResetTriggered);
  connect(p_makerAction, &QAction::triggered, this, &EmoteMenu::OnButtonMakerTriggered);

  m_buttonMaker = new ButtonMaker();
  m_buttonMaker->resize(960, 544);
  m_buttonMaker->hide();
}

void EmoteMenu::EmoteChange(DREmote emote)
{
  if(m_buttonMaker == nullptr) return;
  m_currentEmote = emote;
  m_buttonMaker->SetEmote(emote);

  clearLayers();
  for(const EmoteLayer &layer : emote.emoteOverlays)
  {
    if(!layer.toggleName.trimmed().isEmpty())
      AddLayer(layer.toggleName, actor::user::layerState(layer.toggleName));
  }
}

bool EmoteMenu::isRealtime()
{
  return s_renderSprites;
}

bool EmoteMenu::isDoubleSize()
{
  return s_sizeDoubled;
}

void EmoteMenu::ClearPresets()
{
  m_presetsMenu->clear();
  m_presetsMenu->addAction(p_ResetOffsetsAction);
  m_defaultVertical = 0;
  m_defaultScale = 1000;
  m_presetsClearedCheck = false;
  m_presetsMenu->addSeparator();
}

void EmoteMenu::AddPreset(const QString &name)
{
  QAction* action = m_presetsMenu->addAction(name);
  connect(action, &QAction::triggered, this, [=]() { ApplyPreset(name); });

  if(m_presetsClearedCheck) return;

  for(ActorScalingPreset presetData : actor::user::retrieve()->GetScalingPresets())
  {
    if(presetData.name == name)
    {
      m_defaultVertical = presetData.verticalAlign;
      m_defaultScale = presetData.scale;
    }
  }
  m_presetsClearedCheck = true;
}

void EmoteMenu::clearLayers()
{
  m_layersMenu->clear();
  m_layersMenu->hide();
}

void EmoteMenu::OnMenuRequested(QPoint p_point)
{
  const QPoint l_global_point = parentWidget()->mapToGlobal(p_point);
  popup(l_global_point);
}

void EmoteMenu::OnDoubleSizeTriggered()
{
  s_sizeDoubled = s_sizeDoubled == false;
  m_EmotionSelector->constructEmotes();
}

void EmoteMenu::OnRealtimeTriggered()
{
  if(s_renderSprites)
  {
    p_RenderAction->setText("Use Sprite Images");
    s_renderSprites = false;
  }
  else
  {
    p_RenderAction->setText("Use Button Images");
    s_renderSprites = true;
  }
  m_EmotionSelector->refreshEmotes(true);
}

void EmoteMenu::OnButtonMakerTriggered()
{
  m_buttonMaker->show();
  m_buttonMaker->SetCharacter(actor::user::retrieve()->GetFolder());
  m_buttonMaker->SetEmote(m_currentEmote);
}

void EmoteMenu::OnOffsetResetTriggered()
{
  courtroom::sliders::setScale(m_defaultScale);
  courtroom::sliders::setVertical(m_defaultVertical);
  courtroom::sliders::setHorizontal(500);
}

void EmoteMenu::AddLayer(const QString &name, bool defaultValue)
{
  QAction* action = m_layersMenu->addAction(name);
  action->setCheckable(true);
  action->setChecked(defaultValue);

  connect(action, &QAction::toggled, this, [=](bool checked){
    dro::actor::user::toggleLayer(name, checked);
  });
}

void EmoteMenu::ApplyPreset(const QString &presetName)
{
  for(ActorScalingPreset presetData : actor::user::retrieve()->GetScalingPresets())
  {
    if(presetData.name == presetName)
    {
      courtroom::sliders::setScale(presetData.scale);
      courtroom::sliders::setVertical(presetData.verticalAlign);
      m_defaultVertical = presetData.verticalAlign;
      m_defaultScale = presetData.scale;
    }
  }
}
