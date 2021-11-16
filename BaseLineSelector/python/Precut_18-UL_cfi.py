import FWCore.ParameterSet.Config as cms

DataGlobalTag = '106X_dataRun2_v32'
MCGlobalTag   = '106X_upgrade2018_realistic_v15_L1v1'

commontool = cms.PSet(
        # source
        musrc = cms.InputTag( "slimmedMuons" ),
        elsrc = cms.InputTag( "slimmedElectrons"),
        
        jetsrc  = cms.InputTag( "slimmedJets"),
        jettype = cms.string('AK4PFchs')
        # customized cut
        # e.g. jetPt = cms.double(120),  
        )
