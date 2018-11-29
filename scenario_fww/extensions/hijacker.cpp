// hijacker.cpp

#include "hijacker.hpp"

#include "ns3/log.h"

#include "ns3/ndnSIM/helper/ndn-fib-helper.hpp"

NS_LOG_COMPONENT_DEFINE("Hijacker");

namespace ns3 {

// Necessary if you are planning to use ndn::AppHelper
NS_OBJECT_ENSURE_REGISTERED(Hijacker);

TypeId
Hijacker::GetTypeId()
{
  static TypeId tid = TypeId("Hijacker").SetParent<ndn::App>().AddConstructor<Hijacker>();

  return tid;
}

Hijacker::Hijacker()
{
}

void
Hijacker::OnInterest(std::shared_ptr<const ndn::Interest> interest)
{
  ndn::App::OnInterest(interest); // forward call to perform app-level tracing
  // do nothing else (hijack interest)

  NS_LOG_DEBUG("Do nothing for incoming interest for" << interest->getName());
}

void
Hijacker::StartApplication()
{
  App::StartApplication();

  // equivalent to setting interest filter for "/prefix" prefix
  ndn::FibHelper::AddRoute(GetNode(), "/prefix/sub", m_face, 0);
}

void
Hijacker::StopApplication()
{
  App::StopApplication();
}

} // namespace ns3
