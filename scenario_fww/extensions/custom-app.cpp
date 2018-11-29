// custom-app.cpp

#include "custom-app.hpp"
#include "ns3/ptr.h"
#include "ns3/log.h"
#include "ns3/simulator.h"
#include "ns3/packet.h"

#include "ns3/ndnSIM/helper/ndn-stack-helper.hpp"
#include "ns3/ndnSIM/helper/ndn-fib-helper.hpp"
#include <ndn-cxx/lp/tags.hpp>
#include "utils/ndn-ns3-packet-tag.hpp"
#include "ns3/random-variable-stream.h"

NS_LOG_COMPONENT_DEFINE("CustomApp");

namespace ns3 {

NS_OBJECT_ENSURE_REGISTERED(CustomApp);

// register NS-3 type
TypeId
CustomApp::GetTypeId()
{
  static TypeId tid = TypeId("CustomApp").SetParent<ndn::App>().AddConstructor<CustomApp>();
  
  return tid;
}

CustomApp::CustomApp()
  :m_frequency(1.0)
  ,m_firstTime(true)
{
}

// Processing upon start of the application
void
CustomApp::StartApplication()
{
  // initialize ndn::App
  ndn::App::StartApplication();

  // Add entry to FIB for `/prefix/sub`
  //ndn::FibHelper::AddRoute(GetNode(), "/prefix/sub", m_face, 2);

  // Schedule send of first interest
  Simulator::Schedule(Seconds(1.0), &CustomApp::SendInterest, this);
}
// Processing when application is stopped
void
CustomApp::StopApplication()
{
  // cleanup ndn::App
  ndn::App::StopApplication();
}

void
CustomApp::SendInterest()
{
  /////////////////////////////////////
  // Sending one Interest packet out //
  /////////////////////////////////////

  // Create and configure ndn::Interest
  auto interest = std::make_shared<ndn::Interest>("/prefix");
  Ptr<UniformRandomVariable> rand = CreateObject<UniformRandomVariable>();
  interest->setNonce(rand->GetValue(0, std::numeric_limits<uint32_t>::max()));
  interest->setInterestLifetime(ndn::time::seconds(5));

  NS_LOG_DEBUG("Sending Interest packet for " << *interest);

  // Call trace (for logging purposes)
  m_transmittedInterests(interest, this, m_face);
  //cout face
  //std::cout<<m_face->nfd::face::Face::getRemoteUri()<<std::endl;
  m_appLink->onReceiveInterest(*interest);
  
 }

// Callback that will be called when Interest arrives
void
CustomApp::OnInterest(std::shared_ptr<const ndn::Interest> interest)
{
  ndn::App::OnInterest(interest);

  NS_LOG_DEBUG("Received Interest packet for " << interest->getName());
  // Note that Interests send out by the app will not be sent back to the app !

  auto data = std::make_shared<ndn::Data>(interest->getName());
  data->setFreshnessPeriod(ndn::time::milliseconds(1000));
  data->setContent(std::make_shared< ::ndn::Buffer>(1024));
  ndn::StackHelper::getKeyChain().sign(*data);
  //  data->setTag(std::make_shared<ndn::lp::FwwTag>(0));
  NS_LOG_DEBUG("Sending Data packet for " << data->getName());

  // Call trace (for logging purposes)
  m_transmittedDatas(data, this, m_face);

  m_appLink->onReceiveData(*data);

}

// Callback that will be called when Data arrives
void
CustomApp::OnData(std::shared_ptr<const ndn::Data> data)
{
  NS_LOG_DEBUG("Receiving Data packet for " << data->getName());
  std::cout << "DATA received for name " << data->getName() << std::endl;
  std::cout<<"Betw ===>"<<data->getBetw()<<std::endl;
  auto fwwTag = data->getTag<ndn::lp::FwwTag>();
  if(fwwTag != nullptr )
     std::cout<<"FwwTag$$$$$$$$"<<*fwwTag<<std::endl;
}

} // namespace ns3
