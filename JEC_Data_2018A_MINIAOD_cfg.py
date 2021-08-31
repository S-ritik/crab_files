# -*- coding: utf-8 -*-

import FWCore.ParameterSet.Config as cms
import sys

from RecoJets.Configuration.RecoPFJets_cff import *
from RecoJets.Configuration.RecoGenJets_cff import ak4GenJets, ak8GenJets
from RecoJets.JetProducers.SubJetParameters_cfi import SubJetParameters
from RecoJets.JetProducers.PFJetParameters_cfi import *
from RecoJets.JetProducers.GenJetParameters_cfi import *
from RecoJets.JetProducers.AnomalousCellParameters_cfi import *
from PhysicsTools.PatAlgos.producersLayer1.patCandidates_cff import *
from PhysicsTools.PatAlgos.selectionLayer1.jetSelector_cfi import selectedPatJets
from PhysicsTools.PatAlgos.tools.jetTools import *
from PhysicsTools.PatAlgos.patSequences_cff import *
from PhysicsTools.PatAlgos.patTemplate_cfg import *
from PhysicsTools.PatAlgos.tools.jetTools import *
from PhysicsTools.PatAlgos.slimming.metFilterPaths_cff import *


## Modified version of jetToolBox from https://github.com/cms-jet/jetToolbox
## Options for PUMethod: Puppi, CS, SK, CHS

# -*- coding: utf-8 -*-
import FWCore.ParameterSet.Config as cms

process = cms.Process("Combined")
#!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#! Conditions
#!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load("Configuration.EventContent.EventContent_cff")
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('RecoJets.Configuration.GenJetParticles_cff')
process.load('RecoJets.Configuration.RecoGenJets_cff')
process.load('RecoJets.JetProducers.TrackJetParameters_cfi')
process.load('RecoJets.JetProducers.PileupJetIDParams_cfi')

process.load("PhysicsTools.PatAlgos.producersLayer1.patCandidates_cff")
process.load("PhysicsTools.PatAlgos.selectionLayer1.selectedPatCandidates_cff")


from RecoJets.Configuration.GenJetParticles_cff import *

process.GlobalTag.globaltag = "106X_dataRun2_v32"
#process.GlobalTag.globaltag = "102X_upgrade2018_realistic_v20"
#process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:mc', '')

##-------------------- Import the JEC services -----------------------
process.load('JetMETCorrections.Configuration.DefaultJEC_cff')

from PhysicsTools.PatAlgos.tools.coreTools import *
process.load("PhysicsTools.PatAlgos.patSequences_cff")

#!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#! Input
#!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

inFiles = cms.untracked.vstring(
#'root://cmsxrootd.fnal.gov//store/mc/RunIIAutumn18MiniAOD/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15_ext3-v2/00000/7D55475A-931D-1F47-8BF9-905DD6DC15B8.root'
#'root://cmsxrootd.fnal.gov//store/mc/RunIIAutumn18MiniAOD/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15_ext2-v2/50000/FE475AA9-6572-E548-BF9B-A6DCD6B9BBA1.root'
#'root://cmsxrootd.fnal.gov//store/data/Run2018A/SingleMuon/MINIAOD/17Sep2018-v2/90000/6FEE6A9B-E03C-A14F-AD01-914C76D0A721.root'
# 'root://cmsxrootd.fnal.gov//store/data/Run2018D/EGamma/MINIAOD/12Nov2019_UL2018-v4/00000/03A46B18-077E-AC47-BB0E-AD94F8BD85CE.root'
#'root://cmsxrootd.fnal.gov//store/data/Run2018D/EGamma/MINIAOD/12Nov2019_UL2018-v4/00000/011BB257-AB2C-0940-A242-F6451B1EBA33.root'
# 'root://cmsxrootd.fnal.gov//store/data/Run2018D/MuonEG/MINIAOD/12Nov2019_UL2018_rsb-v1/20000/058F9A66-62A4-4C48-B358-BDD7E732F4EC.root'      
#cms-xrd-global.cern.ch
#'root://cms-xrd-global.cern.ch//store/data/Run2018D/EGamma/MINIAOD/12Nov2019_UL2018-v4/00000/011BB257-AB2C-0940-A242-F6451B1EBA33.root'    
'root://cms-xrd-global.cern.ch//store/data/Run2018D/MuonEG/MINIAOD/UL2018_MiniAODv2-v1/240000/08B3E323-4EC2-F74A-B88A-478AE22DE68C.root'
   )

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(2000))
#process.firstEvent = cms.untracked.PSet(input = cms.untracked.int32(5000))
process.source = cms.Source("PoolSource", fileNames = inFiles )


process.p = cms.Path()

