// hijacker.hpp

#ifndef HIJACKER_H_
#define HIJACKER_H_

#include "ns3/ndnSIM/apps/ndn-app.hpp"

namespace ns3 {

class Hijacker : public ndn::App {
public:
  static TypeId
  GetTypeId();

  Hijacker();

  // Receive all Interests but do nothing in response
  void
  OnInterest(std::shared_ptr<const ndn::Interest> interest);

protected:
  // inherited from Application base class.
  virtual void
  StartApplication();

  virtual void
  StopApplication();
};

} // namespace ns3

#endif // HIJACKER_H_
