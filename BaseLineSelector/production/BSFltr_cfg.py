import FWCore.ParameterSet.VarParsing as opts
import FWCore.ParameterSet.Config as cms 
import importlib
import os

#-------------------------------------------------------------------------------
#   Environment settings
#-------------------------------------------------------------------------------
CMSSW_BASE = os.environ['CMSSW_BASE']
dir_path   = "/src/AcAnalysis/BaseLineSelector" 

#-------------------------------------------------------------------------------
#   Options settings + Parsing, see python/optionsInit and python/OptionParser
#-------------------------------------------------------------------------------
options = opts.VarParsing ('analysis')

options.register('useMC',
    False,
    opts.VarParsing.multiplicity.singleton,
    opts.VarParsing.varType.bool,
    'Sample is mc or data')

options.register('year',
    "16",
    opts.VarParsing.multiplicity.singleton,
    opts.VarParsing.varType.string,
    'Which year')

options.register('Debug',
     0,
     opts.VarParsing.multiplicity.singleton,
     opts.VarParsing.varType.int,
     'Debugging output level' )

options.setDefault('maxEvents', -1 )
options.setDefault('inputFiles', "file:" + CMSSW_BASE + dir_path + '/test/test.root' )
options.parseArguments()

mysetting = importlib.import_module('AcAnalysis.BaseLineSelector.Precut_{}_cfi'.format( options.year ) )
print ">> Importing module AcAnalysis.BaseLineSelector.Precut_{}_cfi".format( options.year )
print ">> Running with [ Use MC: {0} | Year: {1} ]".format(options.useMC, options.year )
print ">> Dataset: {}".format( options.inputFiles )

#-------------------------------------------------------------------------------
#   Process Setup
#-------------------------------------------------------------------------------
process = cms.Process("Preselect")
process.options = cms.untracked.PSet(wantSummary=cms.untracked.bool(True))
process.load("FWCore.MessageService.MessageLogger_cfi")
if options.Debug :
    process.MessageLogger.cerr.FwkReport.reportEvery = 100

process.load('Configuration.EventContent.EventContent_cff')
process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

if options.useMC :
    process.GlobalTag.globaltag = mysetting.MCGlobalTag
else:
    process.GlobalTag.globaltag = mysetting.DataGlobalTag

print ">> Loading GlobalTag: {}".format( process.GlobalTag.globaltag )

#-------------------------------------------------------------------------------
#   Parsing 
#-------------------------------------------------------------------------------
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(options.maxEvents) )
process.source = cms.Source("PoolSource", fileNames=cms.untracked.vstring(options.inputFiles))
print '>> Finished basic setups...'

#-------------------------------------------------------------------------------
#   Settings for preselect
#-------------------------------------------------------------------------------
process.datafltr = cms.EDFilter(
        "BaseLineSelector",
        mysetting.commontool
        )

process.filterpath = cms.Path(
        process.datafltr
        )

process.edmOut = cms.OutputModule(
        "PoolOutputModule",
        fileName = cms.untracked.string( "Precut_{}.root".format( options.year ) ),

        outputCommands=cms.untracked.vstring(
            "keep *",
            "drop *_slimmedPhotons_*_*",
            "drop *_slimmedTaus_*_*"
            ),
        SelectEvents=cms.untracked.PSet(SelectEvents=cms.vstring('filterpath'))
        )

process.endPath = cms.EndPath(
        process.edmOut
        )