#!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#! Services
#!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
process.load('FWCore.MessageLogger.MessageLogger_cfi')
process.MessageLogger.cerr.FwkReport.reportEvery = 100
process.load('CommonTools.UtilAlgos.TFileService_cfi')

process.TFileService = cms.Service("TFileService",
fileName = cms.string('hist_jerc_l5.root')             #largest data till April5,2016 
)

process.patJets.addTagInfos = True

from PhysicsTools.SelectorUtils.tools.vid_id_tools import *
# Electron IDs for AOD/MINIAOD
switchOnVIDElectronIdProducer(process, DataFormat.MiniAOD)

# define which IDs to produce
el_id_modules = [
##    "RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Spring16_GeneralPurpose_V1_cff"
    "RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Fall17_iso_V2_cff",
    "RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Fall17_noIso_V2_cff"
##    "RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Spring16_GeneralPurpose_V1_cff"
]
# Add them to the VID producer
for iModule in el_id_modules:

	setupAllVIDIdsInModule(process, iModule, setupVIDElectronSelection)

switchOnVIDPhotonIdProducer(process, DataFormat.MiniAOD)

pho_id_modules = [
	"RecoEgamma.PhotonIdentification.Identification.mvaPhotonID_Spring16_nonTrig_V1_cff",
	"RecoEgamma.PhotonIdentification.Identification.mvaPhotonID_Fall17_94X_V1p1_cff"
]

for iModule in pho_id_modules:

	setupAllVIDIdsInModule(process, iModule, setupVIDPhotonSelection)


from PhysicsTools.PatAlgos.tools.jetTools import updateJetCollection
deep_discriminators = ["pfMassDecorrelatedDeepBoostedDiscriminatorsJetTags:TvsQCD",
                       "pfMassDecorrelatedDeepBoostedDiscriminatorsJetTags:WvsQCD",
                       "pfMassDecorrelatedDeepBoostedDiscriminatorsJetTags:ZvsQCD",
                       
]
updateJetCollection(
   process,
   jetSource = cms.InputTag('slimmedJetsAK8'),
   pvSource = cms.InputTag('offlineSlimmedPrimaryVertices'),
   svSource = cms.InputTag('slimmedSecondaryVertices'),
   rParam = 0.8,
   labelName = 'SlimmedJetsAK8',
   jetCorrections = ('AK8PFPuppi', cms.vstring([]), 'None' ),
   btagDiscriminators = deep_discriminators 
)
#process.updatedPatJetsTransientCorrectedSlimmedJetsAK8.userData.userFloats.src = []

