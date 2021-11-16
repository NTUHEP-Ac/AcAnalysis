#ifndef BASELINE_H
#define BASELINE_H
// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/stream/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/StreamID.h"

#include "DataFormats/Common/interface/Ptr.h"
#include "DataFormats/FWLite/interface/Handle.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Jet.h"

//
// class declaration
//

class BaseLineSelector : public edm::stream::EDFilter<> {
    public:
        explicit BaseLineSelector(const edm::ParameterSet&);
        ~BaseLineSelector();

        static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

    private:
        virtual void beginStream(edm::StreamID) override;
        virtual bool filter(edm::Event&, const edm::EventSetup&) override;
        virtual void endStream() override;

        /*------common memeber------*/
        const edm::EDGetTokenT<std::vector<pat::Muon> > _musrc;
        const edm::EDGetTokenT<std::vector<pat::Electron> > _elsrc;
        const edm::EDGetTokenT<std::vector<pat::Jet> > _jetsrc;
        edm::Handle<std::vector<pat::Muon> > _muhandle;
        edm::Handle<std::vector<pat::Electron> > _elhandle;
        edm::Handle<std::vector<pat::Jet> > _jethandle;
};

//
#endif
