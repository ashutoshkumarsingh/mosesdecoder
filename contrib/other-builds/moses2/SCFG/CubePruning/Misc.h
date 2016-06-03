/*
 * Misc.h
 *
 *  Created on: 2 Jun 2016
 *      Author: hieu
 */
#pragma once
#include <vector>
#include <queue>
#include "../../HypothesisColl.h"
#include "../Hypothesis.h"

namespace Moses2
{

namespace SCFG
{
class TargetPhrases;
class Queue;

///////////////////////////////////////////
class QueueItem
{
public:
  const SymbolBind &symbolBind;
  const SCFG::TargetPhrases &tps;
  size_t tpInd;

  std::vector<const Moses2::HypothesisColl *> hyposColl;
  std::vector<size_t> hypoIndColl;
    // hypos and ind to the 1 we're using

  SCFG::Hypothesis *hypo;

  QueueItem(
      const SymbolBind &symbolBind,
      const SCFG::TargetPhrases &tps,
      size_t vTPInd = 0);
  void AddHypos(const Moses2::HypothesisColl &hypos);
  void CreateHypo(
      SCFG::Manager &mgr,
      const SCFG::InputPath &path,
      const SCFG::SymbolBind &symbolBind);

  void CreateNext(
      SCFG::Manager &mgr,
      SCFG::Queue &queue,
      const SCFG::InputPath &path);
};

///////////////////////////////////////////
class QueueItemOrderer
{
public:
  bool operator()(QueueItem* itemA, QueueItem* itemB) const
  {
    HypothesisFutureScoreOrderer orderer;
    return !orderer(itemA->hypo, itemB->hypo);
  }
};

///////////////////////////////////////////
class Queue : public std::priority_queue<QueueItem*,
    std::vector<QueueItem*>,
    QueueItemOrderer>
{

};


}
}