process.mcjets =  cms.EDAnalyzer('Leptop',

	 Data =  cms.untracked.bool(True),
	 MonteCarlo =  cms.untracked.bool(False),
         YEAR = cms.untracked.int32(2018),
         UltraLegacy =  cms.untracked.bool(True),                        
	 isReco = cms.untracked.bool(True),
 	 ReRECO = cms.untracked.bool(True),
	 SoftDrop_ON =  cms.untracked.bool(True),
 	 RootFileName = cms.untracked.string('rootuple_jerc_l5.root'),  #largest data till April5,2016

	 softdropmass  = cms.untracked.string("ak8PFJetsSoftDropMass"),#ak8PFJetsPuppiSoftDropMass"),#('ak8PFJetsPuppiSoftDropMass'),
	 tau1  = cms.untracked.string("NjettinessAK8Puppi:tau1"),#'NjettinessAK8Puppi:tau1'),
	 tau2  = cms.untracked.string("NjettinessAK8Puppi:tau2"),#'NjettinessAK8Puppi:tau2'),
	 tau3  = cms.untracked.string("NjettinessAK8Puppi:tau3"),#'NjettinessAK8Puppi:tau3'),
	 subjets  = cms.untracked.string('SoftDropPuppi'),#("SoftDrop"),#'SoftDropPuppi'),
#	 subjets = cms.untracked.string("slimmedJetsAK8PFPuppiSoftDropPacked"),
	 toptagger = cms.untracked.string("pfMassDecorrelatedDeepBoostedDiscriminatorsJetTags:TvsQCD"),
	 Wtagger = cms.untracked.string("pfMassDecorrelatedDeepBoostedDiscriminatorsJetTags:WvsQCD"),
	 Ztagger = cms.untracked.string("pfMassDecorrelatedDeepBoostedDiscriminatorsJetTags:ZvsQCD"),
	 
	 minPt = cms.untracked.double(25.),
         minGenPt = cms.untracked.double(15.),                        
	 maxEta = cms.untracked.double(3.),
         maxGenEta = cms.untracked.double(5.),
	 AK8PtCut = cms.untracked.double(180.),
         AK8GenPtCut = cms.untracked.double(150.),                        
	 

         Beamspot = cms.InputTag("offlineBeamSpot"),
         PrimaryVertices = cms.InputTag("offlineSlimmedPrimaryVertices"),
         SecondaryVertices = cms.InputTag("slimmedSecondaryVertices"),
	 slimmedAddPileupInfo = cms.InputTag("slimmedAddPileupInfo"),
	 PFMet = cms.InputTag("slimmedMETs"),
    	 GENMet  = cms.InputTag("genMetTrue","","SIM"),
         Generator = cms.InputTag("generator"),
  	
         PFRho = cms.InputTag("fixedGridRhoFastjetAll"),

         LHEEventProductInputTag = cms.InputTag('externalLHEProducer'),
         GenEventProductInputTag = cms.InputTag('generator'),

#	 PFJetsAK8 = cms.InputTag("slimmedJetsAK8"),
#	 PFJetsAK8 = cms.InputTag("selectedPatJetsAK8PFPuppiSoftDropPacked","SubJets","Combined"),
#	 PFJetsAK8 = cms.InputTag("selectedPatJetsAK8PFPuppi","","Combined"),
	 PFJetsAK8 = cms.InputTag("updatedPatJetsTransientCorrectedSlimmedJetsAK8"),#"","PAT"),
	 PFJetsAK4 = cms.InputTag("slimmedJets"),
	 GENJetAK8 = cms.InputTag("slimmedGenJetsAK8"),
	 GENJetAK4 = cms.InputTag("slimmedGenJets"),#,"","PAT"),
	 Muons = cms.InputTag("slimmedMuons"),#,"","PAT"),
#         src = cms.InputTag("slimmedMuonsUpdated"),#,"","PAT"), #need to check if properly done for UL from here : https://github.com/cms-sw/cmssw/blob/CMSSW_10_6_X/PhysicsTools/NanoAOD/python/muons_cff.py#L22
         EAFile_MiniIso = cms.FileInPath("PhysicsTools/NanoAOD/data/effAreaMuons_cone03_pfNeuHadronsAndPhotons_94X.txt"), 
         relative = cms.bool(True),
         pfCands = cms.InputTag("packedPFCandidates"),                        
         Electrons = cms.InputTag("slimmedElectrons"),#,"","PAT"),#("gsfElectrons"),
         Photons = cms.InputTag("slimmedPhotons"),#,"","PAT"),
	 GenParticles = cms.InputTag("prunedGenParticles"),#("prunedGenParticles"),#("packedGenParticles"),

         electronID_isowp90        = cms.string('mvaEleID-Fall17-iso-V2-wp90'),
         electronID_noisowp90      = cms.string('mvaEleID-Fall17-noIso-V2-wp90'),                      
         electronID_isowp80        = cms.string('mvaEleID-Fall17-iso-V2-wp80'),
         electronID_noisowp80      = cms.string('mvaEleID-Fall17-noIso-V2-wp80'),                        
	 jecL1FastFileAK4          = cms.string('Summer19UL18_RunA_V5_DATA/Summer19UL18_RunA_V5_DATA_L1FastJet_AK4PFchs.txt'),
         jecL1FastFileAK8          = cms.string('Summer19UL18_RunA_V5_DATA/Summer19UL18_RunA_V5_DATA_L1FastJet_AK8PFPuppi.txt'),
         jecL2RelativeFileAK4      = cms.string('Summer19UL18_RunA_V5_DATA/Summer19UL18_RunA_V5_DATA_L2Relative_AK4PFchs.txt'),
         jecL2RelativeFileAK8      = cms.string('Summer19UL18_RunA_V5_DATA/Summer19UL18_RunA_V5_DATA_L2Relative_AK8PFPuppi.txt'),
         jecL3AbsoluteFileAK4      = cms.string('Summer19UL18_RunA_V5_DATA/Summer19UL18_RunA_V5_DATA_L3Absolute_AK4PFchs.txt'),
         jecL3AbsoluteFileAK8      = cms.string('Summer19UL18_RunA_V5_DATA/Summer19UL18_RunA_V5_DATA_L3Absolute_AK8PFPuppi.txt'),
         jecL2L3ResidualFileAK4    = cms.string('Summer19UL18_RunA_V5_DATA/Summer19UL18_RunA_V5_DATA_L2L3Residual_AK4PFchs.txt'),
         jecL2L3ResidualFileAK8    = cms.string('Summer19UL18_RunA_V5_DATA/Summer19UL18_RunA_V5_DATA_L2L3Residual_AK8PFPuppi.txt'),

         PtResoFileAK4  = cms.string('Summer19UL18_JRV2_MC_PtResolution_AK4PFchs.txt'),
         PtResoFileAK8  = cms.string('Summer19UL18_JRV2_MC_PtResolution_AK8PFPuppi.txt'),
         PtSFFileAK4 = cms.string('Summer19UL18_JRV2_MC_SF_AK4PFchs.txt'),
         PtSFFileAK8 = cms.string('Summer19UL18_JRV2_MC_SF_AK8PFPuppi.txt'),
                                 
	 JECUncFileAK4 = cms.string("Summer19UL18_RunA_V5_DATA/Summer19UL18_RunA_V5_DATA_UncertaintySources_AK4PFchs.txt"),
	 JECUncFileAK8 = cms.string("Summer19UL18_RunA_V5_DATA/Summer19UL18_RunA_V5_DATA_UncertaintySources_AK8PFPuppi.txt"),

	 bits = cms.InputTag("TriggerResults","","HLT"),
         prescales = cms.InputTag("patTrigger","","RECO"),
         objects = cms.InputTag("slimmedPatTrigger")
)

