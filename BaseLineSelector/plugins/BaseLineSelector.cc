#include "AcAnalysis/BaseLineSelector/interface/BaseLineSelector.h"
//
// constructors and destructor
//
using namespace std;
BaseLineSelector::BaseLineSelector(const edm::ParameterSet& iConfig) :
    _musrc( consumes<vector<pat::Muon> >( iConfig.getParameter<edm::InputTag>( "musrc" ) ) ),
    _elsrc( consumes<vector<pat::Electron> >( iConfig.getParameter<edm::InputTag>( "elsrc" ) ) ),
    _jetsrc( consumes<vector<pat::Jet> >( iConfig.getParameter<edm::InputTag>( "jetsrc" ) ) ),
    _Ldjet_Ptmin(iConfig.getParameter<double>("Ldjet_Ptmin")),
    _lep_nmin(iConfig.getParameter<int>("lep_nmin")),
    _lep_Ptmin(iConfig.getParameter<double>("lep_Ptmin"))
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
    edm::Handle<std::vector<pat::Muon> > _muhandle;
    edm::Handle<std::vector<pat::Electron> > _elhandle;
    edm::Handle<pat::JetCollection > _jethandle;
    iEvent.getByToken( _musrc, _muhandle );
    iEvent.getByToken( _elsrc, _elhandle );
    iEvent.getByToken( _jetsrc, _jethandle );
    
    //indicate whether corresponding condition passed or not.
    bool _jet_flag = false;
    bool _el_flag = false;
    bool _mu_flag = false;
    
    //Jet Section
    for(auto &jet : *_jethandle)
    {
        if(jet.pt() > _Ldjet_Ptmin)
        {
            _jet_flag = true;
            break;
        }
    }
    if(!_jet_flag)
    {
        return false;
    }
    
    
    //Leption Section
    
    int nlep = _elhandle->size() + _muhandle->size();
    if(nlep <= _lep_nmin)
    {
        return false;
    }
    
    //Lepton Subsection: Electron
    for(auto &e : *_elhandle)
    {
        if(e.pt() > _lep_Ptmin)
        {
            _el_flag = true;
            break;
        }
    }
    if(!_el_flag)
    {
        return false;
    }

    //Lepton Subsection: Muon
    for(auto &m : *_muhandle)
    {
        if(m.pt() > _lep_Ptmin)
        {
            _mu_flag = true;
            break;
        }
    }
    if(!_mu_flag)
    {
        return false;
    }
    
    
    //Rest condition 
    else
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
