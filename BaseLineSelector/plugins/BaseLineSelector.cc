#include "AcAnalysis/BaseLineSelector/interface/BaseLineSelector.h"
//
// constructors and destructor
//
using namespace std;
BaseLineSelector::BaseLineSelector(const edm::ParameterSet& iConfig) :
    _musrc( consumes<vector<pat::Muon> >( iConfig.getParameter<edm::InputTag>( "musrc" ) ) ),
    _elsrc( consumes<vector<pat::Electron> >( iConfig.getParameter<edm::InputTag>( "elsrc" ) ) ),
    _jetsrc( consumes<vector<pat::Jet> >( iConfig.getParameter<edm::InputTag>( "jetsrc" ) ) )
{
   //now do what ever initialization is needed
}


BaseLineSelector::~BaseLineSelector()
{

}

//
// member functions
//

// ------------ method called on each new Event  ------------
bool
BaseLineSelector::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
    iEvent.getByToken( _musrc, _muhandle );
    iEvent.getByToken( _elsrc, _elhandle );
    iEvent.getByToken( _jetsrc, _jethandle );
    cout<<_muhandle->size()<<endl;
    return true;
}

// ------------ method called once each stream before processing any runs, lumis or events  ------------
void
BaseLineSelector::beginStream(edm::StreamID)
{
}

// ------------ method called once each stream after processing all runs, lumis and events  ------------
void
BaseLineSelector::endStream() {
}

// ------------ method called when starting to processes a run  ------------
/*
void
BaseLineSelector::beginRun(edm::Run const&, edm::EventSetup const&)
{ 
}
*/
 
// ------------ method called when ending the processing of a run  ------------
/*
void
BaseLineSelector::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when starting to processes a luminosity block  ------------
/*
void
BaseLineSelector::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when ending the processing of a luminosity block  ------------
/*
void
BaseLineSelector::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
BaseLineSelector::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}
//define this as a plug-in
DEFINE_FWK_MODULE(BaseLineSelector);
