#ifndef DROANIMATION_H
#define DROANIMATION_H
#include <QElapsedTimer>
#include <datatypes.h>

class DROAnimation
{
public:
  DROAnimation();

  void CacheAnimation();
  float GetFrameValue(AnimationVariableTypes t_frameType, int t_frame);

  int GetLengthInFrames()
  {
    int l_largestNumber = 0;
    for(DROAnimationKeyframe rKeyframe : m_AnimationKeyframes)
    {
      if(rKeyframe.Time > l_largestNumber) l_largestNumber = rKeyframe.Time;
    }

    return l_largestNumber;
  };

  void RunAnimation();

  void SetAnimationLoops(bool l_Loop){m_AnimationLoops = l_Loop; };

  bool GetCurrentlyRunning();
  float GetCachedValue(AnimationVariableTypes type, int t_frame = -1);
  float GetCurrentValue(AnimationVariableTypes type);

  void SetNextKeyframe(AnimationVariableTypes animType);

  void Start(bool loop);
  void Stop();
  void Pause();

  void AddKeyframe(qint64 time, AnimationVariableTypes type, float value, AnimCurveType fin, AnimCurveType fout);
  void SetKeyframes(QVector<DROAnimationKeyframe> t_frames);

  int GetCurrentFrame();

  void UpdateCurrentTick(int t_tick)
  {
    if(m_DurationLength < t_tick && !m_AnimationLoops) m_IsRunning = false;
    m_DurationElapsed = t_tick;
  };

private:
  int m_AnimationTickRate = 16;
  int m_DurationLength = 0;
  qint64 m_DurationElapsed = 0;
  QHash<AnimationVariableTypes, QList<float>> m_CachedVariables = {};

  bool m_IsRunning = false;
  bool m_AnimationLoops = true;


  QVector<DROAnimationKeyframe> m_AnimationKeyframes = {};

  //TO-DO: Remove
  QElapsedTimer m_AnimationTimer = QElapsedTimer();
  int m_KeyframeIndex = 0;
  QHash<AnimationVariableTypes, int> m_UpcomingValues = {};
  QHash<AnimationVariableTypes, int> m_PreviousValues = {};
  QHash<AnimationVariableTypes, float> m_CurrentValues = {};
};

#endif // DROANIMATION_H
