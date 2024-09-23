#include "rendering_layer.h"
#include "file_functions.h"

#include <aoapplication.h>
#include <QtMath>

#include <modules/background/background_reader.h>
#include <modules/background/legacy_background_reader.h>

RenderingLayer::RenderingLayer()
{
}

NovelLayer::NovelLayer()
{
  m_BackgroundSprite = DROTexture::Create("base/shouts/default/witnesstestimony.webp");
  m_Player = new PlayerEntity();
  m_Player->SetCharacter("normal.png", "");
}

void NovelLayer::OnUpdate()
{
  m_BackgroundSprite->UpdateDelay(16);
  m_Player->OnUpdate(16);

  Renderer2D::ClearViewport();
  Renderer2D::DrawQuad(m_BackgroundSprite, {0, 0, 960, 544});

  m_Player->Draw();
}

void NovelLayer::UpdateBackground(QString background)
{
  m_BackgroundName = background;
  m_BackgroundPosition = "";

  const QString l_backgroundJSONPath = AOApplication::getInstance()->find_asset_path(AOApplication::getInstance()->get_background_path(m_BackgroundName) + "/" + "background.json");


  if(file_exists(l_backgroundJSONPath)) m_BackgroundData = new BackgroundReader();
  else m_BackgroundData = new LegacyBackgroundReader();

  m_BackgroundData->execLoadBackground(background);

  UpdateBgPosition("wit");

}

void NovelLayer::UpdateBgPosition(QString position)
{
  if(m_BackgroundPosition == position) return;
  if(m_BackgroundData == nullptr) return;
  m_BackgroundPosition = position;
  QString l_filename = m_BackgroundData->getBackgroundFilename(position);

  delete m_BackgroundSprite;
  m_BackgroundSprite = DROTexture::Create(AOApplication::getInstance()->get_background_sprite_path(m_BackgroundName, l_filename));
}

void NovelLayer::UpdateNovel(ICMessageData lMessage)
{
  if(!lMessage.m_CharacterOutfit.trimmed().isEmpty()) lMessage.m_CharacterFolder = (lMessage.m_CharacterFolder + "/outfits/" +  lMessage.m_CharacterOutfit);

  m_CharacterFolder = lMessage.m_CharacterFolder;
  m_CharacterEmotion = lMessage.m_CharacterEmotion;

  m_SpriteState = ePre;
  if(lMessage.m_UsesPreAnimation)
  {
    m_Player->SetCharacter(AOApplication::getInstance()->get_character_sprite_idle_path(m_CharacterFolder, lMessage.m_PreAnimation), "");
    connect(m_Player->GetTexture(), &DROTexture::AnimationEnd, this, &NovelLayer::PreAnimComplete);
  }
  else
  {
    PreAnimComplete();
  }

  UpdateBgPosition(lMessage.m_AreaPosition);
}

void NovelLayer::PreAnimComplete()
{
  if(m_SpriteState != ePre) return;
  m_Player->SetCharacter(AOApplication::getInstance()->get_character_sprite_idle_path(m_CharacterFolder, m_CharacterEmotion), "");
  m_SpriteState = eIdle;
}
