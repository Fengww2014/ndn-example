#ifndef NDNSIM_EXAMPLES_NDN_TAGFORWARD_STRATEGY_HPP
#define NDNSIM_EXAMPLES_NDN_TAGFORWARD_STRATEGY_HPP

#include <boost/random/mersenne_twister.hpp>
#include "face/face.hpp"
#include "fw/strategy.hpp"
#include "fw/algorithm.hpp"

namespace nfd {
namespace fw {

class TagforwardStrategy : public Strategy {
public:
  TagforwardStrategy(Forwarder& forwarder, const Name& name = getStrategyName());

  virtual ~TagforwardStrategy() override;

  virtual void
  afterReceiveInterest(const Face& inFace, const Interest& interest,
                       const shared_ptr<pit::Entry>& pitEntry) override;

  static const Name&
  getStrategyName();

protected:
  boost::random::mt19937 m_randomGenerator;
};

} // namespace fw
} // namespace nfd

#endif // NDNSIM_EXAMPLES_NDN_TAGFORWARD_STRATEGY_HPP
