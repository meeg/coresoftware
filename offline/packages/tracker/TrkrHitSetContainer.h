#ifndef __TrkrHitSetContainer_H__
#define __TrkrHitSetContainer_H__

#include "TrkrHitSet.h"

#include <phool/PHObject.h>

#include <map>
#include <set>

class TrkrHitSetContainer: public PHObject
{

  public:
  typedef std::map<TrkrDefs::hitsetkey,TrkrHitSet *> Map;
  typedef Map::iterator Iterator;
  typedef Map::const_iterator ConstIterator;
  typedef std::pair<Iterator, Iterator> Range;
  typedef std::pair<ConstIterator, ConstIterator> ConstRange;

  TrkrHitSetContainer();

  virtual ~TrkrHitSetContainer() {}

  void Reset();

  void identify(std::ostream& os = std::cout) const;

  ConstIterator AddHit(TrkrHitSet *newHit);
  ConstIterator AddHitSpecifyKey(const TrkrDefs::hitsetkey key, TrkrHitSet *newHit);
  
  //! preferred removal method, key is currently the hit id
  void RemoveHit(TrkrDefs::hitsetkey key) {
    hitmap.erase(key);
  }

  //! inefficent, use key where possible instead
  void RemoveHit(TrkrHitSet *hit)
  {
    Iterator its = hitmap.begin();
    Iterator last = hitmap.end();
    for (; its != last;)
      {
	if (its->second == hit)
	  {
	    hitmap.erase(its++);
	  }
	else
	  {
	    ++its;
	  }
      }
  }


  Iterator findOrAddHit(TrkrDefs::hitsetkey key);

  //! return all Hits matching a given detid
  ConstRange getHits(const TrkrDefs::TRKRID trackerid) const;

  //! return all Hits matching a given detid, layer
  ConstRange getHits(const TrkrDefs::TRKRID trackerid, const char layer) const;

  //! return all hist
  ConstRange getHits( void ) const;

  TrkrHitSet* findHit(TrkrDefs::hitsetkey key);

  unsigned int size( void ) const
  { return hitmap.size(); }

 protected:
  Map hitmap;
  ClassDef(TrkrHitSetContainer,1)
};

#endif