#===== MET Filters ==

process.load('RecoMET.METFilters.primaryVertexFilter_cfi')
process.primaryVertexFilter.vertexCollection = cms.InputTag("offlineSlimmedPrimaryVertices")
process.load('RecoMET.METFilters.globalSuperTightHalo2016Filter_cfi')
process.load('CommonTools.RecoAlgos.HBHENoiseFilterResultProducer_cfi')
process.load('CommonTools.RecoAlgos.HBHENoiseFilter_cfi')
process.HBHENoiseFilterResultProducerNoMinZ = process.HBHENoiseFilterResultProducer.clone(minZeros = cms.int32(99999))
process.load('RecoMET.METFilters.EcalDeadCellTriggerPrimitiveFilter_cfi')

process.load('RecoMET.METFilters.BadPFMuonFilter_cfi')
process.BadPFMuonFilter.muons = cms.InputTag("slimmedMuons")
process.BadPFMuonFilter.PFCandidates = cms.InputTag("packedPFCandidates")
process.BadPFMuonFilter.vtx = cms.InputTag("offlineSlimmedPrimaryVertices") 
process.BadPFMuonFilter.taggingMode = cms.bool(True)

process.load('RecoMET.METFilters.BadPFMuonDzFilter_cfi')
process.BadPFMuonDzFilter.muons = cms.InputTag("slimmedMuons")
process.BadPFMuonDzFilter.PFCandidates = cms.InputTag("packedPFCandidates")
process.BadPFMuonDzFilter.vtx = cms.InputTag("offlineSlimmedPrimaryVertices")
process.BadPFMuonDzFilter.taggingMode = cms.bool(True)

process.load('RecoMET.METFilters.BadChargedCandidateFilter_cfi')
process.BadChargedCandidateFilter.muons = cms.InputTag("slimmedMuons")
process.BadChargedCandidateFilter.PFCandidates = cms.InputTag("packedPFCandidates")

process.load('RecoMET.METFilters.eeBadScFilter_cfi')
process.eeBadScFilter.EERecHitSource = cms.InputTag('reducedEgamma','reducedEERecHits')

process.load('RecoMET.METFilters.ecalBadCalibFilter_cfi')

process.RECOSIMoutput = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string('eventoutput.root'),
    outputCommands = process.RECOSIMEventContent.outputCommands,
    splitLevel = cms.untracked.int32(0)
)

process.allMetFilterPaths=cms.Sequence(process.primaryVertexFilter*process.globalSuperTightHalo2016Filter*process.HBHENoiseFilter*process.HBHENoiseIsoFilter*process.EcalDeadCellTriggerPrimitiveFilter*process.BadPFMuonFilter*process.BadPFMuonDzFilter*process.ecalBadCalibFilter)

process.jetSeq=cms.Sequence(process.patJetCorrFactorsSlimmedJetsAK8+process.updatedPatJetsSlimmedJetsAK8+process.patJetCorrFactorsTransientCorrectedSlimmedJetsAK8+process.pfDeepBoostedJetTagInfosSlimmedJetsAK8+process.pfMassDecorrelatedDeepBoostedJetTagsSlimmedJetsAK8+process.pfMassDecorrelatedDeepBoostedDiscriminatorsJetTagsSlimmedJetsAK8+process.updatedPatJetsTransientCorrectedSlimmedJetsAK8)

process.p = cms.Path(process.egmPhotonIDSequence* 
 		     process.HBHENoiseFilterResultProducer*process.HBHENoiseFilterResultProducerNoMinZ*
		     process.allMetFilterPaths*
#		     process.egmGsfElectronIDSequence*
		     process.jetSeq *
		     process.mcjets)

process.schedule = cms.Schedule(process.p)

process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(False) )
process.options.allowUnscheduled = cms.untracked.bool(True)
