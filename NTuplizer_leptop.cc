// -*- C++ -*-
//
// Package:    Run2_2016/TopplusB
// Class:      TopplusB
// 
/**\class TopplusB TopplusB.cc Run2_2016/TopplusB/plugins/TopplusB.cc
   
   Description: [one line class summary]
   
   Implementation:
   [Notes on implementation]
*/
//
// Original Author:  Suman Chatterjee
//         Created:  Thu, 31 Oct 2019 16:22:44 GMT
// Modified by Debarati Roy
//

// system include files-
#include <memory>
// user include files
#include "RecoEgamma/EgammaTools/interface/EffectiveAreas.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/global/EDProducer.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"
#include "DataFormats/JetReco/interface/PFJet.h"
#include "DataFormats/JetReco/interface/CaloJet.h"
#include "DataFormats/JetReco/interface/CaloJetCollection.h"
#include "DataFormats/METReco/interface/PFMET.h"
#include "DataFormats/METReco/interface/PFMETCollection.h"
#include "DataFormats/METReco/interface/MET.h"
#include "DataFormats/METReco/interface/CaloMET.h"
#include "DataFormats/METReco/interface/METCollection.h"
#include "DataFormats/METReco/interface/CaloMETCollection.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/METReco/interface/GenMET.h"
#include "DataFormats/METReco/interface/GenMETFwd.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "SimDataFormats/JetMatching/interface/JetFlavourInfo.h"
#include "SimDataFormats/JetMatching/interface/JetFlavourInfoMatching.h"
#include "DataFormats/PatCandidates/interface/PackedGenParticle.h"
#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/JetReco/interface/PFJetCollection.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/HcalRecHit/interface/HcalRecHitCollections.h"
#include "DataFormats/JetReco/interface/JetID.h"
#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TTree.h"
#include "TAxis.h"
#include "CLHEP/Vector/LorentzVector.h"
#include "TRandom.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectronFwd.h"
#include "DataFormats/GsfTrackReco/interface/GsfTrack.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonSelectors.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenRunInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#include "JetMETCorrections/Objects/interface/JetCorrector.h"
#include "JetMETCorrections/Objects/interface/JetCorrectionsRecord.h"
#include "GeneratorInterface/Pythia8Interface/plugins/ReweightUserHooks.h"
#include "fastjet/contrib/SoftDrop.hh"
#include "fastjet/contrib/Nsubjettiness.hh"
#include <string>
#include <iostream>
#include <fstream>
#include "DataFormats/EgammaCandidates/interface/Photon.h"
#include "DataFormats/EgammaCandidates/interface/PhotonFwd.h"
#include "DataFormats/HcalDigi/interface/HcalDigiCollections.h"
#include "DataFormats/HcalDetId/interface/HcalDetId.h"
#include "CalibFormats/HcalObjects/interface/HcalCoderDb.h"
#include "CalibFormats/HcalObjects/interface/HcalCalibrations.h"
#include "CalibFormats/HcalObjects/interface/HcalDbService.h"
#include "CalibFormats/HcalObjects/interface/HcalDbRecord.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "JetMETCorrections/JetCorrector/interface/JetCorrector.h"
#include "JetMETCorrections/Objects/interface/JetCorrectionsRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
#include "HLTrigger/HLTcore/interface/HLTPrescaleProvider.h"
#include "FWCore/Utilities/interface/typelookup.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include  "FWCore/Common/interface/TriggerNames.h"
#include "FWCore/Common/interface/TriggerResultsByName.h"
#include "FWCore/Utilities/interface/StreamID.h"
#include "FWCore/ParameterSet/interface/FileInPath.h"
#include "RecoEgamma/ElectronIdentification/interface/ElectronMVAEstimatorRun2.h"
#include "L1Trigger/GlobalTriggerAnalyzer/interface/L1GtTrigReportEntry.h"
#include "L1Trigger/GlobalTriggerAnalyzer/interface/L1GtTrigReport.h"
#include "CondFormats/L1TObjects/interface/L1GtTriggerMenu.h"
#include "CondFormats/DataRecord/interface/L1GtTriggerMenuRcd.h"
#include "JetMETCorrections/Modules/interface/JetResolution.h"
#include "CondFormats/JetMETObjects/interface/JetResolutionObject.h"
#include <FWCore/Framework/interface/EventSetup.h>
#include <FWCore/Framework/interface/ESHandle.h>
#include "FWCore/Utilities/interface/typelookup.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#include "SimDataFormats/GeneratorProducts/interface/PdfInfo.h"
#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenRunInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/LHERunInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/PatCandidates/interface/PackedGenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "CondFormats/BTauObjects/interface/BTagCalibration.h"
#include "CondFormats/BTauObjects/interface/BTagEntry.h"
#include "CondFormats/BTauObjects/interface/BTagCalibration.h"
#include "CondTools/BTau/interface/BTagCalibrationReader.h"
#include "fastjet/Selector.hh"
#include "fastjet/PseudoJet.hh"
#include "fastjet/JetDefinition.hh"
#include "fastjet/ClusterSequence.hh"
#include <fastjet/GhostedAreaSpec.hh>
#include "fastjet/GhostedAreaSpec.hh"
#include "fastjet/tools/Filter.hh"
#include "fastjet/tools/Pruner.hh"
#include "fastjet/tools/MassDropTagger.hh"
#include "fastjet/tools/JetMedianBackgroundEstimator.hh"
#include "fastjet/tools/GridMedianBackgroundEstimator.hh"
#include "fastjet/tools/Subtractor.hh"
#include "fastjet/Selector.hh"
#include "fastjet/tools/Subtractor.hh"

// Rochester correction for muons //
#include "RoccoR.h"
//#include "RoccoR.cc"

# include <vector>


using namespace std;
using namespace edm;
using namespace reco;  
using namespace CLHEP;
using namespace trigger;
using namespace math;
using namespace fastjet;
using namespace fastjet::contrib;

const float mu_mass = 0.105658;
const float el_mass = 0.000511;
const float pival = acos(-1.);

static const int nsrc = 28;
const char* jecsrcnames[nsrc] = {
  "AbsoluteStat", "AbsoluteScale","AbsoluteMPFBias", 
  "FlavorQCD", "Fragmentation", 
  "PileUpDataMC",  "PileUpPtBB", "PileUpPtEC1", "PileUpPtEC2", "PileUpPtHF",
  "PileUpPtRef",
  "RelativeFSR", "RelativeJEREC1", "RelativeJEREC2", "RelativeJERHF",
  "RelativePtBB", "RelativePtEC1", "RelativePtEC2", "RelativePtHF", 
  "RelativeBal", "RelativeSample", "RelativeStatEC", "RelativeStatFSR", "RelativeStatHF", 
  "SinglePionECAL", "SinglePionHCAL","TimePtEta",
  "Total"
};
const int njecmcmx = 2*nsrc + 1 ;
const int nomassbins = 200 ;
double massbins[nomassbins+1] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,192,193,194,195,196,197,198,199,200}; 
const int norhobins = 51 ;
double rhobins[norhobins+1] = {0.0001,0.00012,0.000144,0.0001728,0.00020736,0.000248832,0.000298598,0.000358318,0.000429982,0.000515978,0.000619174,0.000743008,0.00089161,0.00106993,0.00128392,0.0015407,0.00184884,0.00221861,0.00266233,0.0031948,0.00383376,0.00460051,0.00552061,0.00662474,0.00794968,0.00953962,0.0114475,0.0137371,0.0164845,0.0197814,0.0237376,0.0284852,0.0341822,0.0410186,0.0492224,0.0590668,0.0708802,0.0850562,0.102067,0.122481,0.146977,0.176373,0.211647,0.253977,0.304772,0.365726,0.438871,0.526646,0.631975,0.75837,0.910044,1.09205};
double logrhobins[norhobins+1] = {-0.088059,0.0942625,0.276584,0.458906,0.641227,0.823549,1.00587,1.18819,1.37051,1.55283,1.73516,1.91748,2.0998,2.28212,2.46444,2.64676,2.82909,3.01141,3.19373,3.37605,3.55837,3.74069,3.92302,4.10534,4.28766,4.46998,4.6523,4.83462,5.01694,5.19927,5.38159,5.56391,5.74623,5.92855,6.11087,6.2932,6.47552,6.65784,6.84016,7.02248,7.2048,7.38712,7.56945,7.75177,7.93409,8.11641,8.29873,8.48105,8.66338,8.8457,9.02802,9.21034};
double width = 1.2;

struct triggervar{
  TLorentzVector  trg4v;
  bool		  both;
  bool            level1;
  bool            highl;
  int             ihlt;
  int             prescl;
  int             pdgId;
};

int getbinid(double val, int nbmx, double* array) {
  if (val<array[0]) return -2;
  for (int ix=0; ix<=nbmx; ix++) {
    if (val < array[ix]) return ix-1;
  }
  return -3;
}

double theta_to_eta(double theta) { return -log(tan(theta/2.)); }

double PhiInRange(const double& phi) {
  double phiout = phi;
  if( phiout > 2*M_PI || phiout < -2*M_PI) {
    phiout = fmod( phiout, 2*M_PI);
  }
  if (phiout <= -M_PI) phiout += 2*M_PI;
  else if (phiout >  M_PI) phiout -= 2*M_PI;
  return phiout;
}

double delta2R(double eta1, double phi1, double eta2, double phi2) {
  return sqrt(pow(eta1 - eta2,2) +pow(PhiInRange(phi1 - phi2),2));
}

double diff_func(double f1, double f2){
  double ff = pow(f1-f2,2)*1./pow(max(f1+f2,0.000001),2);
  return ff;
}


TLorentzVector productX(TLorentzVector X, TLorentzVector Y, float pro1, float pro2)
{
  float b1, b2, b3;
  float c1, c2, c3;
  
  b1 = X.Px();
  b2 = X.Py();
  b3 = X.Pz();
  
  c1 = Y.Px();
  c2 = Y.Py();
  c3 = Y.Pz();
  
  float d1, d2, e1, e2, X1, X2;
  
  X1 = pro1;
  X2 = pro2;
  
  d1 = (c2*X1 - b2*X2)*1./(b1*c2 - b2*c1);
  d2 = (c1*X1 - b1*X2)*1./(b2*c1 - b1*c2);
  e1 = (b2*c3 - b3*c2)*1./(b1*c2 - b2*c1);
  e2 = (b1*c3 - b3*c1)*1./(b2*c1 - b1*c2);
  
  float A, B, C;
  A = (e1*e1 + e2*e2+ 1);
  B = 2*(d1*e1 + d2*e2);
  C = d1*d1 + d2*d2 - 1;
  
  float sol;
  
  if((pow(B,2) - (4*A*C)) < 0){
    sol = -1*B/(2*A);
    
    float A1, A2, A3;
    A3 = sol;
    A1 = d1 + e1*A3;
    A2 = d2 + e2*A3;
    
    TLorentzVector vec4;
    vec4.SetPxPyPzE(A1,A2,A3,0);
    return vec4;
  }
  else{
    float sol1 = (-1*B+sqrt((pow(B,2) - (4*A*C))))*1./(2*A);
    float sol2 =  (-1*B-sqrt((pow(B,2) - (4*A*C))))*1./(2*A);
    (sol1>sol2)?sol=sol1:sol=sol2;
    
    float A1, A2, A3;
    A3 = sol;
    A1 = d1 + e1*A3;
    A2 = d2 + e2*A3;
    
    TLorentzVector vec4;
    vec4.SetPxPyPzE(A1,A2,A3,0);
    return vec4;;
  }
}

struct JetIDVars
{
  float NHF, NEMF, MUF, CHF, CEMF;
  int NumConst, NumNeutralParticle, CHM;
};

bool Muon_TightID(bool muonisGL,bool muonisPF, float muonchi, float muonhit, float muonmst,
		  float muontrkvtx, float muondz, float muonpixhit, float muontrklay){
  bool tightid = false;
  if(muonisGL && muonisPF){
    if(muonchi<10 && muonhit>0 && muonmst>1){
      if(fabs(muontrkvtx)<0.2 && fabs(muondz)<0.5){
	if(muonpixhit>0 && muontrklay>5){
	  tightid = true;
	}
      }
    }
  }
  return tightid;
}

bool getJetID(JetIDVars vars, string jettype="CHS", int year=2018, double eta=0, bool tightLepVeto=true, bool UltraLegacy=false){
  
  //https://twiki.cern.ch/twiki/bin/viewauth/CMS/JetID
  
  if (jettype!="CHS" && jettype!="PUPPI"){
    cout<<"Don't know your jet type! I know only CHS & PUPPI :D"<<endl;
    return false;
  }
  
  float NHF, NEMF, MUF, CHF, CEMF;
  int NumConst, NumNeutralParticle, CHM;
  
  NHF = vars.NHF; 
  NEMF = vars.NEMF;
  MUF = vars.MUF;
  CHF = vars.CHF;
  CEMF = vars.CEMF;
  NumConst = vars.NumConst;
  NumNeutralParticle = vars.NumNeutralParticle;
  CHM = vars.CHM;
  
  bool JetID = false;
  
  if(!UltraLegacy){
    
    if(year==2018 && jettype=="CHS"){
      
      JetID = ( (fabs(eta)<=2.6 && CEMF<0.8 && CHM>0 && CHF>0 && NumConst>1 && NEMF<0.9 && MUF <0.8 && NHF < 0.9 && tightLepVeto ) || (fabs(eta)<=2.6 && CHM>0 && CHF>0 && NumConst>1 && NEMF<0.9 && NHF < 0.9 && !tightLepVeto ) || (fabs(eta)>2.6 && fabs(eta)<=2.7 && CEMF<0.8 && CHM>0 && NEMF<0.99 && MUF <0.8 && NHF < 0.9 && tightLepVeto ) || (fabs(eta)>2.6 && fabs(eta)<=2.7 && CHM>0 && NEMF<0.99 && NHF < 0.9 && !tightLepVeto ) || (fabs(eta)>2.7 && fabs(eta)<=3.0 && NEMF>0.02 && NEMF<0.99 && NumNeutralParticle>2) || (fabs(eta)>3.0 && NEMF<0.90 && NHF>0.2 && NumNeutralParticle>10));
    }
    
    if(year==2018 && jettype=="PUPPI"){
      
      JetID = ( (fabs(eta)<=2.6 && CEMF<0.8 && CHM>0 && CHF>0 && NumConst>1 && NEMF<0.9 && MUF <0.8 && NHF < 0.9 && tightLepVeto ) || (fabs(eta)<=2.6 && CHM>0 && CHF>0 && NumConst>1 && NEMF<0.9 && NHF < 0.9 && !tightLepVeto ) || (fabs(eta)>2.6 && fabs(eta)<=2.7 && CEMF<0.8 && NEMF<0.99 && MUF <0.8 && NHF < 0.9 && tightLepVeto ) || (fabs(eta)>2.6 && fabs(eta)<=2.7 && NEMF<0.99 && NHF < 0.9 && !tightLepVeto ) || (fabs(eta)<=3.0 && NHF<0.99) || (fabs(eta)>3.0 && NEMF<0.90 && NHF>0.02 && NumNeutralParticle>2 && NumNeutralParticle<15));
    }
    
    if(year==2017 && jettype=="CHS"){
      
      JetID = ( (fabs(eta)<=2.4 && CEMF<0.8 && CHM>0 && CHF>0 && NumConst>1 && NEMF<0.9 && MUF <0.8 && NHF < 0.9 && tightLepVeto ) || (fabs(eta)<=2.4 && CHM>0 && CHF>0 && NumConst>1 && NEMF<0.9 && NHF < 0.9 && !tightLepVeto ) || (fabs(eta)>2.4 && fabs(eta)<=2.7 &&  NumConst>1 && NEMF<0.9 && MUF <0.8 && NHF < 0.9 && tightLepVeto ) || (fabs(eta)>2.4 && fabs(eta)<=2.7 &&  NumConst>1 && NEMF<0.9 && NHF < 0.9 && !tightLepVeto ) || (fabs(eta)>2.7 && fabs(eta)<=3.0 && NEMF>0.02 && NEMF<0.99 && NumNeutralParticle>2) || (fabs(eta)>3.0 && NEMF<0.90 && NHF>0.02 && NumNeutralParticle>10));
    }
    
    if(year==2017 && jettype=="PUPPI"){
      
      JetID = ( (fabs(eta)<=2.4 && CEMF<0.8 && CHM>0 && CHF>0 && NumConst>1 && NEMF<0.9 && MUF <0.8 && NHF < 0.9 && tightLepVeto ) || (fabs(eta)<=2.4 && CHM>0 && CHF>0 && NumConst>1 && NEMF<0.9 && NHF < 0.9 && !tightLepVeto ) ||
		(fabs(eta)>2.4 && fabs(eta)<=2.7 &&  NumConst>1 && NEMF<0.9 && MUF <0.8 && NHF < 0.9 && tightLepVeto ) || (fabs(eta)>2.4 && fabs(eta)<=2.7 &&  NumConst>1 && NEMF<0.9 && NHF < 0.9 && !tightLepVeto ) || (fabs(eta)>2.7 && fabs(eta)<=3.0 && NHF<0.99) || (fabs(eta)>3.0 && NEMF<0.90 && NHF>0.02 && NumNeutralParticle>2 && NumNeutralParticle<15));
    }

    if(year==2016 && jettype=="CHS"){
      
      JetID = ( (fabs(eta)<=2.4 && CEMF<0.90 && CHM>0 && CHF>0 && NumConst>1 && NEMF<0.9 && MUF <0.8 && NHF < 0.9 && tightLepVeto ) || (fabs(eta)<=2.4 && CEMF<0.99 && CHM>0 && CHF>0 && NumConst>1 && NEMF<0.9 && NHF < 0.9  && !tightLepVeto ) || (fabs(eta)>2.4 && fabs(eta)<=2.7 && NumConst>1 && NEMF<0.9 && MUF <0.8 && NHF < 0.9 && tightLepVeto ) || (fabs(eta)>2.4 && fabs(eta)<=2.7 && NumConst>1 && NEMF<0.9 && NHF < 0.9 && !tightLepVeto ) || (fabs(eta)>2.7 && fabs(eta)<=3.0 && NEMF>0.01 && NHF<0.98 && NumNeutralParticle>2) || (fabs(eta)>3.0 && NEMF<0.90 && NumNeutralParticle>10));
    }
    
    if(year==2016 && jettype=="PUPPI"){
      
      JetID = ( (fabs(eta)<=2.4 && CEMF<0.9 && CHM>0 && CHF>0 && NumConst>1 && NEMF<0.9 && MUF <0.8 && NHF < 0.9 && tightLepVeto ) || (fabs(eta)<=2.4 && CEMF<0.99 && CHM>0 && CHF>0 && NumConst>1 && NEMF<0.9 && NHF < 0.9 && !tightLepVeto ) || (fabs(eta)>2.4 && fabs(eta)<=2.7 && NumConst>1 && NEMF<0.9 && MUF <0.8 && NHF < 0.9 && tightLepVeto ) || (fabs(eta)>2.4 && fabs(eta)<=2.7 && NumConst>1 && NEMF<0.9 && NHF < 0.9 && !tightLepVeto ));
      if(fabs(eta)>2.7) { JetID = false; }
    }
  }
  
  else {
    
    if(year==2017||year==2018){
      
      if(jettype=="CHS"){
	
	JetID = ( fabs(eta)<=2.6 && CEMF<0.8 && CHM>0 && CHF>0 && NumConst>1 && NEMF<0.9 && MUF <0.8 && NHF < 0.9 && tightLepVeto ) || ( fabs(eta)<=2.6 && CHM>0 && CHF>0 && NumConst>1 && NEMF<0.9 && NHF < 0.9 && !tightLepVeto ) || ( fabs(eta)>2.6 && fabs(eta)<=2.7 && CEMF<0.8 && CHM>0 && NEMF<0.99 && MUF <0.8 && NHF < 0.9 ) || ( fabs(eta)>2.6 && fabs(eta)<=2.7 && CHM>0 && NEMF<0.99 && NHF < 0.9 ) || ( fabs(eta)>2.7 && fabs(eta)<=3.0 && NEMF>0.01 && NEMF<0.99 && NumNeutralParticle>1 ) || ( fabs(eta)>3.0 && NEMF<0.90 && NHF>0.2 && NumNeutralParticle>10) ;
      }
      
      if(jettype=="PUPPI"){
	
	JetID =  ( fabs(eta)<=2.6 && CEMF<0.8 && CHM>0 && CHF>0 && NumConst>1 && NEMF<0.9 && MUF <0.8 && NHF < 0.9 && tightLepVeto ) || ( fabs(eta)<=2.6 && CHM>0 && CHF>0 && NumConst>1 && NEMF<0.9 && NHF < 0.9 && !tightLepVeto ) || ( fabs(eta)>2.6 && fabs(eta)<=2.7 && CEMF<0.8 && NEMF<0.99 && MUF <0.8 && NHF < 0.9 && tightLepVeto ) || ( fabs(eta)>2.6 && fabs(eta)<=2.7 && NEMF<0.99 && NHF < 0.9 && !tightLepVeto ) || ( fabs(eta)>2.7 && fabs(eta)<=3.0 && NHF<0.9999 ) ||( fabs(eta)>3.0 && NEMF<0.90 && NumNeutralParticle>2 ) ;
      }
      // there is a inconsistency between table & lines in https://twiki.cern.ch/twiki/bin/view/CMS/JetID13TeVUL
      // table is chosen as it is consistent with the slides https://indico.cern.ch/event/937597/contributions/3940302/attachments/2073315/3481068/ULJetID_UL17_UL18_AK4PUPPI.pdf 
	   }
    
    if(year==2016){
      
      if(jettype=="CHS"){
	
	JetID =  ( fabs(eta)<=2.4 && CEMF<0.8 && CHM>0 && CHF>0 && NumConst>1 && NEMF<0.9 && MUF <0.8 && NHF < 0.9 && tightLepVeto ) || ( fabs(eta)<=2.4 && CHM>0 && CHF>0 && NumConst>1 && NEMF<0.9 && NHF < 0.9 && !tightLepVeto ) || ( fabs(eta)>2.4 && fabs(eta)<=2.7 && NEMF<0.99 && NHF < 0.9 ) || ( fabs(eta)>2.7 && fabs(eta)<=3.0 && NEMF>0.0 && NEMF<0.99 && NHF<0.9 && NumNeutralParticle>1 ) || ( fabs(eta)>3.0 && NEMF<0.90 && NHF>0.2 && NumNeutralParticle>10) ;
	
      }
      
      if(jettype=="PUPPI"){
	
	JetID = ( fabs(eta)<=2.4 && CEMF<0.8 && CHM>0 && CHF>0 && NumConst>1 && NEMF<0.9 && MUF <0.8 && NHF < 0.9 && tightLepVeto ) || ( fabs(eta)<=2.4 && CHM>0 && CHF>0 && NumConst>1 && NEMF<0.9 && NHF < 0.9 && !tightLepVeto ) || ( fabs(eta)>2.4 && fabs(eta)<=2.7 && NEMF<0.99 && NHF < 0.98 ) || ( fabs(eta)>2.7 && fabs(eta)<=3.0 && NumNeutralParticle>=1 ) || ( fabs(eta)>3.0 && NEMF<0.90 && NumNeutralParticle>2  ) ;
      }
    }	
  }
  
  return JetID;
  
}

TLorentzVector LeptonJet_subtraction(vector<auto> leps, pat::Jet jet, TLorentzVector jet4v){
	
  TLorentzVector newjet4v;
  newjet4v = jet4v;
	
  if (leps.size()>0) {                                                                                           
    for (unsigned int ilep = 0; ilep<leps.size(); ilep++) {
	  
      bool lepmember = false;
			
      for(unsigned int jd = 0 ; jd < leps[ilep].numberOfSourceCandidatePtrs() ; ++jd) {
				
	if(leps[ilep].sourceCandidatePtr(jd).isNonnull() && leps[ilep].sourceCandidatePtr(jd).isAvailable()){
	  const reco::Candidate* jcand = leps[ilep].sourceCandidatePtr(jd).get();
				
	  for(unsigned int ic = 0 ; ic < jet.numberOfSourceCandidatePtrs() ; ++ic) {  
					
	    if(jet.sourceCandidatePtr(ic).isNonnull() && jet.sourceCandidatePtr(ic).isAvailable()){
	      const reco::Candidate* icand = jet.sourceCandidatePtr(ic).get();
	      if (delta2R(jcand->eta(),jcand->phi(),icand->eta(),icand->phi()) < 0.00001)    
		{
		  TLorentzVector tmpvec(jcand->px(),jcand->py(),jcand->pz(),jcand->energy());
		  newjet4v = jet4v - tmpvec;
		  lepmember = true; 
		  break;
		}
	    }
	  }		
				
	}
								
      }//jd
			
      if(lepmember) break;
			
    }//ilep
  }
    
  return newjet4v;
}

//class declaration
//
class Leptop : public edm::EDAnalyzer {
public:
  explicit Leptop(const edm::ParameterSet&);
  ~Leptop();
  
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
  
  
private:
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
  virtual void endJob() ;
  
  virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
  virtual void endRun(edm::Run const&, edm::EventSetup const&);
  virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  void fillmetarray();
  // ----------member data ---------------------------
  int Nevt;
  int ncnt;
  bool isData;
  bool isMC;
  int year;
  bool isUltraLegacy;
  bool isSoftDrop;
  bool read_btagSF;
  bool add_prefireweights;
  bool store_electron_scalnsmear, store_electron_addvariabs;

  uint nPDFsets;

  std::string theRootFileName;
  std::string theHLTTag;
  std::string softdropmass;
  std::string tau1;
  std::string tau2;
  std::string tau3;
  std::string subjets;
  std::string toptagger_DAK8;
  std::string Wtagger_DAK8;
  std::string Ztagger_DAK8;
  std::string toptagger_PNet;
  std::string Wtagger_PNet;
  
  int iTag;
  int iTagMET;
  double jtptthr;
  double minPt;
  double minGenPt;
  double maxEta;
  double maxgenEta;
  double AK8PtCut;
  double AK8GenPtCut;
  
  double beta ;
  double z_cut;
  
  edm::EDGetTokenT<double> tok_Rho_;
  edm::EDGetTokenT<reco::BeamSpot> tok_beamspot_;
  edm::EDGetTokenT<reco::VertexCollection> tok_primaryVertices_;
  edm::EDGetTokenT<reco::VertexCompositePtrCandidateCollection> tok_sv;
  edm::EDGetTokenT<pat::METCollection>tok_mets_, tok_mets_PUPPI_;
  edm::EDGetTokenT<pat::PackedCandidateCollection>tok_pfcands_;
  edm::EDGetTokenT<reco::GenMETCollection>tok_genmets_;
  edm::EDGetTokenT<edm::View<pat::Jet>>tok_pfjetAK8s_;
  bool relative_;
  std::unique_ptr<EffectiveAreas> ea_miniiso_;
  edm::EDGetTokenT<reco::GenJetCollection>tok_genjetAK8s_;
  edm::EDGetTokenT<edm::View<pat::Jet>>tok_pfjetAK4s_;
  edm::EDGetTokenT<reco::GenJetCollection>tok_genjetAK4s_;
  edm::EDGetTokenT<std::vector<reco::GenParticle>>tok_genparticles_;
  edm::EDGetTokenT<reco::JetFlavourInfoMatchingCollection> jetFlavourInfosToken_;
  edm::EDGetTokenT<HepMCProduct> tok_HepMC ;
  edm::EDGetTokenT<GenEventInfoProduct> tok_wt_;
  edm::EDGetTokenT<LHEEventProduct> lheEventProductToken_;
  edm::EDGetTokenT<edm::View<pat::Muon>> tok_muons_;
  edm::EDGetTokenT<edm::View<pat::Electron>> tok_electrons_;
  edm::EDGetTokenT<edm::View<pat::Photon>>tok_photons_;
  edm::EDGetTokenT<std::vector<PileupSummaryInfo> > pileup_;
  
  edm::EDGetTokenT<edm::TriggerResults> triggerBits_;
  edm::EDGetTokenT<pat::TriggerObjectStandAloneCollection> triggerObjects_;
  edm::EDGetTokenT<pat::PackedTriggerPrescales> triggerPrescales_;

  edm::EDGetTokenT< double > prefweight_token;
  edm::EDGetTokenT< double > prefweightup_token;
  edm::EDGetTokenT< double > prefweightdown_token;
  
  TFile* theFile;
  
  TTree* T1;
  TTree* T2;
  // HLTConfigProvider hltConfig_;
  
  unsigned ievt;
  
  static const int njetmx = 20; 
  static const int njetmxAK8 =10;
  static const int npartmx = 50; 
  
  int irunold;
  int irun, ilumi, ifltr, nprim, nprimi, ibrnch;
  double Generator_weight;
  double weights[njetmx];
  
  double Rho ;
  
  double prefiringweight, prefiringweightup, prefiringweightdown;

  int npfjetAK8;
  
  float pfjetAK8pt[njetmxAK8], pfjetAK8y[njetmxAK8], pfjetAK8eta[njetmxAK8], pfjetAK8phi[njetmxAK8], pfjetAK8mass[njetmxAK8];
  
  bool pfjetAK8jetID_tightlepveto[njetmxAK8], pfjetAK8jetID[njetmxAK8];
  
  float pfjetAK8btag_DeepCSV[njetmxAK8];
  float pfjetAK8DeepTag_DAK8_TvsQCD[njetmxAK8], pfjetAK8DeepTag_DAK8_WvsQCD[njetmxAK8], pfjetAK8DeepTag_DAK8_ZvsQCD[njetmxAK8]; 
  float pfjetAK8DeepTag_PNet_TvsQCD[njetmxAK8], pfjetAK8DeepTag_PNet_WvsQCD[njetmxAK8];
  
  float pfjetAK8CHF[njetmxAK8], pfjetAK8NHF[njetmxAK8], pfjetAK8MUF[njetmxAK8], pfjetAK8PHF[njetmxAK8], pfjetAK8CEMF[njetmxAK8], pfjetAK8NEMF[njetmxAK8], pfjetAK8EEF[njetmxAK8], pfjetAK8HFHF[njetmxAK8], /*pfjetAK8HFEMF[njetmxAK8],*/ pfjetAK8HOF[njetmxAK8];
  int pfjetAK8CHM[njetmxAK8], pfjetAK8NHM[njetmxAK8], pfjetAK8MUM[njetmxAK8], pfjetAK8PHM[njetmxAK8], pfjetAK8Neucons[njetmxAK8], pfjetAK8Chcons[njetmxAK8], pfjetAK8EEM[njetmxAK8], pfjetAK8HFHM[njetmxAK8];// pfjetAK8HFEMM[njetmxAK8];
  
  float pfjetAK8chrad[njetmxAK8], pfjetAK8pTD[njetmxAK8]; 
  float pfjetAK8sdmass[njetmxAK8], pfjetAK8tau1[njetmxAK8], pfjetAK8tau2[njetmxAK8], pfjetAK8tau3[njetmxAK8];
  
  float pfjetAK8sub1pt[njetmxAK8], pfjetAK8sub1eta[njetmxAK8], pfjetAK8sub1phi[njetmxAK8], pfjetAK8sub1mass[njetmxAK8], pfjetAK8sub1btag[njetmxAK8]; 
  float pfjetAK8sub1hadfrac[njetmxAK8], pfjetAK8sub1chhadfrac[njetmxAK8], pfjetAK8sub1neuhadfrac[njetmxAK8], pfjetAK8sub1emfrac[njetmxAK8], pfjetAK8sub1neuemfrac[njetmxAK8], pfjetAK8sub1phofrac[njetmxAK8], pfjetAK8sub1mufrac[njetmxAK8];
  float pfjetAK8sub2pt[njetmxAK8], pfjetAK8sub2eta[njetmxAK8], pfjetAK8sub2phi[njetmxAK8], pfjetAK8sub2mass[njetmxAK8], pfjetAK8sub2btag[njetmxAK8];
  float pfjetAK8sub2hadfrac[njetmxAK8], pfjetAK8sub2chhadfrac[njetmxAK8], pfjetAK8sub2neuhadfrac[njetmxAK8], pfjetAK8sub2emfrac[njetmxAK8], pfjetAK8sub2neuemfrac[njetmxAK8], pfjetAK8sub2phofrac[njetmxAK8], pfjetAK8sub2mufrac[njetmxAK8];
  
  float pfjetAK8muinpt[njetmxAK8], pfjetAK8muineta[njetmxAK8], pfjetAK8muinphi[njetmxAK8], pfjetAK8muinmass[njetmxAK8];
  
  float pfjetAK8elinpt[njetmxAK8], pfjetAK8elineta[njetmxAK8], pfjetAK8elinphi[njetmxAK8], pfjetAK8elinmass[njetmxAK8];
  
  float pfjetAK8muinsubpt[njetmxAK8], pfjetAK8muinsubeta[njetmxAK8], pfjetAK8muinsubphi[njetmxAK8], pfjetAK8muinsubmass[njetmxAK8];
  float pfjetAK8muinsubjpt[njetmxAK8], pfjetAK8muinsubjeta[njetmxAK8], pfjetAK8muinsubjphi[njetmxAK8], pfjetAK8muinsubjmass[njetmxAK8];
  
  float pfjetAK8muinsubIfar[njetmxAK8], pfjetAK8muinsubI0[njetmxAK8], pfjetAK8muinsubInear[njetmxAK8];
  
  float pfjetAK8elinsubpt[njetmxAK8], pfjetAK8elinsubeta[njetmxAK8], pfjetAK8elinsubphi[njetmxAK8], pfjetAK8elinsubmass[njetmxAK8];
  float pfjetAK8elinsubjpt[njetmxAK8], pfjetAK8elinsubjeta[njetmxAK8], pfjetAK8elinsubjphi[njetmxAK8], pfjetAK8elinsubjmass[njetmxAK8];
  
  float pfjetAK8elinsubIfar[njetmxAK8], pfjetAK8elinsubI0[njetmxAK8], pfjetAK8elinsubInear[njetmxAK8];
  
  float pfjetAK8subhaddiff[njetmxAK8], pfjetAK8subemdiff[njetmxAK8], pfjetAK8subptdiff[njetmxAK8];
  
  float pfjetAK8JEC[njetmxAK8];
  float pfjetAK8reso[njetmxAK8], pfjetAK8resoup[njetmxAK8], pfjetAK8resodn[njetmxAK8];
  
  float pfjetAK8jesup_AbsoluteStat[njetmxAK8], pfjetAK8jesdn_AbsoluteStat[njetmxAK8];
  float pfjetAK8jesup_AbsoluteScale[njetmxAK8], pfjetAK8jesdn_AbsoluteScale[njetmxAK8];
  float pfjetAK8jesup_AbsoluteMPFBias[njetmxAK8], pfjetAK8jesdn_AbsoluteMPFBias[njetmxAK8];
  float pfjetAK8jesup_FlavorQCD[njetmxAK8], pfjetAK8jesdn_FlavorQCD[njetmxAK8];
  float pfjetAK8jesup_Fragmentation[njetmxAK8], pfjetAK8jesdn_Fragmentation[njetmxAK8];
  float pfjetAK8jesup_PileUpDataMC[njetmxAK8], pfjetAK8jesdn_PileUpDataMC[njetmxAK8];
  float pfjetAK8jesup_PileUpPtBB[njetmxAK8], pfjetAK8jesdn_PileUpPtBB[njetmxAK8];
  float pfjetAK8jesup_PileUpPtEC1[njetmxAK8], pfjetAK8jesdn_PileUpPtEC1[njetmxAK8];
  float pfjetAK8jesup_PileUpPtEC2[njetmxAK8], pfjetAK8jesdn_PileUpPtEC2[njetmxAK8];
  float pfjetAK8jesup_PileUpPtHF[njetmxAK8], pfjetAK8jesdn_PileUpPtHF[njetmxAK8];
  float pfjetAK8jesup_PileUpPtRef[njetmxAK8], pfjetAK8jesdn_PileUpPtRef[njetmxAK8];
  float pfjetAK8jesup_RelativeFSR[njetmxAK8], pfjetAK8jesdn_RelativeFSR[njetmxAK8];
  float pfjetAK8jesup_RelativeJEREC1[njetmxAK8], pfjetAK8jesdn_RelativeJEREC1[njetmxAK8];
  float pfjetAK8jesup_RelativeJEREC2[njetmxAK8], pfjetAK8jesdn_RelativeJEREC2[njetmxAK8];
  float pfjetAK8jesup_RelativeJERHF[njetmxAK8], pfjetAK8jesdn_RelativeJERHF[njetmxAK8];
  float pfjetAK8jesup_RelativePtBB[njetmxAK8], pfjetAK8jesdn_RelativePtBB[njetmxAK8];
  float pfjetAK8jesup_RelativePtEC1[njetmxAK8], pfjetAK8jesdn_RelativePtEC1[njetmxAK8];
  float pfjetAK8jesup_RelativePtEC2[njetmxAK8], pfjetAK8jesdn_RelativePtEC2[njetmxAK8];
  float pfjetAK8jesup_RelativePtHF[njetmxAK8], pfjetAK8jesdn_RelativePtHF[njetmxAK8];
  float pfjetAK8jesup_RelativeBal[njetmxAK8], pfjetAK8jesdn_RelativeBal[njetmxAK8];
  float pfjetAK8jesup_RelativeSample[njetmxAK8], pfjetAK8jesdn_RelativeSample[njetmxAK8];
  float pfjetAK8jesup_RelativeStatEC[njetmxAK8], pfjetAK8jesdn_RelativeStatEC[njetmxAK8];
  float pfjetAK8jesup_RelativeStatHF[njetmxAK8], pfjetAK8jesdn_RelativeStatHF[njetmxAK8];
  float pfjetAK8jesup_RelativeStatFSR[njetmxAK8], pfjetAK8jesdn_RelativeStatFSR[njetmxAK8];
  float pfjetAK8jesup_SinglePionECAL[njetmxAK8], pfjetAK8jesdn_SinglePionECAL[njetmxAK8];
  float pfjetAK8jesup_SinglePionHCAL[njetmxAK8], pfjetAK8jesdn_SinglePionHCAL[njetmxAK8];
  float pfjetAK8jesup_TimePtEta[njetmxAK8], pfjetAK8jesdn_TimePtEta[njetmxAK8];
  float pfjetAK8jesup_Total[njetmxAK8], pfjetAK8jesdn_Total[njetmxAK8];
  
  int npfjetAK4;
  float pfjetAK4pt[njetmx], pfjetAK4eta[njetmx], pfjetAK4y[njetmx], pfjetAK4phi[njetmx], pfjetAK4mass[njetmx];
 
  float pfjetAK4btag_DeepCSV[njetmx], pfjetAK4btag_DeepFlav[njetmx]; 
  float pfjetAK4CHF[njetmx], pfjetAK4NHF[njetmx], pfjetAK4MUF[njetmx], pfjetAK4PHF[njetmx], pfjetAK4CEMF[njetmx], pfjetAK4NEMF[njetmx], pfjetAK4EEF[njetmx], pfjetAK4HFEMF[njetmx];
  int pfjetAK4CHM[njetmx], pfjetAK4NHM[njetmx], pfjetAK4MUM[njetmx], pfjetAK4PHM[njetmx], pfjetAK4Neucons[njetmx], pfjetAK4Chcons[njetmx], pfjetAK4EEM[njetmx],  pfjetAK4HFEMM[njetmx];
  

  bool pfjetAK4jetID[njetmx], pfjetAK4jetID_tightlepveto[njetmx];

  float pfjetAK4btag_DeepCSV_SF[njetmx], pfjetAK4btag_DeepCSV_SF_up[njetmx], pfjetAK4btag_DeepCSV_SF_dn[njetmx];
  float pfjetAK4btag_DeepFlav_SF[njetmx], pfjetAK4btag_DeepFlav_SF_up[njetmx], pfjetAK4btag_DeepFlav_SF_dn[njetmx];
  float pfjetAK4reso[njetmx], pfjetAK4resoup[njetmx], pfjetAK4resodn[njetmx];
  
  float pfjetAK4JEC[njetmx];

  float pfjetAK4jesup_AbsoluteStat[njetmx], pfjetAK4jesdn_AbsoluteStat[njetmx];
  float pfjetAK4jesup_AbsoluteScale[njetmx], pfjetAK4jesdn_AbsoluteScale[njetmx];
  float pfjetAK4jesup_AbsoluteMPFBias[njetmx], pfjetAK4jesdn_AbsoluteMPFBias[njetmx];
  float pfjetAK4jesup_FlavorQCD[njetmx], pfjetAK4jesdn_FlavorQCD[njetmx];
  float pfjetAK4jesup_Fragmentation[njetmx], pfjetAK4jesdn_Fragmentation[njetmx];
  float pfjetAK4jesup_PileUpDataMC[njetmx], pfjetAK4jesdn_PileUpDataMC[njetmx];
  float pfjetAK4jesup_PileUpPtBB[njetmx], pfjetAK4jesdn_PileUpPtBB[njetmx];
  float pfjetAK4jesup_PileUpPtEC1[njetmx], pfjetAK4jesdn_PileUpPtEC1[njetmx];
  float pfjetAK4jesup_PileUpPtEC2[njetmx], pfjetAK4jesdn_PileUpPtEC2[njetmx];
  float pfjetAK4jesup_PileUpPtHF[njetmx], pfjetAK4jesdn_PileUpPtHF[njetmx];
  float pfjetAK4jesup_PileUpPtRef[njetmx], pfjetAK4jesdn_PileUpPtRef[njetmx];
  float pfjetAK4jesup_RelativeFSR[njetmx], pfjetAK4jesdn_RelativeFSR[njetmx];
  float pfjetAK4jesup_RelativeJEREC1[njetmx], pfjetAK4jesdn_RelativeJEREC1[njetmx];
  float pfjetAK4jesup_RelativeJEREC2[njetmx], pfjetAK4jesdn_RelativeJEREC2[njetmx];
  float pfjetAK4jesup_RelativeJERHF[njetmx], pfjetAK4jesdn_RelativeJERHF[njetmx];
  float pfjetAK4jesup_RelativePtBB[njetmx], pfjetAK4jesdn_RelativePtBB[njetmx];
  float pfjetAK4jesup_RelativePtEC1[njetmx], pfjetAK4jesdn_RelativePtEC1[njetmx];
  float pfjetAK4jesup_RelativePtEC2[njetmx], pfjetAK4jesdn_RelativePtEC2[njetmx];
  float pfjetAK4jesup_RelativePtHF[njetmx], pfjetAK4jesdn_RelativePtHF[njetmx];
  float pfjetAK4jesup_RelativeBal[njetmx], pfjetAK4jesdn_RelativeBal[njetmx];
  float pfjetAK4jesup_RelativeSample[njetmx], pfjetAK4jesdn_RelativeSample[njetmx];
  float pfjetAK4jesup_RelativeStatEC[njetmx], pfjetAK4jesdn_RelativeStatEC[njetmx];
  float pfjetAK4jesup_RelativeStatHF[njetmx], pfjetAK4jesdn_RelativeStatHF[njetmx];
  float pfjetAK4jesup_RelativeStatFSR[njetmx], pfjetAK4jesdn_RelativeStatFSR[njetmx];
  float pfjetAK4jesup_SinglePionECAL[njetmx], pfjetAK4jesdn_SinglePionECAL[njetmx];
  float pfjetAK4jesup_SinglePionHCAL[njetmx], pfjetAK4jesdn_SinglePionHCAL[njetmx];
  float pfjetAK4jesup_TimePtEta[njetmx], pfjetAK4jesdn_TimePtEta[njetmx];
  float pfjetAK4jesup_Total[njetmx], pfjetAK4jesdn_Total[njetmx];
  
  int pfjetAK4hadronflav[njetmx], pfjetAK4partonflav[njetmx];
  int pfjetAK4Ncons[njetmx];
  float pfjetAK4qgl[njetmx], pfjetAK4PUID[njetmx];
  int pfjetAK4GenMatch[njetmx];
  
  static const int ngenjetAK8mx =10;
  
  int ngenjetAK8;
  float genjetAK8pt[njetmxAK8], genjetAK8eta[njetmxAK8], genjetAK8phi[njetmxAK8], genjetAK8mass[njetmxAK8], genjetAK8sdmass[njetmxAK8]; 
  int genjetAK8hadronflav[njetmxAK8], genjetAK8partonflav[njetmxAK8];

  int ngenjetAK4;
  float genjetAK4pt[njetmx], genjetAK4eta[njetmx], genjetAK4phi[njetmx], genjetAK4mass[njetmx];
  int genjetAK4hadronflav[njetmx], genjetAK4partonflav[njetmx];

  int ngenparticles;
  int genpartstatus[npartmx], genpartpdg[npartmx], genpartmompdg[npartmx], genpartmomstatus[npartmx], genpartgrmompdg[npartmx], genpartmomid[npartmx], genpartdaugno[npartmx];
  float genpartpt[npartmx], genparteta[npartmx], genpartphi[npartmx], genpartm[npartmx]; //genpartq[npartmx];
  bool genpartfromhard[npartmx], genpartfromhardbFSR[npartmx], genpartisPromptFinalState[npartmx], genpartisLastCopyBeforeFSR[npartmx];

  float Generator_x1, Generator_x2, Generator_xpdf1,Generator_xpdf2, Generator_id1, Generator_id2, Generator_scalePDF;
  
  static const int nlhemax = 10;
  int nLHEparticles;
  float LHEpartpt[nlhemax], LHEparteta[nlhemax], LHEpartphi[nlhemax], LHEpartm[nlhemax];
  int LHEpartpdg[nlhemax];

  static const int nlheallweightsmax = 152;
  int nLHEAllWeights;
  float LHEAllWeights[nlheallweightsmax];

  static const int nlhescalemax = 9;
  int nLHEScaleWeights;
  float LHEScaleWeights[nlhescalemax];
  
  static const int nlhepdfmax = 103; // be consistent with nPDFsets (nlhepdfmax should be >= nPDFsets)
  int nLHEPDFWeights;
  float LHEPDFWeights[nlhepdfmax];
  
  static const int nalpsmax = 3;
  int nLHEAlpsWeights;
  float LHEAlpsWeights[nalpsmax];
  
  static const int nlhepsmax = 8;
  int nLHEPSWeights;
  float LHEPSWeights[nlhepsmax];
  
  double LHE_weight;
  
  float miset , misphi , sumEt, misetsig;
  float miset_UnclusEup, miset_UnclusEdn;
  float misphi_UnclusEup, misphi_UnclusEdn;
  
  float miset_PUPPI , misphi_PUPPI , sumEt_PUPPI, misetsig_PUPPI;
  float miset_PUPPI_JESup, miset_PUPPI_JESdn, miset_PUPPI_JERup, miset_PUPPI_JERdn, miset_PUPPI_UnclusEup, miset_PUPPI_UnclusEdn;
  float misphi_PUPPI_JESup, misphi_PUPPI_JESdn, misphi_PUPPI_JERup, misphi_PUPPI_JERdn, misphi_PUPPI_UnclusEup, misphi_PUPPI_UnclusEdn;
  float genmiset, genmisphi, genmisetsig;
  
  int nmuons;
  
  float muonchiso[njetmx], muonnhiso[njetmx], muonphiso[njetmx], muonminisoall[njetmx]; 
  float /*muoncharge[njetmx],*/ muonp[njetmx], muonpt[njetmx], muoneta[njetmx], muonphi[njetmx], muondz[njetmx], muonpter[njetmx], muonchi[njetmx], muonecal[njetmx], muonhcal[njetmx]; //muonemiso[njetmx], muonhadiso[njetmx], muontkpt03[njetmx], muontkpt05[njetmx];
  
  float muonposmatch[njetmx], muontrkink[njetmx], muonsegcom[njetmx], muonpfiso[njetmx], muontrkvtx[njetmx], muonhit[njetmx], muonpixhit[njetmx], muonmst[njetmx], muontrklay[njetmx], muonvalfrac[njetmx],mudxy_sv[njetmx];
  int muonndf[njetmx];
  
  bool muonisPF[njetmx], muonisGL[njetmx], muonisTRK[njetmx];
  bool muonisGoodGL[njetmx], muonisTight[njetmx], muonisHighPt[njetmx], muonisHighPttrk[njetmx], muonisMed[njetmx], muonisMedPr[njetmx], muonisLoose[njetmx];

  float Muon_corrected_pt[njetmx], Muon_correctedUp_pt[njetmx], Muon_correctedDown_pt[njetmx];
  
  int nelecs;
  bool elmvaid[njetmx], elmvaid_noIso[njetmx];
  bool elmvaid_wpLoose[njetmx], elmvaid_wpLoose_noIso[njetmx];
  bool elmvaid_Fallv2WP80[njetmx], elmvaid_Fallv2WP80_noIso[njetmx];
  bool elcutid_veto[njetmx], elcutid_loose[njetmx], elcutid_med[njetmx], elcutid_tight[njetmx];

  float /*elcharge[njetmx],*/ elpt[njetmx], eleta[njetmx], elphi[njetmx], ele[njetmx], elp[njetmx], eldxytrk[njetmx], eldxy_sv[njetmx], eldztrk[njetmx],elhovere[njetmx], elqovrper[njetmx], elchi[njetmx]; //elemiso03[njetmx], elhadiso03[njetmx], elemiso04[njetmx], elhadiso04[njetmx];
  float eleoverp[njetmx], elietaieta[njetmx], eletain[njetmx], elphiin[njetmx], elfbrem[njetmx]; 
  float elnohits[njetmx], elmisshits[njetmx];
  float elpfiso[njetmx];
  int elndf[njetmx];

  float Electron_eccalTrkEnergyPostCorr[njetmx];
  float Electron_energyScaleValue[njetmx];
  float Electron_energyScaleUp[njetmx];
  float Electron_energyScaleDown[njetmx];
  float Electron_energySigmaValue[njetmx];
  float Electron_energySigmaUp[njetmx];
  float Electron_energySigmaDown[njetmx];
  
  float elsupcl_eta[njetmx]; 
  float elsupcl_phi[njetmx]; 
  float elsupcl_rawE[njetmx];
  float elsupcl_e[njetmx]; 
  float elsigmaieta[njetmx];
  float elsigmaiphi[njetmx];
  float elr9full[njetmx];
  float elsupcl_etaw[njetmx];
  float elsupcl_phiw[njetmx];
  float elhcaloverecal[njetmx];
  float elcloctftrkn[njetmx];
  float elcloctftrkchi2[njetmx];
  float ele1x5bye5x5[njetmx];
  float elnormchi2[njetmx];
  float elhitsmiss[njetmx];
  float eltrkmeasure[njetmx];
  float elconvtxprob[njetmx];
  float elecloverpout[njetmx];
  float elecaletrkmomentum[njetmx];
  float eldeltaetacltrkcalo[njetmx];
  float elsupcl_preshvsrawe[njetmx];
  float elpfisolsumphet[njetmx];
  float elpfisolsumchhadpt[njetmx];
  float elpfsiolsumneuhadet[njetmx];
  
  /***as do not needed for boosted dileptonic ttbar emu analysis***/
  /*int nphotons;
    bool phomvaid[njetmx];
    float phoe[njetmx], phoeta[njetmx], phophi[njetmx], phoe1by9[njetmx], phoe9by25[njetmx], phohadbyem[njetmx], photrkiso[njetmx], phoemiso[njetmx], phohadiso[njetmx], phochhadiso[njetmx], phoneuhadiso[njetmx], phoPUiso[njetmx], phophoiso[njetmx], phoietaieta[njetmx];
  */
  
  int ntrigobjs;
  float trigobjpt[njetmx], trigobjeta[njetmx],trigobjphi[njetmx], trigobjmass[njetmx];
  bool trigobjHLT[njetmx], trigobjL1[njetmx],  trigobjBoth[njetmx];
  int  trigobjIhlt[njetmx], trigobjpdgId[njetmx], trigobjprescale[njetmx];
  
  float qscale;
  float wtfact;
  int npu_vert;
  int npu_vert_true;
  
  //int nchict;
  //int nvert;;
  //int ndofct;
  
  /*********initially with all triggers********/
  /*
    static const int nHLTmx = 17;
    const char *hlt_name[nHLTmx] = {"HLT_IsoMu24_v","HLT_Mu50_v","HLT_Ele32_WPTight_Gsf_v","HLT_Ele20_WPLoose_Gsf_v","HLT_Ele300_CaloIdVT_GsfTrkIdT","HLT_AK8PFJet420_TrimMass30_v","HLT_AK8PFHT900_TrimMass50_v","HLT_PFJet500_v","HLT_AK8PFJet500_v","HLT_PFHT1050_v","HLT_AK8PFHT750_TrimMass50_v","HLT_AK8PFHT800_TrimMass50_v","HLT_AK8PFHT850_TrimMass50_v","HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet165_v","HLT_Ele115_CaloIdVT_GsfTrkIdT_v","HLT_DoubleEle33_CaloIdL_MW_v","HLT_DoubleEle25_CaloIdL_MW_v"};
  */  
  static const int nHLTmx = 38;
  const char *hlt_name[nHLTmx] = {"HLT_IsoMu24_v","HLT_Mu50_v","HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet165_v","HLT_Ele115_CaloIdVT_GsfTrkIdT_v",   //4
				  "HLT_AK8PFJet500_v", "HLT_Photon200_v",     //6
				  "HLT_Mu37_Ele27_CaloIdL_MW_v", "HLT_Mu27_Ele37_CaloIdL_MW_v", "HLT_Mu37_TkMu27_v", "HLT_OldMu100", "HLT_TkMu100_v", "HLT_DoubleEle25_CaloIdL_MW_v",  //12
				  "HLT_PFMET250_HBHECleaned","HLT_PFMET300_HBHECleaned","HLT_PFMET200_HBHE_BeamHaloCleaned","HLT_PFMETTypeOne200_HBHE_BeamHaloCleaned",      //16
				  "HLT_AK8PFHT800_TrimMass50_v","HLT_AK8PFHT900_TrimMass50_v","HLT_AK8PFJet400_TrimMass30_v","HLT_AK8PFJet420_TrimMass30_v","HLT_AK8PFJet550_v","HLT_CaloJet500_NoJetID_v","HLT_PFHT1050_v",   //23
				  "HLT_PFJet500_v","HLT_AK8PFJet320_v","HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17_v","HLT_AK8PFJet360_TrimMass30_v","HLT_DiPFJetAve400_v","HLT_PFJet400_v","HLT_PFJet320_v","HLT_PFJet200_v",  //31
				  "HLT_CaloMET100_HBHECleaned_v","HLT_CaloMET250_HBHECleaned_v","HLT_CaloMET90_HBHECleaned_v","HLT_CaloMET70_HBHECleaned_v","HLT_PFMETTypeOne140_PFMHT140_IDTight_v","HLT_PFMETTypeOne120_PFMHT120_IDTight_v","HLT_CaloMET80_HBHECleaned_v"};
  
  //HLT_AK8PFJet360_TrimMass30_v = > can be added 
    //HLT_Ele20_WPLoose_Gsf_v : this was there till 19th Jan, 2020 as 6th element 
  
    bool hlt_IsoMu24, hlt_Mu50, hlt_Ele50_PFJet165, hlt_Ele115, hlt_AK8PFJet500, hlt_Photon200, hlt_Mu37Ele27, hlt_Mu27Ele37, hlt_Mu37TkMu27, hlt_OldMu100, hlt_TkMu100, hlt_DoubleEle25, hlt_PFMET250, hlt_PFMET300, hlt_PFMET200, hlt_PFMET200_TypeOne,hlt_AK8PFHT800_TrimMass50,hlt_AK8PFHT900_TrimMass50,hlt_AK8PFJet400_TrimMass30,hlt_AK8PFJet420_TrimMass30,hlt_AK8PFJet550,hlt_CaloJet500_NoJetID,hlt_PFHT1050,hlt_PFJet500,hlt_AK8PFJet320, hlt_AK8PFJet330_PFAK8BTagDeepCSV,hlt_AK8PFJet360_TrimMass30,hlt_DiPFJetAve400,hlt_PFJet400,hlt_PFJet320,hlt_PFJet200,hlt_CaloMET100_HBHECleaned,hlt_CaloMET250_HBHECleaned,hlt_CaloMET90_HBHECleaned,hlt_CaloMET70_HBHECleaned,hlt_PFMETTypeOne140_PFMHT140_IDTight,hlt_PFMETTypeOne120_PFMHT120_IDTight,hlt_CaloMET80_HBHECleaned;
  
  float psfactor_hlt_IsoMu24, psfactor_hlt_Mu50, psfactor_hlt_Ele50_PFJet165, psfactor_hlt_Ele115, psfactor_hlt_AK8PFJet500, psfactor_hlt_Photon200, psfactor_hlt_Mu37Ele27, psfactor_hlt_Mu27Ele37, psfactor_hlt_Mu37TkMu27, psfactor_hlt_OldMu100, psfactor_hlt_TkMu100, psfactor_hlt_DoubleEle25, psfactor_hlt_PFMET250, psfactor_hlt_PFMET300, psfactor_hlt_PFMET200, psfactor_hlt_PFMET200_TypeOne, psfactor_hlt_AK8PFHT800_TrimMass50, psfactor_hlt_AK8PFHT900_TrimMass50, psfactor_hlt_AK8PFJet400_TrimMass30, psfactor_hlt_AK8PFJet420_TrimMass30, psfactor_hlt_AK8PFJet550, psfactor_hlt_CaloJet500_NoJetID, psfactor_hlt_PFHT1050, psfactor_hlt_PFJet500, psfactor_hlt_AK8PFJet320, psfactor_hlt_AK8PFJet330_PFAK8BTagDeepCSV, psfactor_hlt_AK8PFJet360_TrimMass30, psfactor_hlt_DiPFJetAve400, psfactor_hlt_PFJet400, psfactor_hlt_PFJet320, psfactor_hlt_PFJet200, psfactor_hlt_CaloMET100_HBHECleaned, psfactor_hlt_CaloMET250_HBHECleaned, psfactor_hlt_CaloMET90_HBHECleaned, psfactor_hlt_CaloMET70_HBHECleaned, psfactor_hlt_PFMETTypeOne140_PFMHT140_IDTight, psfactor_hlt_PFMETTypeOne120_PFMHT120_IDTight, psfactor_hlt_CaloMET80_HBHECleaned;  

  float ps_column;
  int trig_value;
  
  HLTPrescaleProvider hltPrescaleProvider_;
  
  // ---- Jet Corrector Parameter End---- //
  
  // ---- Jet Corrector Parameter ---- //
  JetCorrectorParameters *L1FastAK4, *L2RelativeAK4, *L3AbsoluteAK4, *L2L3ResidualAK4;
  vector<JetCorrectorParameters> vecL1FastAK4, vecL2RelativeAK4, vecL3AbsoluteAK4, vecL2L3ResidualAK4;
  FactorizedJetCorrector *jecL1FastAK4, *jecL2RelativeAK4, *jecL3AbsoluteAK4, *jecL2L3ResidualAK4;
  
  JetCorrectorParameters *L1FastAK8, *L2RelativeAK8, *L3AbsoluteAK8, *L2L3ResidualAK8;
  vector<JetCorrectorParameters> vecL1FastAK8, vecL2RelativeAK8, vecL3AbsoluteAK8, vecL2L3ResidualAK8;
  FactorizedJetCorrector *jecL1FastAK8, *jecL2RelativeAK8, *jecL3AbsoluteAK8, *jecL2L3ResidualAK8;

  BTagCalibration calib_deepcsv, calib_deepflav;
  BTagCalibrationReader reader_deepcsv, reader_deepflav;

  std::string melectronID_isowp90, melectronID_noisowp90;
  std::string melectronID_isowp80, melectronID_noisowp80;
  std::string melectronID_isowploose, melectronID_noisowploose;
  std::string melectronID_veto, melectronID_loose,melectronID_med, melectronID_tight;
  
  // std::string mFileName,mPuFileName,mPuTrigName;
  std::string mJECL1FastFileAK4, mJECL2RelativeFileAK4, mJECL3AbsoluteFileAK4, mJECL2L3ResidualFileAK4, mJECL1FastFileAK8, mJECL2RelativeFileAK8, mJECL3AbsoluteFileAK8, mJECL2L3ResidualFileAK8;
  std::string mPtResoFileAK4, mPtResoFileAK8, mPtSFFileAK4, mPtSFFileAK8;
  // ---- Jet Corrector Parameter End---- //
  
  std::string mJECUncFileAK4;
  std::vector<JetCorrectionUncertainty*> vsrc ;
  
  std::string mJECUncFileAK8;
  std::vector<JetCorrectionUncertainty*> vsrcAK8 ;

  std::string mBtagSF_DeepCSV;
  std::string mBtagSF_DeepFlav;

  // ---- Rochester correction //
  std::string mRochcorFolder;
  RoccoR roch_cor; 

};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//

Leptop::Leptop(const edm::ParameterSet& pset):
  hltPrescaleProvider_(pset, consumesCollector(), *this)
{
  //now do what ever initialization is needed
  
  edm::Service<TFileService> fs;
  
  isMC      = pset.getUntrackedParameter<bool>("MonteCarlo", false);
  isData = !isMC;
  year		= pset.getUntrackedParameter<int>("YEAR", 2018);
  isUltraLegacy = pset.getUntrackedParameter<bool>("UltraLegacy", false);
  isSoftDrop      = pset.getUntrackedParameter<bool>("SoftDrop_ON",false);
  theRootFileName = pset.getUntrackedParameter<string>("RootFileName");
  theHLTTag = pset.getUntrackedParameter<string>("HLTTag", "HLT");
  add_prefireweights = pset.getUntrackedParameter<bool>("add_prefireweights", false);
  read_btagSF = pset.getUntrackedParameter<bool>("Read_btagging_SF", false);
  store_electron_scalnsmear = pset.getUntrackedParameter<bool>("store_electron_scalnsmear", false);

  minPt = pset.getUntrackedParameter<double>("minPt",25.);
  minGenPt = pset.getUntrackedParameter<double>("minGenPt",15.);
  maxEta = pset.getUntrackedParameter<double>("maxEta",3.);
  maxgenEta = pset.getUntrackedParameter<double>("maxgenEta",3.);
  AK8PtCut = pset.getUntrackedParameter<double>("AK8PtCut",180.);
  AK8GenPtCut = pset.getUntrackedParameter<double>("AK8GenPtCut",150.);
  
  triggerBits_ = consumes<edm::TriggerResults> ( pset.getParameter<edm::InputTag>("bits"));
  triggerObjects_ = consumes<pat::TriggerObjectStandAloneCollection>(pset.getParameter<edm::InputTag>("objects"));
  triggerPrescales_ = consumes<pat::PackedTriggerPrescales>(pset.getParameter<edm::InputTag>("prescales"));
  
  softdropmass = pset.getUntrackedParameter<string>("softdropmass");
  tau1 = pset.getUntrackedParameter<string>("tau1");
  tau2 = pset.getUntrackedParameter<string>("tau2");
  tau3 = pset.getUntrackedParameter<string>("tau3");
  subjets = pset.getUntrackedParameter<string>("subjets");
  toptagger_DAK8 = pset.getUntrackedParameter<string>("toptagger_DAK8");
  Wtagger_DAK8 = pset.getUntrackedParameter<string>("Wtagger_DAK8");
  Ztagger_DAK8 = pset.getUntrackedParameter<string>("Ztagger_DAK8");
  toptagger_PNet = pset.getUntrackedParameter<string>("toptagger_PNet");
  Wtagger_PNet = pset.getUntrackedParameter<string>("Wtagger_PNet");
 
  tok_beamspot_ = consumes<reco::BeamSpot> (pset.getParameter<edm::InputTag>("Beamspot"));
  tok_primaryVertices_ =consumes<reco::VertexCollection>( pset.getParameter<edm::InputTag>("PrimaryVertices"));
  //slimmedSecondaryVertices
  tok_sv =consumes<reco::VertexCompositePtrCandidateCollection>( pset.getParameter<edm::InputTag>("SecondaryVertices"));
  
  tok_Rho_ = consumes<double>(pset.getParameter<edm::InputTag>("PFRho"));
  
  //ea_miniiso_ = std::make_unique<EffectiveAreas>((pset.getParameter<edm::FileInPath>("EAFile_MiniIso")).fullPath());
  ea_miniiso_.reset(new EffectiveAreas((pset.getParameter<edm::FileInPath>("EAFile_MiniIso")).fullPath()));
  //edm::FileInPath fp = pset.getParameter<edm::FileInPath>("EAFile_MiniIso");
  //ea_miniiso_ = consumes<EffectiveAreas>((pset.getParameter<edm::FileInPath>("EAFile_MiniIso")).fullPath());
  
  //src_ = consumes<edm::View<pat::Muon>> ( pset.getParameter<edm::InputTag>("src"));
  relative_ = pset.getParameter<bool>("relative");
  
  tok_mets_= consumes<pat::METCollection> ( pset.getParameter<edm::InputTag>("PFMet"));
  tok_mets_PUPPI_ = consumes<pat::METCollection> ( pset.getParameter<edm::InputTag>("PuppiMet"));
  
  //pfToken_(consumes<pat::PackedCandidateCollection>(iConfig.getParameter<edm::InputTag>("pfCands")))
  tok_pfcands_ = consumes<pat::PackedCandidateCollection>( pset.getParameter<edm::InputTag>("pfCands"));
  
  tok_muons_ = consumes<edm::View<pat::Muon>> ( pset.getParameter<edm::InputTag>("Muons"));
  tok_electrons_ = consumes<edm::View<pat::Electron>> ( pset.getParameter<edm::InputTag>("Electrons"));
  //tok_photons_ = consumes<edm::View<pat::Photon>>  ( pset.getParameter<edm::InputTag>("Photons"));
  
  tok_pfjetAK8s_= consumes<edm::View<pat::Jet>>( pset.getParameter<edm::InputTag>("PFJetsAK8"));
  tok_pfjetAK4s_= consumes<edm::View<pat::Jet>>( pset.getParameter<edm::InputTag>("PFJetsAK4"));
  if(isMC){
    tok_genmets_= consumes<reco::GenMETCollection> ( pset.getParameter<edm::InputTag>("GENMet"));
    tok_genjetAK8s_= consumes<reco::GenJetCollection>( pset.getParameter<edm::InputTag>("GENJetAK8"));
    tok_genjetAK4s_= consumes<reco::GenJetCollection>( pset.getParameter<edm::InputTag>("GENJetAK4"));
    tok_genparticles_ = consumes<std::vector<reco::GenParticle>>( pset.getParameter<edm::InputTag>("GenParticles"));
    jetFlavourInfosToken_ = consumes<reco::JetFlavourInfoMatchingCollection>(pset.getParameter<edm::InputTag>("jetFlavourInfos"));
  }
  
  melectronID_isowp90       = pset.getParameter<std::string>("electronID_isowp90");
  melectronID_noisowp90     = pset.getParameter<std::string>("electronID_noisowp90");
  melectronID_isowploose    = pset.getParameter<std::string>("electronID_isowploose");
  melectronID_noisowploose  = pset.getParameter<std::string>("electronID_noisowploose");
  melectronID_isowp80       = pset.getParameter<std::string>("electronID_isowp80");
  melectronID_noisowp80     = pset.getParameter<std::string>("electronID_noisowp80");
  melectronID_veto          = pset.getParameter<std::string>("electronID_veto");
  melectronID_loose         = pset.getParameter<std::string>("electronID_loose");
  melectronID_med           = pset.getParameter<std::string>("electronID_med");
  melectronID_tight         = pset.getParameter<std::string>("electronID_tight");

  mJECL1FastFileAK4         = pset.getParameter<std::string>("jecL1FastFileAK4");
  mJECL1FastFileAK8         = pset.getParameter<std::string>("jecL1FastFileAK8");
  mJECL2RelativeFileAK4     = pset.getParameter<std::string>("jecL2RelativeFileAK4");
  mJECL2RelativeFileAK8     = pset.getParameter<std::string>("jecL2RelativeFileAK8");
  mJECL3AbsoluteFileAK4     = pset.getParameter<std::string>("jecL3AbsoluteFileAK4");
  mJECL3AbsoluteFileAK8     = pset.getParameter<std::string> ("jecL3AbsoluteFileAK8");
  mJECL2L3ResidualFileAK4   = pset.getParameter<std::string> ("jecL2L3ResidualFileAK4");
  mJECL2L3ResidualFileAK8   = pset.getParameter<std::string> ("jecL2L3ResidualFileAK8");
  
  mPtResoFileAK4  = pset.getParameter<std::string>("PtResoFileAK4");
  mPtResoFileAK8  = pset.getParameter<std::string>("PtResoFileAK8");
  mPtSFFileAK4  = pset.getParameter<std::string>("PtSFFileAK4");
  mPtSFFileAK8  = pset.getParameter<std::string>("PtSFFileAK8");
  
  mJECUncFileAK4 = pset.getParameter<std::string>("JECUncFileAK4");
  mJECUncFileAK8 = pset.getParameter<std::string>("JECUncFileAK8");

  mBtagSF_DeepCSV = pset.getParameter<std::string>("BtagSFFile_DeepCSV");
  mBtagSF_DeepFlav = pset.getParameter<std::string>("BtagSFFile_DeepFlav");

  mRochcorFolder = pset.getParameter<std::string>("RochcorFolder");

  if(isMC){    
    tok_HepMC = consumes<HepMCProduct>(pset.getParameter<edm::InputTag>("Generator"));
    tok_wt_ = consumes<GenEventInfoProduct>(pset.getParameter<edm::InputTag>("Generator")) ;
    lheEventProductToken_ = consumes<LHEEventProduct>(pset.getParameter<edm::InputTag>("LHEEventProductInputTag")) ;
    pileup_ = consumes<std::vector<PileupSummaryInfo> >(pset.getParameter<edm::InputTag>("slimmedAddPileupInfo"));
    nPDFsets      = pset.getUntrackedParameter<uint>("nPDFsets", 103);	
  }

  if(add_prefireweights){
    prefweight_token = consumes< double >(edm::InputTag("prefiringweight:nonPrefiringProb"));
    prefweightup_token = consumes< double >(edm::InputTag("prefiringweight:nonPrefiringProbUp"));
    prefweightdown_token = consumes< double >(edm::InputTag("prefiringweight:nonPrefiringProbDown"));
  }
  
  beta = pset.getUntrackedParameter<double>("beta",0.);
  z_cut = pset.getUntrackedParameter<double>("z_cut",0.1); 
  
  theFile = new TFile(theRootFileName.c_str(), "RECREATE");
  theFile->cd();
  
  T1 = new TTree("T1", "EMuboosted");
  
  T1->Branch("irun", &irun, "irun/I");  
  T1->Branch("ilumi", &ilumi, "ilumi/I");  
  
  // primary vertices //
  
  T1->Branch("ievt", &ievt, "ievt/i");
  T1->Branch("nprim", &nprim, "nprim/I");
  
  //T1->Branch("nvert", &nvert, "nvert/I");  
  //T1->Branch("ndofct", &ndofct, "ndofct/I");
  //T1->Branch("nchict", &nchict, "nchict/I");
  
  T1->Branch("nprimi", &nprimi, "nprimi/I");
  
  // energy density //
  
  T1->Branch("Rho", &Rho, "Rho/D") ;
  
  // generator-related info //
  if(isMC){
    T1->Branch("Generator_weight", &Generator_weight, "Generator_weight/D") ;
    T1->Branch("qscale",&qscale,"qscale/F");
    T1->Branch("npu_vert",&npu_vert,"npu_vert/I");
    T1->Branch("npu_vert_true",&npu_vert_true,"npu_vert_true/I");
  }
  // trigger info //
  
  T1->Branch("trig_value",&trig_value,"trig_value/I");  
  
  T1->Branch("hlt_IsoMu24",&hlt_IsoMu24,"hlt_IsoMu24/O");
  T1->Branch("hlt_Mu50",&hlt_Mu50,"hlt_Mu50/O");
  T1->Branch("hlt_Ele50_PFJet165",&hlt_Ele50_PFJet165,"hlt_Ele50_PFJet165/O");
  T1->Branch("hlt_Ele115",&hlt_Ele115,"hlt_Ele115/O");
  T1->Branch("hlt_AK8PFJet500",&hlt_AK8PFJet500,"hlt_AK8PFJet500/O");
  T1->Branch("hlt_Photon200",&hlt_Photon200,"hlt_Photon200/O");
  T1->Branch("hlt_Mu37Ele27",&hlt_Mu37Ele27,"hlt_Mu37Ele27/O");
  T1->Branch("hlt_Mu27Ele37",&hlt_Mu27Ele37,"hlt_Mu27Ele37/O");
  T1->Branch("hlt_Mu37TkMu27",&hlt_Mu37TkMu27,"hlt_Mu37TkMu27/O");
  T1->Branch("hlt_OldMu100",&hlt_OldMu100,"hlt_OldMu100/O");
  T1->Branch("hlt_TkMu100",&hlt_TkMu100,"hlt_TkMu100/O");
  T1->Branch("hlt_DoubleEle25",&hlt_DoubleEle25,"hlt_DoubleEle25/O");
  T1->Branch("hlt_PFMET250",&hlt_PFMET250,"hlt_PFMET250/O");
  T1->Branch("hlt_PFMET300",&hlt_PFMET300,"hlt_PFMET300/O");
  T1->Branch("hlt_PFMET200",&hlt_PFMET200,"hlt_PFMET200/O");
  T1->Branch("hlt_PFMET200_TypeOne",&hlt_PFMET200_TypeOne,"hlt_PFMET200_TypeOne/O");
  T1->Branch("hlt_AK8PFHT800_TrimMass50",&hlt_AK8PFHT800_TrimMass50,"hlt_AK8PFHT800_TrimMass50/O");
  T1->Branch("hlt_AK8PFHT900_TrimMass50",&hlt_AK8PFHT900_TrimMass50,"hlt_AK8PFHT900_TrimMass50/O");
  T1->Branch("hlt_AK8PFJet400_TrimMass30",&hlt_AK8PFJet400_TrimMass30,"hlt_AK8PFJet400_TrimMass30/O");
  T1->Branch("hlt_AK8PFJet420_TrimMass30",&hlt_AK8PFJet420_TrimMass30,"hlt_AK8PFJet420_TrimMass30/O");
  T1->Branch("hlt_AK8PFJet550",&hlt_AK8PFJet550,"hlt_AK8PFJet550/O");
  T1->Branch("hlt_CaloJet500_NoJetID",&hlt_CaloJet500_NoJetID,"hlt_CaloJet500_NoJetID/O");
  T1->Branch("hlt_PFHT1050",&hlt_PFHT1050,"hlt_PFHT1050/O");
  T1->Branch("hlt_PFJet500",&hlt_PFJet500,"hlt_PFJet500/O");
  T1->Branch("hlt_AK8PFJet320",&hlt_AK8PFJet320,"hlt_AK8PFJet320/O");
  T1->Branch("hlt_AK8PFJet330_PFAK8BTagDeepCSV",&hlt_AK8PFJet330_PFAK8BTagDeepCSV,"hlt_AK8PFJet330_PFAK8BTagDeepCSV/O");
  T1->Branch("hlt_AK8PFJet360_TrimMass30",&hlt_AK8PFJet360_TrimMass30,"hlt_AK8PFJet360_TrimMass30/O");
  T1->Branch("hlt_DiPFJetAve400",&hlt_DiPFJetAve400,"hlt_DiPFJetAve400/O");
  T1->Branch("hlt_PFJet400",&hlt_PFJet400,"hlt_PFJet400/O");
  T1->Branch("hlt_PFJet320",&hlt_PFJet320,"hlt_PFJet320/O");
  T1->Branch("hlt_PFJet200",&hlt_PFJet200,"hlt_PFJet200/O");
  T1->Branch("hlt_CaloMET100_HBHECleaned",&hlt_CaloMET100_HBHECleaned,"hlt_CaloMET100_HBHECleaned/O");
  T1->Branch("hlt_CaloMET250_HBHECleaned",&hlt_CaloMET250_HBHECleaned,"hlt_CaloMET250_HBHECleaned/O");
  T1->Branch("hlt_CaloMET90_HBHECleaned",&hlt_CaloMET90_HBHECleaned,"hlt_CaloMET90_HBHECleaned/O");
  T1->Branch("hlt_CaloMET70_HBHECleaned",&hlt_CaloMET70_HBHECleaned,"hlt_CaloMET70_HBHECleaned/O");
  T1->Branch("hlt_PFMETTypeOne140_PFMHT140_IDTight",&hlt_PFMETTypeOne140_PFMHT140_IDTight,"hlt_PFMETTypeOne140_PFMHT140_IDTight/O");
  T1->Branch("hlt_PFMETTypeOne120_PFMHT120_IDTight",&hlt_PFMETTypeOne120_PFMHT120_IDTight,"hlt_PFMETTypeOne120_PFMHT120_IDTight/O");
  T1->Branch("hlt_CaloMET80_HBHECleaned",&hlt_CaloMET80_HBHECleaned,"hlt_CaloMET80_HBHECleaned/O");

  T1->Branch("psfactor_hlt_IsoMu24",&psfactor_hlt_IsoMu24,"psfactor_hlt_IsoMu24/F");
  T1->Branch("psfactor_hlt_Mu50",&psfactor_hlt_Mu50,"psfactor_hlt_Mu50/F");
  T1->Branch("psfactor_hlt_Ele50_PFJet165",&psfactor_hlt_Ele50_PFJet165,"psfactor_hlt_Ele50_PFJet165/F");
  T1->Branch("psfactor_hlt_Ele115",&psfactor_hlt_Ele115,"psfactor_hlt_Ele115/F");
  T1->Branch("psfactor_hlt_AK8PFJet500",&psfactor_hlt_AK8PFJet500,"psfactor_hlt_AK8PFJet500/F");
  T1->Branch("psfactor_hlt_Photon200",&psfactor_hlt_Photon200,"psfactor_hlt_Photon200/F");
  T1->Branch("psfactor_hlt_Mu37Ele27",&psfactor_hlt_Mu37Ele27,"psfactor_hlt_Mu37Ele27/F");
  T1->Branch("psfactor_hlt_Mu27Ele37",&psfactor_hlt_Mu27Ele37,"psfactor_hlt_Mu27Ele37/F");
  T1->Branch("psfactor_hlt_Mu37TkMu27",&psfactor_hlt_Mu37TkMu27,"psfactor_hlt_Mu37TkMu27/F");
  T1->Branch("psfactor_hlt_OldMu100",&psfactor_hlt_OldMu100,"psfactor_hlt_OldMu100/F");
  T1->Branch("psfactor_hlt_TkMu100",&psfactor_hlt_TkMu100,"psfactor_hlt_TkMu100/F");
  T1->Branch("psfactor_hlt_DoubleEle25",&psfactor_hlt_DoubleEle25,"psfactor_hlt_DoubleEle25/F");
  T1->Branch("psfactor_hlt_PFMET250",&psfactor_hlt_PFMET250,"psfactor_hlt_PFMET250/F");
  T1->Branch("psfactor_hlt_PFMET300",&psfactor_hlt_PFMET300,"psfactor_hlt_PFMET300/F");
  T1->Branch("psfactor_hlt_PFMET200",&psfactor_hlt_PFMET200,"psfactor_hlt_PFMET200/F");
  T1->Branch("psfactor_hlt_PFMET200_TypeOne",&psfactor_hlt_PFMET200_TypeOne,"psfactor_hlt_PFMET200_TypeOne/F");
  T1->Branch("psfactor_hlt_AK8PFHT800_TrimMass50",&psfactor_hlt_AK8PFHT800_TrimMass50,"psfactor_hlt_AK8PFHT800_TrimMass50/F");
  T1->Branch("psfactor_hlt_AK8PFHT900_TrimMass50",&psfactor_hlt_AK8PFHT900_TrimMass50,"psfactor_hlt_AK8PFHT900_TrimMass50/F");
  T1->Branch("psfactor_hlt_AK8PFJet400_TrimMass30",&psfactor_hlt_AK8PFJet400_TrimMass30,"psfactor_hlt_AK8PFJet400_TrimMass30/F");
  T1->Branch("psfactor_hlt_AK8PFJet420_TrimMass30",&psfactor_hlt_AK8PFJet420_TrimMass30,"psfactor_hlt_AK8PFJet420_TrimMass30/F");
  T1->Branch("psfactor_hlt_AK8PFJet550",&psfactor_hlt_AK8PFJet550,"psfactor_hlt_AK8PFJet550/F");
  T1->Branch("psfactor_hlt_CaloJet500_NoJetID",&psfactor_hlt_CaloJet500_NoJetID,"psfactor_hlt_CaloJet500_NoJetID/F");
  T1->Branch("psfactor_hlt_PFHT1050",&psfactor_hlt_PFHT1050,"psfactor_hlt_PFHT1050/F");
  T1->Branch("psfactor_hlt_PFJet500",&psfactor_hlt_PFJet500,"psfactor_hlt_PFJet500/F");
  T1->Branch("psfactor_hlt_AK8PFJet320",&psfactor_hlt_AK8PFJet320,"psfactor_hlt_AK8PFJet320/F");
  T1->Branch("psfactor_hlt_AK8PFJet330_PFAK8BTagDeepCSV",&psfactor_hlt_AK8PFJet330_PFAK8BTagDeepCSV,"psfactor_hlt_AK8PFJet330_PFAK8BTagDeepCSV/F");
  T1->Branch("psfactor_hlt_AK8PFJet360_TrimMass30",&psfactor_hlt_AK8PFJet360_TrimMass30,"psfactor_hlt_AK8PFJet360_TrimMass30/F");
  T1->Branch("psfactor_hlt_DiPFJetAve400",&psfactor_hlt_DiPFJetAve400,"psfactor_hlt_DiPFJetAve400/F");
  T1->Branch("psfactor_hlt_PFJet400",&psfactor_hlt_PFJet400,"psfactor_hlt_PFJet400/F");
  T1->Branch("psfactor_hlt_PFJet320",&psfactor_hlt_PFJet320,"psfactor_hlt_PFJet320/F");
  T1->Branch("psfactor_hlt_PFJet200",&psfactor_hlt_PFJet200,"psfactor_hlt_PFJet200/F");
  T1->Branch("psfactor_hlt_CaloMET100_HBHECleaned",&psfactor_hlt_CaloMET100_HBHECleaned,"psfactor_hlt_CaloMET100_HBHECleaned/F");
  T1->Branch("psfactor_hlt_CaloMET250_HBHECleaned",&psfactor_hlt_CaloMET250_HBHECleaned,"psfactor_hlt_CaloMET250_HBHECleaned/F");
  T1->Branch("psfactor_hlt_CaloMET90_HBHECleaned",&psfactor_hlt_CaloMET90_HBHECleaned,"psfactor_hlt_CaloMET90_HBHECleaned/F");
  T1->Branch("psfactor_hlt_CaloMET70_HBHECleaned",&psfactor_hlt_CaloMET70_HBHECleaned,"psfactor_hlt_CaloMET70_HBHECleaned/F");
  T1->Branch("psfactor_hlt_PFMETTypeOne140_PFMHT140_IDTight",&psfactor_hlt_PFMETTypeOne140_PFMHT140_IDTight,"psfactor_hlt_PFMETTypeOne140_PFMHT140_IDTight/F");
  T1->Branch("psfactor_hlt_PFMETTypeOne120_PFMHT120_IDTight",&psfactor_hlt_PFMETTypeOne120_PFMHT120_IDTight,"psfactor_hlt_PFMETTypeOne120_PFMHT120_IDTight/F");
  T1->Branch("psfactor_hlt_CaloMET80_HBHECleaned",&psfactor_hlt_CaloMET80_HBHECleaned,"psfactor_hlt_CaloMET80_HBHECleaned/F");
  T1->Branch("ps_column",&ps_column,"ps_column/F");
	     
  T1->Branch("ntrigobjs",&ntrigobjs,"ntrigobjs/I");
  T1->Branch("trigobjpt",trigobjpt,"trigobjpt[ntrigobjs]/F");
  T1->Branch("trigobjeta",trigobjeta,"trigobjeta[ntrigobjs]/F");
  T1->Branch("trigobjphi",trigobjphi,"trigobjphi[ntrigobjs]/F");
  T1->Branch("trigobjmass",trigobjmass,"trigobjmass[ntrigobjs]/F");
  T1->Branch("trigobjHLT",trigobjHLT,"trigobjHLT[ntrigobjs]/O");
  T1->Branch("trigobjL1",trigobjL1,"trigobjL1[ntrigobjs]/O");
  //T1->Branch("trigobjBoth",trigobjBoth,"trigobjBoth[ntrigobjs]/O");
  T1->Branch("trigobjIhlt",trigobjIhlt,"trigobjIhlt[ntrigobjs]/I");
  //T1->Branch("trigobjprescale",trigobjprescale,"trigobjprescale[ntrigobjs]/I");
  T1->Branch("trigobjpdgId",trigobjpdgId,"trigobjpdgId[ntrigobjs]/I");

  // Prefire weights //
  if(add_prefireweights){
    T1->Branch("prefiringweight",&prefiringweight,"prefiringweight/D");
    T1->Branch("prefiringweightup",&prefiringweightup,"prefiringweightup/D");
    T1->Branch("prefiringweightdown",&prefiringweightdown,"prefiringweightdown/D");
  }
  // MET info //
  
  T1->Branch("CHSMET_pt",&miset,"miset/F") ;
  T1->Branch("CHSMET_phi",&misphi,"misphi/F") ;
  T1->Branch("CHSMET_sig",&misetsig,"misetsig/F");
  T1->Branch("CHSMET_sumEt",&sumEt,"sumEt/F");
  
  T1->Branch("CHSMET_pt_UnclusEup",&miset_UnclusEup,"miset_CHS_UnclusEup/F") ;
  T1->Branch("CHSMET_pt_UnclusEdn",&miset_UnclusEdn,"miset_CHS_UnclusEdn/F") ;
  T1->Branch("CHSMET_phi_UnclusEup",&misphi_UnclusEup,"CHSMET_phi_UnclusEup/F") ;
  T1->Branch("CHSMET_phi_UnclusEdn",&misphi_UnclusEdn,"CHSMET_phi_UnclusEdn/F") ;
  
  T1->Branch("PuppiMET_pt",&miset_PUPPI,"miset_PUPPI/F") ;
  T1->Branch("PuppiMET_phi",&misphi_PUPPI,"misphi_PUPPI/F") ;
  T1->Branch("PuppiMET_sig",&misetsig_PUPPI,"misetsig_PUPPI/F");
  T1->Branch("PuppiMET_sumEt",&sumEt_PUPPI,"sumEt_PUPPI/F");
  
  T1->Branch("PuppiMET_pt_JESup",&miset_PUPPI_JESup,"miset_PUPPI_JESup/F") ;
  T1->Branch("PuppiMET_pt_JESdn",&miset_PUPPI_JESdn,"miset_PUPPI_JESdn/F") ;
  T1->Branch("PuppiMET_pt_JERup",&miset_PUPPI_JERup,"miset_PUPPI_JERup/F") ;
  T1->Branch("PuppiMET_pt_JERdn",&miset_PUPPI_JERdn,"miset_PUPPI_JERdn/F") ;
  T1->Branch("PuppiMET_pt_UnclusEup",&miset_PUPPI_UnclusEup,"miset_PUPPI_UnclusEup/F") ;
  T1->Branch("PuppiMET_pt_UnclusEdn",&miset_PUPPI_UnclusEdn,"miset_PUPPI_UnclusEdn/F") ;
  T1->Branch("PuppiMET_phi_JESup",&misphi_PUPPI_JESup,"misphi_PUPPI_JESup/F") ;
  T1->Branch("PuppiMET_phi_JESdn",&misphi_PUPPI_JESdn,"misphi_PUPPI_JESdn/F") ;
  T1->Branch("PuppiMET_phi_JERup",&misphi_PUPPI_JERup,"misphi_PUPPI_JERup/F") ;
  T1->Branch("PuppiMET_phi_JERdn",&misphi_PUPPI_JERdn,"misphi_PUPPI_JERdn/F") ;
  T1->Branch("PuppiMET_phi_UnclusEup",&misphi_PUPPI_UnclusEup,"misphi_PUPPI_UnclusEup/F") ;
  T1->Branch("PuppiMET_phi_UnclusEdn",&misphi_PUPPI_UnclusEdn,"misphi_PUPPI_UnclusEdn/F") ;

  // AK8 jet info //
  
  T1->Branch("npfjetAK8",&npfjetAK8, "npfjetAK8/I"); 
  T1->Branch("pfjetAK8pt",pfjetAK8pt,"pfjetAK8pt[npfjetAK8]/F");
  T1->Branch("pfjetAK8y",pfjetAK8y,"pfjetAK8y[npfjetAK8]/F");
  T1->Branch("pfjetAK8eta",pfjetAK8eta,"pfjetAK8eta[npfjetAK8]/F");
  T1->Branch("pfjetAK8phi",pfjetAK8phi,"pfjetAK8phi[npfjetAK8]/F");
  T1->Branch("pfjetAK8mass",pfjetAK8mass,"pfjetAK8mass[npfjetAK8]/F");
  T1->Branch("pfjetAK8jetID_tightlepveto",pfjetAK8jetID_tightlepveto,"pfjetAK8jetID_tightlepveto[npfjetAK8]/O");
  T1->Branch("pfjetAK8jetID",pfjetAK8jetID,"pfjetAK8jetID[npfjetAK8]/O");
  T1->Branch("pfjetAK8JEC",pfjetAK8JEC,"pfjetAK8JEC[npfjetAK8]/F");
  T1->Branch("pfjetAK8btag_DeepCSV",pfjetAK8btag_DeepCSV,"pfjetAK8btag_DeepCSV[npfjetAK8]/F");
  T1->Branch("pfjetAK8DeepTag_DAK8_TvsQCD",pfjetAK8DeepTag_DAK8_TvsQCD,"pfjetAK8DeepTag_DAK8_TvsQCD[npfjetAK8]/F");
  T1->Branch("pfjetAK8DeepTag_DAK8_WvsQCD",pfjetAK8DeepTag_DAK8_WvsQCD,"pfjetAK8DeepTag_DAK8_WvsQCD[npfjetAK8]/F");
  T1->Branch("pfjetAK8DeepTag_DAK8_ZvsQCD",pfjetAK8DeepTag_DAK8_ZvsQCD,"pfjetAK8DeepTag_DAK8_ZvsQCD[npfjetAK8]/F");
  T1->Branch("pfjetAK8DeepTag_PNet_TvsQCD",pfjetAK8DeepTag_PNet_TvsQCD,"pfjetAK8DeepTag_PNet_TvsQCD[npfjetAK8]/F");
  T1->Branch("pfjetAK8DeepTag_PNet_WvsQCD",pfjetAK8DeepTag_PNet_WvsQCD,"pfjetAK8DeepTag_PNet_WvsQCD[npfjetAK8]/F");
  T1->Branch("pfjetAK8CHF",pfjetAK8CHF,"pfjetAK8CHF[npfjetAK8]/F");
  T1->Branch("pfjetAK8NHF",pfjetAK8NHF,"pfjetAK8NHF[npfjetAK8]/F");
  T1->Branch("pfjetAK8CEMF",pfjetAK8CEMF,"pfjetAK8CEMF[npfjetAK8]/F");
  T1->Branch("pfjetAK8NEMF",pfjetAK8NEMF,"pfjetAK8NEMF[npfjetAK8]/F");
  T1->Branch("pfjetAK8MUF",pfjetAK8MUF,"pfjetAK8MUF[npfjetAK8]/F");
  T1->Branch("pfjetAK8PHF",pfjetAK8PHF,"pfjetAK8PHF[npfjetAK8]/F");
  T1->Branch("pfjetAK8EEF",pfjetAK8EEF,"pfjetAK8EEF[npfjetAK8]/F");
  T1->Branch("pfjetAK8HFHF",pfjetAK8HFHF,"pfjetAK8HFHF[npfjetAK8]/F");
  T1->Branch("pfjetAK8CHM",pfjetAK8CHM,"pfjetAK8CHM[npfjetAK8]/I");
  T1->Branch("pfjetAK8NHM",pfjetAK8NHM,"pfjetAK8NHM[npfjetAK8]/I");
  T1->Branch("pfjetAK8MUM",pfjetAK8MUM,"pfjetAK8MUM[npfjetAK8]/I");
  T1->Branch("pfjetAK8PHM",pfjetAK8PHM,"pfjetAK8PHM[npfjetAK8]/I");
  T1->Branch("pfjetAK8EEM",pfjetAK8EEM,"pfjetAK8EEM[npfjetAK8]/I");
  T1->Branch("pfjetAK8HFHM",pfjetAK8HFHM,"pfjetAK8HFHM[npfjetAK8]/I");
  T1->Branch("pfjetAK8Neucons",pfjetAK8Neucons,"pfjetAK8Neucons[npfjetAK8]/I");
  T1->Branch("pfjetAK8Chcons",pfjetAK8Chcons,"pfjetAK8Chcons[npfjetAK8]/I");
  
  T1->Branch("pfjetAK8JER",pfjetAK8reso,"pfjetAK8reso[npfjetAK8]/F");
  T1->Branch("pfjetAK8JERup",pfjetAK8resoup,"pfjetAK8resoup[npfjetAK8]/F");
  T1->Branch("pfjetAK8JERdn",pfjetAK8resodn,"pfjetAK8resodn[npfjetAK8]/F");
  
  T1->Branch("pfjetAK8jesup_AbsoluteStat",pfjetAK8jesup_AbsoluteStat,"pfjetAK8jesup_AbsoluteStat[npfjetAK8]/F");
  T1->Branch("pfjetAK8jesup_AbsoluteScale",pfjetAK8jesup_AbsoluteScale,"pfjetAK8jesup_AbsoluteScale[npfjetAK8]/F");
  T1->Branch("pfjetAK8jesup_AbsoluteMPFBias",pfjetAK8jesup_AbsoluteMPFBias,"pfjetAK8jesup_AbsoluteMPFBias[npfjetAK8]/F");
  T1->Branch("pfjetAK8jesup_FlavorQCD",pfjetAK8jesup_FlavorQCD,"pfjetAK8jesup_FlavorQCD[npfjetAK8]/F");
  T1->Branch("pfjetAK8jesup_Fragmentation",pfjetAK8jesup_Fragmentation,"pfjetAK8jesup_Fragmentation[npfjetAK8]/F");
  T1->Branch("pfjetAK8jesup_PileUpDataMC",pfjetAK8jesup_PileUpDataMC,"pfjetAK8jesup_PileUpDataMC[npfjetAK8]/F");
  T1->Branch("pfjetAK8jesup_PileUpPtBB",pfjetAK8jesup_PileUpPtBB,"pfjetAK8jesup_PileUpPtBB[npfjetAK8]/F");
  T1->Branch("pfjetAK8jesup_PileUpPtEC1",pfjetAK8jesup_PileUpPtEC1,"pfjetAK8jesup_PileUpPtEC1[npfjetAK8]/F");
  T1->Branch("pfjetAK8jesup_PileUpPtEC2",pfjetAK8jesup_PileUpPtEC2,"pfjetAK8jesup_PileUpPtEC2[npfjetAK8]/F");
  T1->Branch("pfjetAK8jesup_PileUpPtHF",pfjetAK8jesup_PileUpPtHF,"pfjetAK8jesup_PileUpPtHF[npfjetAK8]/F");
  T1->Branch("pfjetAK8jesup_PileUpPtRef",pfjetAK8jesup_PileUpPtRef,"pfjetAK8jesup_PileUpPtRef[npfjetAK8]/F");
  T1->Branch("pfjetAK8jesup_RelativeFSR",pfjetAK8jesup_RelativeFSR,"pfjetAK8jesup_RelativeFSR[npfjetAK8]/F");
  T1->Branch("pfjetAK8jesup_RelativeJEREC1",pfjetAK8jesup_RelativeJEREC1,"pfjetAK8jesup_RelativeJEREC1[npfjetAK8]/F");
  T1->Branch("pfjetAK8jesup_RelativeJEREC2",pfjetAK8jesup_RelativeJEREC2,"pfjetAK8jesup_RelativeJEREC2[npfjetAK8]/F");
  T1->Branch("pfjetAK8jesup_RelativeJERHF",pfjetAK8jesup_RelativeJERHF,"pfjetAK8jesup_RelativeJERHF[npfjetAK8]/F");
  T1->Branch("pfjetAK8jesup_RelativePtBB",pfjetAK8jesup_RelativePtBB,"pfjetAK8jesup_RelativePtBB[npfjetAK8]/F");
  T1->Branch("pfjetAK8jesup_RelativePtEC1",pfjetAK8jesup_RelativePtEC1,"pfjetAK8jesup_RelativePtEC1[npfjetAK8]/F");
  T1->Branch("pfjetAK8jesup_RelativePtEC2",pfjetAK8jesup_RelativePtEC2,"pfjetAK8jesup_RelativePtEC2[npfjetAK8]/F");
  T1->Branch("pfjetAK8jesup_RelativePtHF",pfjetAK8jesup_RelativePtHF,"pfjetAK8jesup_RelativePtHF[npfjetAK8]/F");
  T1->Branch("pfjetAK8jesup_RelativeBal",pfjetAK8jesup_RelativeBal,"pfjetAK8jesup_RelativeBal[npfjetAK8]/F");
  T1->Branch("pfjetAK8jesup_RelativeSample",pfjetAK8jesup_RelativeSample,"pfjetAK8jesup_RelativeSample[npfjetAK8]/F");
  T1->Branch("pfjetAK8jesup_RelativeStatEC",pfjetAK8jesup_RelativeStatEC,"pfjetAK8jesup_RelativeStatEC[npfjetAK8]/F");
  T1->Branch("pfjetAK8jesup_RelativeStatHF",pfjetAK8jesup_RelativeStatHF,"pfjetAK8jesup_RelativeStatHF[npfjetAK8]/F");
  T1->Branch("pfjetAK8jesup_RelativeStatFSR",pfjetAK8jesup_RelativeStatFSR,"pfjetAK8jesup_RelativeStatFSR[npfjetAK8]/F");
  T1->Branch("pfjetAK8jesup_SinglePionECAL",pfjetAK8jesup_SinglePionECAL,"pfjetAK8jesup_SinglePionECAL[npfjetAK8]/F");
  T1->Branch("pfjetAK8jesup_SinglePionHCAL",pfjetAK8jesup_SinglePionHCAL,"pfjetAK8jesup_SinglePionHCAL[npfjetAK8]/F");
  T1->Branch("pfjetAK8jesup_TimePtEta",pfjetAK8jesup_TimePtEta,"pfjetAK8jesup_TimePtEta[npfjetAK8]/F");
  T1->Branch("pfjetAK8jesup_Total",pfjetAK8jesup_Total,"pfjetAK8jesup_Total[npfjetAK8]/F");
  
  T1->Branch("pfjetAK8jesdn_AbsoluteStat",pfjetAK8jesdn_AbsoluteStat,"pfjetAK8jesdn_AbsoluteStat[npfjetAK8]/F");
  T1->Branch("pfjetAK8jesdn_AbsoluteScale",pfjetAK8jesdn_AbsoluteScale,"pfjetAK8jesdn_AbsoluteScale[npfjetAK8]/F");
  T1->Branch("pfjetAK8jesdn_AbsoluteMPFBias",pfjetAK8jesdn_AbsoluteMPFBias,"pfjetAK8jesdn_AbsoluteMPFBias[npfjetAK8]/F");
  T1->Branch("pfjetAK8jesdn_FlavorQCD",pfjetAK8jesdn_FlavorQCD,"pfjetAK8jesdn_FlavorQCD[npfjetAK8]/F");
  T1->Branch("pfjetAK8jesdn_Fragmentation",pfjetAK8jesdn_Fragmentation,"pfjetAK8jesdn_Fragmentation[npfjetAK8]/F");
  T1->Branch("pfjetAK8jesdn_PileUpDataMC",pfjetAK8jesdn_PileUpDataMC,"pfjetAK8jesdn_PileUpDataMC[npfjetAK8]/F");
  T1->Branch("pfjetAK8jesdn_PileUpPtBB",pfjetAK8jesdn_PileUpPtBB,"pfjetAK8jesdn_PileUpPtBB[npfjetAK8]/F");
  T1->Branch("pfjetAK8jesdn_PileUpPtEC1",pfjetAK8jesdn_PileUpPtEC1,"pfjetAK8jesdn_PileUpPtEC1[npfjetAK8]/F");
  T1->Branch("pfjetAK8jesdn_PileUpPtEC2",pfjetAK8jesdn_PileUpPtEC2,"pfjetAK8jesdn_PileUpPtEC2[npfjetAK8]/F");
  T1->Branch("pfjetAK8jesdn_PileUpPtHF",pfjetAK8jesdn_PileUpPtHF,"pfjetAK8jesdn_PileUpPtHF[npfjetAK8]/F");
  T1->Branch("pfjetAK8jesdn_PileUpPtRef",pfjetAK8jesdn_PileUpPtRef,"pfjetAK8jesdn_PileUpPtRef[npfjetAK8]/F");
  T1->Branch("pfjetAK8jesdn_RelativeFSR",pfjetAK8jesdn_RelativeFSR,"pfjetAK8jesdn_RelativeFSR[npfjetAK8]/F");
  T1->Branch("pfjetAK8jesdn_RelativeJEREC1",pfjetAK8jesdn_RelativeJEREC1,"pfjetAK8jesdn_RelativeJEREC1[npfjetAK8]/F");
  T1->Branch("pfjetAK8jesdn_RelativeJEREC2",pfjetAK8jesdn_RelativeJEREC2,"pfjetAK8jesdn_RelativeJEREC2[npfjetAK8]/F");
  T1->Branch("pfjetAK8jesdn_RelativeJERHF",pfjetAK8jesdn_RelativeJERHF,"pfjetAK8jesdn_RelativeJERHF[npfjetAK8]/F");
  T1->Branch("pfjetAK8jesdn_RelativePtBB",pfjetAK8jesdn_RelativePtBB,"pfjetAK8jesdn_RelativePtBB[npfjetAK8]/F");
  T1->Branch("pfjetAK8jesdn_RelativePtEC1",pfjetAK8jesdn_RelativePtEC1,"pfjetAK8jesdn_RelativePtEC1[npfjetAK8]/F");
  T1->Branch("pfjetAK8jesdn_RelativePtEC2",pfjetAK8jesdn_RelativePtEC2,"pfjetAK8jesdn_RelativePtEC2[npfjetAK8]/F");
  T1->Branch("pfjetAK8jesdn_RelativePtHF",pfjetAK8jesdn_RelativePtHF,"pfjetAK8jesdn_RelativePtHF[npfjetAK8]/F");
  T1->Branch("pfjetAK8jesdn_RelativeBal",pfjetAK8jesdn_RelativeBal,"pfjetAK8jesdn_RelativeBal[npfjetAK8]/F");
  T1->Branch("pfjetAK8jesdn_RelativeSample",pfjetAK8jesdn_RelativeSample,"pfjetAK8jesdn_RelativeSample[npfjetAK8]/F");
  T1->Branch("pfjetAK8jesdn_RelativeStatEC",pfjetAK8jesdn_RelativeStatEC,"pfjetAK8jesdn_RelativeStatEC[npfjetAK8]/F");
  T1->Branch("pfjetAK8jesdn_RelativeStatHF",pfjetAK8jesdn_RelativeStatHF,"pfjetAK8jesdn_RelativeStatHF[npfjetAK8]/F");
  T1->Branch("pfjetAK8jesdn_RelativeStatFSR",pfjetAK8jesdn_RelativeStatFSR,"pfjetAK8jesdn_RelativeStatFSR[npfjetAK8]/F");
  T1->Branch("pfjetAK8jesdn_SinglePionECAL",pfjetAK8jesdn_SinglePionECAL,"pfjetAK8jesdn_SinglePionECAL[npfjetAK8]/F");
  T1->Branch("pfjetAK8jesdn_SinglePionHCAL",pfjetAK8jesdn_SinglePionHCAL,"pfjetAK8jesdn_SinglePionHCAL[npfjetAK8]/F");
  T1->Branch("pfjetAK8jesdn_TimePtEta",pfjetAK8jesdn_TimePtEta,"pfjetAK8jesdn_TimePtEta[npfjetAK8]/F");
  T1->Branch("pfjetAK8jesdn_Total",pfjetAK8jesdn_Total,"pfjetAK8jesdn_Total[npfjetAK8]/F");
  
  T1->Branch("pfjetAK8chrad",pfjetAK8chrad,"pfjetAK8chrad[npfjetAK8]/F");
  T1->Branch("pfjetAK8pTD",pfjetAK8pTD,"pfjetAK8pTD[npfjetAK8]/F");
  T1->Branch("pfjetAK8sdmass",pfjetAK8sdmass,"pfjetAK8sdmass[npfjetAK8]/F");
  T1->Branch("pfjetAK8tau1",pfjetAK8tau1,"pfjetAK8tau1[npfjetAK8]/F");
  T1->Branch("pfjetAK8tau2",pfjetAK8tau2,"pfjetAK8tau2[npfjetAK8]/F");
  T1->Branch("pfjetAK8tau3",pfjetAK8tau3,"pfjetAK8tau3[npfjetAK8]/F");
  
  T1->Branch("pfjetAK8sub1pt",pfjetAK8sub1pt,"pfjetAK8sub1pt[npfjetAK8]/F");
  T1->Branch("pfjetAK8sub1eta",pfjetAK8sub1eta,"pfjetAK8sub1eta[npfjetAK8]/F");
  T1->Branch("pfjetAK8sub1phi",pfjetAK8sub1phi,"pfjetAK8sub1phi[npfjetAK8]/F");
  T1->Branch("pfjetAK8sub1mass",pfjetAK8sub1mass,"pfjetAK8sub1mass[npfjetAK8]/F");
  T1->Branch("pfjetAK8sub1btag",pfjetAK8sub1btag,"pfjetAK8sub1btag[npfjetAK8]/F");
  T1->Branch("pfjetAK8sub1chhadfrac",pfjetAK8sub1chhadfrac,"pfjetAK8sub1chhadfrac[npfjetAK8]/F");
  T1->Branch("pfjetAK8sub1neuhadfrac",pfjetAK8sub1neuhadfrac,"pfjetAK8sub1neuhadfrac[npfjetAK8]/F");
  T1->Branch("pfjetAK8sub1emfrac",pfjetAK8sub1emfrac,"pfjetAK8sub1emfrac[npfjetAK8]/F");
  T1->Branch("pfjetAK8sub1phofrac",pfjetAK8sub1phofrac,"pfjetAK8sub1phofrac[npfjetAK8]/F");
  T1->Branch("pfjetAK8sub1mufrac",pfjetAK8sub1mufrac,"pfjetAK8sub1mufrac[npfjetAK8]/F");
  
  T1->Branch("pfjetAK8sub2pt",pfjetAK8sub2pt,"pfjetAK8sub2pt[npfjetAK8]/F");
  T1->Branch("pfjetAK8sub2eta",pfjetAK8sub2eta,"pfjetAK8sub2eta[npfjetAK8]/F");
  T1->Branch("pfjetAK8sub2phi",pfjetAK8sub2phi,"pfjetAK8sub2phi[npfjetAK8]/F");
  T1->Branch("pfjetAK8sub2mass",pfjetAK8sub2mass,"pfjetAK8sub2mass[npfjetAK8]/F");
  T1->Branch("pfjetAK8sub2btag",pfjetAK8sub2btag,"pfjetAK8sub2btag[npfjetAK8]/F");
  T1->Branch("pfjetAK8sub2chhadfrac",pfjetAK8sub2chhadfrac,"pfjetAK8sub2chhadfrac[npfjetAK8]/F");
  T1->Branch("pfjetAK8sub2neuhadfrac",pfjetAK8sub2neuhadfrac,"pfjetAK8sub2neuhadfrac[npfjetAK8]/F");
  T1->Branch("pfjetAK8sub2emfrac",pfjetAK8sub2emfrac,"pfjetAK8sub2emfrac[npfjetAK8]/F");
  T1->Branch("pfjetAK8sub2phofrac",pfjetAK8sub2phofrac,"pfjetAK8sub2phofrac[npfjetAK8]/F");
  T1->Branch("pfjetAK8sub2mufrac",pfjetAK8sub2mufrac,"pfjetAK8sub2mufrac[npfjetAK8]/F");
 
  T1->Branch("pfjetAK8muinpt", pfjetAK8muinpt, "pfjetAK8muinpt[npfjetAK8]/F");
  T1->Branch("pfjetAK8muineta", pfjetAK8muineta, "pfjetAK8muineta[npfjetAK8]/F");
  T1->Branch("pfjetAK8muinphi", pfjetAK8muinphi, "pfjetAK8muinphi[npfjetAK8]/F");
  T1->Branch("pfjetAK8muinmass", pfjetAK8muinmass, "pfjetAK8muinmass[npfjetAK8]/F");
  
  T1->Branch("pfjetAK8elinpt", pfjetAK8elinpt, "pfjetAK8elinpt[npfjetAK8]/F");
  T1->Branch("pfjetAK8elineta", pfjetAK8elineta, "pfjetAK8elineta[npfjetAK8]/F");
  T1->Branch("pfjetAK8elinphi", pfjetAK8elinphi, "pfjetAK8elinphi[npfjetAK8]/F");
  T1->Branch("pfjetAK8elinmass", pfjetAK8elinmass, "pfjetAK8elinmass[npfjetAK8]/F");
  
  T1->Branch("pfjetAK8muinsubpt", pfjetAK8muinsubpt, "pfjetAK8muinsubpt[npfjetAK8]/F");
  T1->Branch("pfjetAK8muinsubeta", pfjetAK8muinsubeta, "pfjetAK8muinsubeta[npfjetAK8]/F");
  T1->Branch("pfjetAK8muinsubphi", pfjetAK8muinsubphi, "pfjetAK8muinsubphi[npfjetAK8]/F");
  T1->Branch("pfjetAK8muinsubmass", pfjetAK8muinsubmass, "pfjetAK8muinsubmass[npfjetAK8]/F");

  T1->Branch("pfjetAK8muinsubIfar", pfjetAK8muinsubIfar, "pfjetAK8muinsubIfar[npfjetAK8]/F");
  T1->Branch("pfjetAK8muinsubI0", pfjetAK8muinsubI0,"pfjetAK8muinsubI0[npfjetAK8]/F");
  T1->Branch("pfjetAK8muinsubInear", pfjetAK8muinsubInear,"pfjetAK8muinsubInear[npfjetAK8]/F");

  T1->Branch("pfjetAK8muinsubjpt", pfjetAK8muinsubjpt, "pfjetAK8muinsubjpt[npfjetAK8]/F");
  T1->Branch("pfjetAK8muinsubjeta", pfjetAK8muinsubjeta, "pfjetAK8muinsubjeta[npfjetAK8]/F");
  T1->Branch("pfjetAK8muinsubjphi", pfjetAK8muinsubjphi, "pfjetAK8muinsubjphi[npfjetAK8]/F");
  T1->Branch("pfjetAK8muinsubjmass", pfjetAK8muinsubjmass, "pfjetAK8muinsubjmass[npfjetAK8]/F");
  
  T1->Branch("pfjetAK8elinsubpt", pfjetAK8elinsubpt, "pfjetAK8elinsubpt[npfjetAK8]/F");
  T1->Branch("pfjetAK8elinsubeta", pfjetAK8elinsubeta, "pfjetAK8elinsubeta[npfjetAK8]/F");
  T1->Branch("pfjetAK8elinsubphi", pfjetAK8elinsubphi, "pfjetAK8elinsubphi[npfjetAK8]/F");
  T1->Branch("pfjetAK8elinsubmass", pfjetAK8elinsubmass, "pfjetAK8elinsubmass[npfjetAK8]/F");

  T1->Branch("pfjetAK8elinsubIfar", pfjetAK8elinsubIfar,"pfjetAK8elinsubIfar[npfjetAK8]/F");
  T1->Branch("pfjetAK8elinsubI0", pfjetAK8elinsubI0,"pfjetAK8elinsubI0[npfjetAK8]/F");
  T1->Branch("pfjetAK8elinsubInear", pfjetAK8elinsubInear,"pfjetAK8elinsubInear[npfjetAK8]/F");

  T1->Branch("pfjetAK8elinsubjpt", pfjetAK8elinsubjpt, "pfjetAK8elinsubjpt[npfjetAK8]/F");
  T1->Branch("pfjetAK8elinsubjeta", pfjetAK8elinsubjeta, "pfjetAK8elinsubjeta[npfjetAK8]/F");
  T1->Branch("pfjetAK8elinsubjphi", pfjetAK8elinsubjphi, "pfjetAK8elinsubjphi[npfjetAK8]/F");
  T1->Branch("pfjetAK8elinsubjmass", pfjetAK8elinsubjmass, "pfjetAK8elinsubjmass[npfjetAK8]/F");
  
  T1->Branch("pfjetAK8subhaddiff",pfjetAK8subhaddiff,"pfjetAK8subhaddiff[npfjetAK8]/F");
  T1->Branch("pfjetAK8subemdiff",pfjetAK8subemdiff,"pfjetAK8subemdiff[npfjetAK8]/F");
  T1->Branch("pfjetAK8subptdiff",pfjetAK8subptdiff,"pfjetAK8subptdiff[npfjetAK8]/F");

  // AK4 jet info //
 
  T1->Branch("npfjetAK4",&npfjetAK4,"npfjetAK4/I"); 

  T1->Branch("pfjetAK4jetID",pfjetAK4jetID,"pfjetAK4jetID[npfjetAK4]/O");
  T1->Branch("pfjetAK4jetID_tightlepveto",pfjetAK4jetID_tightlepveto,"pfjetAK4jetID_tightlepveto[npfjetAK4]/O");
  
  T1->Branch("pfjetAK4pt",pfjetAK4pt,"pfjetAK4pt[npfjetAK4]/F");
  T1->Branch("pfjetAK4eta",pfjetAK4eta,"pfjetAK4eta[npfjetAK4]/F");
  T1->Branch("pfjetAK4y",pfjetAK4y,"pfjetAK4y[npfjetAK4]/F");
  T1->Branch("pfjetAK4phi",pfjetAK4phi,"pfjetAK4phi[npfjetAK4]/F");
  T1->Branch("pfjetAK4mass",pfjetAK4mass,"pfjetAK4mass[npfjetAK4]/F");
  T1->Branch("pfjetAK4JEC",pfjetAK4JEC,"pfjetAK4JEC[npfjetAK4]/F");
  T1->Branch("pfjetAK4btag_DeepCSV",pfjetAK4btag_DeepCSV,"pfjetAK4btag_DeepCSV[npfjetAK4]/F");
  T1->Branch("pfjetAK4btag_DeepFlav",pfjetAK4btag_DeepFlav,"pfjetAK4btag_DeepFlav[npfjetAK4]/F");
  if(read_btagSF){
    T1->Branch("pfjetAK4btag_DeepCSV_SF",pfjetAK4btag_DeepCSV_SF,"pfjetAK4btag_DeepCSV_SF[npfjetAK4]/F");
    T1->Branch("pfjetAK4btag_DeepCSV_SF_up",pfjetAK4btag_DeepCSV_SF_up,"pfjetAK4btag_DeepCSV_SF_up[npfjetAK4]/F");
    T1->Branch("pfjetAK4btag_DeepCSV_SF_dn",pfjetAK4btag_DeepCSV_SF_dn,"pfjetAK4btag_DeepCSV_SF_dn[npfjetAK4]/F");
    T1->Branch("pfjetAK4btag_DeepFlav_SF",pfjetAK4btag_DeepFlav_SF,"pfjetAK4btag_DeepFlav_SF[npfjetAK4]/F");
    T1->Branch("pfjetAK4btag_DeepFlav_SF_up",pfjetAK4btag_DeepFlav_SF_up,"pfjetAK4btag_DeepFlav_SF_up[npfjetAK4]/F");
    T1->Branch("pfjetAK4btag_DeepFlav_SF_dn",pfjetAK4btag_DeepFlav_SF_dn,"pfjetAK4btag_DeepFlav_SF_dn[npfjetAK4]/F");
  }
  T1->Branch("pfjetAK4JER",pfjetAK4reso,"pfjetAK4reso[npfjetAK4]/F");
  T1->Branch("pfjetAK4JERup",pfjetAK4resoup,"pfjetAK4resoup[npfjetAK4]/F");
  T1->Branch("pfjetAK4JERdn",pfjetAK4resodn,"pfjetAK4resodn[npfjetAK4]/F");

  T1->Branch("pfjetAK4jesup_AbsoluteStat",pfjetAK4jesup_AbsoluteStat,"pfjetAK4jesup_AbsoluteStat[npfjetAK4]/F");
  T1->Branch("pfjetAK4jesup_AbsoluteScale",pfjetAK4jesup_AbsoluteScale,"pfjetAK4jesup_AbsoluteScale[npfjetAK4]/F");
  T1->Branch("pfjetAK4jesup_AbsoluteMPFBias",pfjetAK4jesup_AbsoluteMPFBias,"pfjetAK4jesup_AbsoluteMPFBias[npfjetAK4]/F");
  T1->Branch("pfjetAK4jesup_FlavorQCD",pfjetAK4jesup_FlavorQCD,"pfjetAK4jesup_FlavorQCD[npfjetAK4]/F");
  T1->Branch("pfjetAK4jesup_Fragmentation",pfjetAK4jesup_Fragmentation,"pfjetAK4jesup_Fragmentation[npfjetAK4]/F");
  T1->Branch("pfjetAK4jesup_PileUpDataMC",pfjetAK4jesup_PileUpDataMC,"pfjetAK4jesup_PileUpDataMC[npfjetAK4]/F");
  T1->Branch("pfjetAK4jesup_PileUpPtBB",pfjetAK4jesup_PileUpPtBB,"pfjetAK4jesup_PileUpPtBB[npfjetAK4]/F");
  T1->Branch("pfjetAK4jesup_PileUpPtEC1",pfjetAK4jesup_PileUpPtEC1,"pfjetAK4jesup_PileUpPtEC1[npfjetAK4]/F");
  T1->Branch("pfjetAK4jesup_PileUpPtEC2",pfjetAK4jesup_PileUpPtEC2,"pfjetAK4jesup_PileUpPtEC2[npfjetAK4]/F");
  T1->Branch("pfjetAK4jesup_PileUpPtHF",pfjetAK4jesup_PileUpPtHF,"pfjetAK4jesup_PileUpPtHF[npfjetAK4]/F");
  T1->Branch("pfjetAK4jesup_PileUpPtRef",pfjetAK4jesup_PileUpPtRef,"pfjetAK4jesup_PileUpPtRef[npfjetAK4]/F");
  T1->Branch("pfjetAK4jesup_RelativeFSR",pfjetAK4jesup_RelativeFSR,"pfjetAK4jesup_RelativeFSR[npfjetAK4]/F");
  T1->Branch("pfjetAK4jesup_RelativeJEREC1",pfjetAK4jesup_RelativeJEREC1,"pfjetAK4jesup_RelativeJEREC1[npfjetAK4]/F");
  T1->Branch("pfjetAK4jesup_RelativeJEREC2",pfjetAK4jesup_RelativeJEREC2,"pfjetAK4jesup_RelativeJEREC2[npfjetAK4]/F");
  T1->Branch("pfjetAK4jesup_RelativeJERHF",pfjetAK4jesup_RelativeJERHF,"pfjetAK4jesup_RelativeJERHF[npfjetAK4]/F");
  T1->Branch("pfjetAK4jesup_RelativePtBB",pfjetAK4jesup_RelativePtBB,"pfjetAK4jesup_RelativePtBB[npfjetAK4]/F");
  T1->Branch("pfjetAK4jesup_RelativePtEC1",pfjetAK4jesup_RelativePtEC1,"pfjetAK4jesup_RelativePtEC1[npfjetAK4]/F");
  T1->Branch("pfjetAK4jesup_RelativePtEC2",pfjetAK4jesup_RelativePtEC2,"pfjetAK4jesup_RelativePtEC2[npfjetAK4]/F");
  T1->Branch("pfjetAK4jesup_RelativePtHF",pfjetAK4jesup_RelativePtHF,"pfjetAK4jesup_RelativePtHF[npfjetAK4]/F");
  T1->Branch("pfjetAK4jesup_RelativeBal",pfjetAK4jesup_RelativeBal,"pfjetAK4jesup_RelativeBal[npfjetAK4]/F");
  T1->Branch("pfjetAK4jesup_RelativeSample",pfjetAK4jesup_RelativeSample,"pfjetAK4jesup_RelativeSample[npfjetAK4]/F");
  T1->Branch("pfjetAK4jesup_RelativeStatEC",pfjetAK4jesup_RelativeStatEC,"pfjetAK4jesup_RelativeStatEC[npfjetAK4]/F");
  T1->Branch("pfjetAK4jesup_RelativeStatHF",pfjetAK4jesup_RelativeStatHF,"pfjetAK4jesup_RelativeStatHF[npfjetAK4]/F");
  T1->Branch("pfjetAK4jesup_RelativeStatFSR",pfjetAK4jesup_RelativeStatFSR,"pfjetAK4jesup_RelativeStatFSR[npfjetAK4]/F");
  T1->Branch("pfjetAK4jesup_SinglePionECAL",pfjetAK4jesup_SinglePionECAL,"pfjetAK4jesup_SinglePionECAL[npfjetAK4]/F");
  T1->Branch("pfjetAK4jesup_SinglePionHCAL",pfjetAK4jesup_SinglePionHCAL,"pfjetAK4jesup_SinglePionHCAL[npfjetAK4]/F");
  T1->Branch("pfjetAK4jesup_TimePtEta",pfjetAK4jesup_TimePtEta,"pfjetAK4jesup_TimePtEta[npfjetAK4]/F");
  T1->Branch("pfjetAK4jesup_Total",pfjetAK4jesup_Total,"pfjetAK4jesup_Total[npfjetAK4]/F");
  
  T1->Branch("pfjetAK4jesdn_AbsoluteStat",pfjetAK4jesdn_AbsoluteStat,"pfjetAK4jesdn_AbsoluteStat[npfjetAK4]/F");
  T1->Branch("pfjetAK4jesdn_AbsoluteScale",pfjetAK4jesdn_AbsoluteScale,"pfjetAK4jesdn_AbsoluteScale[npfjetAK4]/F");
  T1->Branch("pfjetAK4jesdn_AbsoluteMPFBias",pfjetAK4jesdn_AbsoluteMPFBias,"pfjetAK4jesdn_AbsoluteMPFBias[npfjetAK4]/F");
  T1->Branch("pfjetAK4jesdn_FlavorQCD",pfjetAK4jesdn_FlavorQCD,"pfjetAK4jesdn_FlavorQCD[npfjetAK4]/F");
  T1->Branch("pfjetAK4jesdn_Fragmentation",pfjetAK4jesdn_Fragmentation,"pfjetAK4jesdn_Fragmentation[npfjetAK4]/F");
  T1->Branch("pfjetAK4jesdn_PileUpDataMC",pfjetAK4jesdn_PileUpDataMC,"pfjetAK4jesdn_PileUpDataMC[npfjetAK4]/F");
  T1->Branch("pfjetAK4jesdn_PileUpPtBB",pfjetAK4jesdn_PileUpPtBB,"pfjetAK4jesdn_PileUpPtBB[npfjetAK4]/F");
  T1->Branch("pfjetAK4jesdn_PileUpPtEC1",pfjetAK4jesdn_PileUpPtEC1,"pfjetAK4jesdn_PileUpPtEC1[npfjetAK4]/F");
  T1->Branch("pfjetAK4jesdn_PileUpPtEC2",pfjetAK4jesdn_PileUpPtEC2,"pfjetAK4jesdn_PileUpPtEC2[npfjetAK4]/F");
  T1->Branch("pfjetAK4jesdn_PileUpPtHF",pfjetAK4jesdn_PileUpPtHF,"pfjetAK4jesdn_PileUpPtHF[npfjetAK4]/F");
  T1->Branch("pfjetAK4jesdn_PileUpPtRef",pfjetAK4jesdn_PileUpPtRef,"pfjetAK4jesdn_PileUpPtRef[npfjetAK4]/F");
  T1->Branch("pfjetAK4jesdn_RelativeFSR",pfjetAK4jesdn_RelativeFSR,"pfjetAK4jesdn_RelativeFSR[npfjetAK4]/F");
  T1->Branch("pfjetAK4jesdn_RelativeJEREC1",pfjetAK4jesdn_RelativeJEREC1,"pfjetAK4jesdn_RelativeJEREC1[npfjetAK4]/F");
  T1->Branch("pfjetAK4jesdn_RelativeJEREC2",pfjetAK4jesdn_RelativeJEREC2,"pfjetAK4jesdn_RelativeJEREC2[npfjetAK4]/F");
  T1->Branch("pfjetAK4jesdn_RelativeJERHF",pfjetAK4jesdn_RelativeJERHF,"pfjetAK4jesdn_RelativeJERHF[npfjetAK4]/F");
  T1->Branch("pfjetAK4jesdn_RelativePtBB",pfjetAK4jesdn_RelativePtBB,"pfjetAK4jesdn_RelativePtBB[npfjetAK4]/F");
  T1->Branch("pfjetAK4jesdn_RelativePtEC1",pfjetAK4jesdn_RelativePtEC1,"pfjetAK4jesdn_RelativePtEC1[npfjetAK4]/F");
  T1->Branch("pfjetAK4jesdn_RelativePtEC2",pfjetAK4jesdn_RelativePtEC2,"pfjetAK4jesdn_RelativePtEC2[npfjetAK4]/F");
  T1->Branch("pfjetAK4jesdn_RelativePtHF",pfjetAK4jesdn_RelativePtHF,"pfjetAK4jesdn_RelativePtHF[npfjetAK4]/F");
  T1->Branch("pfjetAK4jesdn_RelativeBal",pfjetAK4jesdn_RelativeBal,"pfjetAK4jesdn_RelativeBal[npfjetAK4]/F");
  T1->Branch("pfjetAK4jesdn_RelativeSample",pfjetAK4jesdn_RelativeSample,"pfjetAK4jesdn_RelativeSample[npfjetAK4]/F");
  T1->Branch("pfjetAK4jesdn_RelativeStatEC",pfjetAK4jesdn_RelativeStatEC,"pfjetAK4jesdn_RelativeStatEC[npfjetAK4]/F");
  T1->Branch("pfjetAK4jesdn_RelativeStatHF",pfjetAK4jesdn_RelativeStatHF,"pfjetAK4jesdn_RelativeStatHF[npfjetAK4]/F");
  T1->Branch("pfjetAK4jesdn_RelativeStatFSR",pfjetAK4jesdn_RelativeStatFSR,"pfjetAK4jesdn_RelativeStatFSR[npfjetAK4]/F");
  T1->Branch("pfjetAK4jesdn_SinglePionECAL",pfjetAK4jesdn_SinglePionECAL,"pfjetAK4jesdn_SinglePionECAL[npfjetAK4]/F");
  T1->Branch("pfjetAK4jesdn_SinglePionHCAL",pfjetAK4jesdn_SinglePionHCAL,"pfjetAK4jesdn_SinglePionHCAL[npfjetAK4]/F");
  T1->Branch("pfjetAK4jesdn_TimePtEta",pfjetAK4jesdn_TimePtEta,"pfjetAK4jesdn_TimePtEta[npfjetAK4]/F");
  T1->Branch("pfjetAK4jesdn_Total",pfjetAK4jesdn_Total,"pfjetAK4jesdn_Total[npfjetAK4]/F");
  
  T1->Branch("pfjetAK4hadronflav",pfjetAK4hadronflav,"pfjetAK4hadronflav[npfjetAK4]/I");
  T1->Branch("pfjetAK4partonflav",pfjetAK4partonflav,"pfjetAK4partonflav[npfjetAK4]/I");
  T1->Branch("pfjetAK4qgl",pfjetAK4qgl,"pfjetAK4qgl[npfjetAK4]/F");
  T1->Branch("pfjetAK4PUID",pfjetAK4PUID,"pfjetAK4PUID[npfjetAK4]/F");
  T1->Branch("pfjetAK4GenMatch",pfjetAK4GenMatch,"pfjetAK4GenMatch/I");
  
  if(isMC){
    // generator-related info //
    
    T1->Branch("Generator_x1",&Generator_x1,"Generator_x1/F");
    T1->Branch("Generator_x2",&Generator_x2,"Generator_x2/F");
    T1->Branch("Generator_xpdf1",&Generator_xpdf1,"Generator_xpdf1/F");
    T1->Branch("Generator_xpdf2",&Generator_xpdf2,"Generator_xpdf2/F");
    T1->Branch("Generator_id1",&Generator_id1,"Generator_id1/F");
    T1->Branch("Generator_id2",&Generator_id2,"Generator_id2/F");
    T1->Branch("Generator_scalePDF",&Generator_scalePDF,"Generator_scalePDF/F");
 
    // GEN MET info //
    
    T1->Branch("GENMET",&genmiset,"genmiset/F") ;
    T1->Branch("GENMETPhi",&genmisphi,"genmisphi/F") ;
  
    // GEN AK8 jet info //  
	 T1->Branch("ngenjetAK8",&ngenjetAK8, "ngenjetAK8/I");
    T1->Branch("genjetAK8pt",genjetAK8pt,"genjetAK8pt[ngenjetAK8]/F");
    T1->Branch("genjetAK8eta",genjetAK8eta,"genjetAK8eta[ngenjetAK8]/F");
    T1->Branch("genjetAK8phi",genjetAK8phi,"genjetAK8phi[ngenjetAK8]/F");
    T1->Branch("genjetAK8mass",genjetAK8mass,"genjetAK8mass[ngenjetAK8]/F"); 
    T1->Branch("genjetAK8sdmass",genjetAK8sdmass,"genjetAK8sdmass[ngenjetAK8]/F");
    T1->Branch("genjetAK8hadronflav",genjetAK8hadronflav,"genjetAK8hadronflav[ngenjetAK8]/I");
    T1->Branch("genjetAK8partonflav",genjetAK8partonflav,"genjetAK8partonflav[ngenjetAK8]/I");

    // GEN AK4 jet info //  
 
	 T1->Branch("ngenjetAK4",&ngenjetAK4, "ngenjetAK4/I");
    T1->Branch("genjetAK4pt",genjetAK4pt,"genjetAK4pt[ngenjetAK4]/F");
    T1->Branch("genjetAK4eta",genjetAK4eta,"genjetAK4eta[ngenjetAK4]/F");
    T1->Branch("genjetAK4phi",genjetAK4phi,"genjetAK4phi[ngenjetAK4]/F");
    T1->Branch("genjetAK4mass",genjetAK4mass,"genjetAK4mass[ngenjetAK4]/F");
    T1->Branch("genjetAK4hadronflav",genjetAK4hadronflav,"genjetAK4hadronflav[ngenjetAK4]/I");
    T1->Branch("genjetAK4partonflav",genjetAK4partonflav,"genjetAK4partonflav[ngenjetAK4]/I");
    
    // GEN particles info //  
	 
	 T1->Branch("ngenparticles",&ngenparticles, "ngenparticles/I");
    T1->Branch("genpartstatus",genpartstatus,"genpartstatus[ngenparticles]/I");
    T1->Branch("genpartpdg",genpartpdg,"genpartpdg[ngenparticles]/I");
    T1->Branch("genpartmompdg",genpartmompdg,"genpartmompdg[ngenparticles]/I");
    T1->Branch("genpartmomstatus",genpartmomstatus,"genpartmomstatus[ngenparticles]/I");
    T1->Branch("genpartgrmompdg",genpartgrmompdg,"genpartgrmompdg[ngenparticles]/I");
    T1->Branch("genpartdaugno",genpartdaugno,"genpartdaugno[ngenparticles]/I");
    T1->Branch("genpartfromhard",genpartfromhard,"genpartfromhard[ngenparticles]/O");
    T1->Branch("genpartfromhardbFSR",genpartfromhardbFSR,"genpartfromhardbFSR[ngenparticles]/O");
    T1->Branch("genpartisPromptFinalState",genpartisPromptFinalState,"genpartisPromptFinalState[ngenparticles]/O");
    T1->Branch("genpartisLastCopyBeforeFSR",genpartisLastCopyBeforeFSR,"genpartisLastCopyBeforeFSR[ngenparticles]/O");
    T1->Branch("genpartpt",genpartpt,"genpartpt[ngenparticles]/F");
    T1->Branch("genparteta",genparteta,"genparteta[ngenparticles]/F");
    T1->Branch("genpartphi",genpartphi,"genpartphi[ngenparticles]/F");
    T1->Branch("genpartm",genpartm,"genpartm[ngenparticles]/F");

    // LHE Info //

    T1->Branch("nLHEparticles",&nLHEparticles, "nLHEparticles/I");
    T1->Branch("LHEpartpdg",LHEpartpdg,"LHEpartpdg[nLHEparticles]/I");
    T1->Branch("LHEpartpt",LHEpartpt,"LHEpartpt[nLHEparticles]/F");
    T1->Branch("LHEparteta",LHEparteta,"LHEparteta[nLHEparticles]/F");
    T1->Branch("LHEpartphi",LHEpartphi,"LHEpartphi[nLHEparticles]/F");
    T1->Branch("LHEpartm",LHEpartm,"LHEpartm[nLHEparticles]/F");

    T1->Branch("LHE_weight",&LHE_weight, "LHE_weight/D");
    T1->Branch("nLHEAllWeights",&nLHEAllWeights, "nLHEAllWeights/I");
    T1->Branch("LHEAllWeights",LHEAllWeights,"LHEAllWeights[nLHEAllWeights]/F");
    T1->Branch("nLHEScaleWeights",&nLHEScaleWeights, "nLHEScaleWeights/I");
    T1->Branch("LHEScaleWeights",LHEScaleWeights,"LHEScaleWeights[nLHEScaleWeights]/F");
    T1->Branch("nLHEPDFWeights",&nLHEPDFWeights, "nLHEPDFWeights/I");
    T1->Branch("LHEPDFWeights",LHEPDFWeights,"LHEPDFWeights[nLHEPDFWeights]/F");
    T1->Branch("nLHEAlpsWeights",&nLHEAlpsWeights, "nLHEAlpsWeights/I");
    T1->Branch("LHEAlpsWeights",LHEAlpsWeights,"LHEAlpsWeights[nLHEAlpsWeights]/F");
    T1->Branch("nLHEPSWeights",&nLHEPSWeights, "nLHEPSWeights/I");
    T1->Branch("LHEPSWeights",LHEPSWeights,"LHEPSWeights[nLHEPSWeights]/F");
  
  } //isMC
  
  // Muon info //
  
  T1->Branch("nmuons",&nmuons,"nmuons/I");
  T1->Branch("muonisPF",muonisPF,"muonisPF[nmuons]/O");
  T1->Branch("muonisGL",muonisGL,"muonisGL[nmuons]/O");
  T1->Branch("muonisTRK",muonisTRK,"muonisTRK[nmuons]/O");
  
  T1->Branch("muonisLoose",muonisLoose,"muonisLoose[nmuons]/O");
  T1->Branch("muonisGoodGL",muonisGoodGL,"muonisGoodGL[nmuons]/O");
  T1->Branch("muonisMed",muonisMed,"muonisMed[nmuons]/O");
  T1->Branch("muonisMedPr",muonisMedPr,"muonisMedPr[nmuons]/O");
  T1->Branch("muonisTight",muonisTight,"muonisTight[nmuons]/O");
  T1->Branch("muonisHighPt",muonisHighPt,"muonisHighPt[nmuons]/O"); 
  T1->Branch("muonisHighPttrk",muonisHighPttrk,"muonisHighPttrk[nmuons]/O");
  
  T1->Branch("muonchiso", muonchiso, "muonchiso[nmuons]/F");
  T1->Branch("muonnhiso", muonnhiso, "muonnhiso[nmuons]/F");
  T1->Branch("muonphiso", muonphiso, "muonphiso[nmuons]/F");
  T1->Branch("muonminisoall", muonminisoall, "muonminisoall[nmuons]/F");
  //T1->Branch("muoncharge", muoncharge, "muoncharge[nmuons]/F");
  T1->Branch("muonpt",muonpt,"muonpt[nmuons]/F");
  T1->Branch("muonp",muonp,"muonp[nmuons]/F");
  T1->Branch("muoneta",muoneta,"muoneta[nmuons]/F");
  T1->Branch("muonphi",muonphi,"muonphi[nmuons]/F");
  T1->Branch("muontrkvtx",muontrkvtx,"muontrkvtx[nmuons]/F");
  T1->Branch("muondz",muondz,"muondz[nmuons]/F");
  T1->Branch("muonpter",muonpter,"muonpter[nmuons]/F");
  T1->Branch("muonchi",muonchi,"muonchi[nmuons]/F");
  T1->Branch("muonndf",muonndf,"muonndf[nmuons]/I");
  T1->Branch("muonecal",muonecal,"muonecal[nmuons]/F");
  T1->Branch("muonhcal",muonhcal,"muonhcal[nmuons]/F");
  T1->Branch("muonpfiso",muonpfiso,"muonpfiso[nmuons]/F");
  T1->Branch("muonposmatch",muonposmatch,"muonposmatch[nmuons]/F");
  T1->Branch("muontrkink",muontrkink,"muontrkink[nmuons]/F");
  T1->Branch("muonsegcom",muonsegcom,"muonsegcom[nmuons]/F");
  T1->Branch("muonhit",muonhit,"muonhit[nmuons]/F");
  T1->Branch("muonpixhit",muonpixhit,"muonpixhit[nmuons]/F");
  T1->Branch("muonmst",muonmst,"muonmst[nmuons]/F");
  T1->Branch("muontrklay",muontrklay,"muontrklay[nmuons]/F"); 
  T1->Branch("muonvalfrac",muonvalfrac,"muonvalfrac[nmuons]/F"); 
  T1->Branch("mudxy_sv",mudxy_sv,"mudxy_sv[nmuons]/F");

  T1->Branch("Muon_corrected_pt",Muon_corrected_pt,"Muon_corrected_pt[nmuons]/F");
  T1->Branch("Muon_correctedUp_pt",Muon_correctedUp_pt,"Muon_correctedUp_pt[nmuons]/F");
  T1->Branch("Muon_correctedDown_pt",Muon_correctedDown_pt,"Muon_correctedDown_pt[nmuons]/F");

  // Electron info //
  
  T1->Branch("nelecs",&nelecs,"nelecs/I");
  T1->Branch("elsupcl_eta",elsupcl_eta,"elsupcl_eta[nelecs]/F");
  T1->Branch("elsupcl_phi",elsupcl_phi,"elsupcl_phi[nelecs]/F");
  T1->Branch("elsupcl_rawE",elsupcl_rawE,"elsupcl_rawE[nelecs]/F");
  T1->Branch("elsupcl_e",elsupcl_e,"elsupcl_e[nelecs]/F");
  T1->Branch("elpt",elpt,"elpt[nelecs]/F");
  //T1->Branch("elcharge", elcharge, "elcharge[nelecs]/F");
  //new 20 variables added//
  T1->Branch("elsigmaieta", elsigmaieta, "elsigmaieta[nelecs]/F");
  T1->Branch("elsigmaiphi", elsigmaiphi, "elsigmaiphi[nelecs]/F");
  T1->Branch("elr9full", elr9full, "elr9full[nelecs]/F");
  T1->Branch("elsupcl_etaw", elsupcl_etaw, "elsupcl_etaw[nelecs]/F");
  T1->Branch("elsupcl_phiw", elsupcl_phiw, "elsupcl_phiw[nelecs]/F");
  T1->Branch("elhcaloverecal", elhcaloverecal, "elhcaloverecal[nelecs]/F");
  T1->Branch("elcloctftrkn", elcloctftrkn, "elcloctftrkn[nelecs]/F");
  T1->Branch("elcloctftrkchi2", elcloctftrkchi2, "elcloctftrkchi2[nelecs]/F");
  T1->Branch("ele1x5bye5x5", ele1x5bye5x5, "ele1x5bye5x5[nelecs]/F");
  T1->Branch("elnormchi2", elnormchi2, "elnormchi2[nelecs]/F");
  T1->Branch("elhitsmiss", elhitsmiss, "elhitsmiss[nelecs]/F");
  T1->Branch("eltrkmeasure", eltrkmeasure, "eltrkmeasure[nelecs]/F");
  T1->Branch("elconvtxprob", elconvtxprob, "elconvtxprob[nelecs]/F");
  T1->Branch("elecloverpout", elecloverpout, "elecloverpout[nelecs]/F");
  T1->Branch("elecaletrkmomentum", elecaletrkmomentum, "elecaletrkmomentum[nelecs]/F");
  T1->Branch("eldeltaetacltrkcalo", eldeltaetacltrkcalo, "eldeltaetacltrkcalo[nelecs]/F");
  T1->Branch("elsupcl_preshvsrawe", elsupcl_preshvsrawe, "elsupcl_preshvsrawe[nelecs]/F");
  T1->Branch("elpfisolsumphet", elpfisolsumphet, "elpfisolsumphet[nelecs]/F");
  T1->Branch("elpfisolsumchhadpt", elpfisolsumchhadpt, "elpfisolsumchhadpt[nelecs]/F");
  T1->Branch("elpfsiolsumneuhadet", elpfsiolsumneuhadet, "elpfsiolsumneuhadet[nelecs]/F");
  ///20 variables addition ended//
  T1->Branch("eleta",eleta,"eleta[nelecs]/F");
  T1->Branch("elphi",elphi,"elphi[nelecs]/F");
  T1->Branch("elp",elp,"elp[nelecs]/F");
  T1->Branch("ele",ele,"ele[nelecs]/F");
  T1->Branch("elmvaid",elmvaid,"elmvaid[nelecs]/O");
  T1->Branch("elmvaid_noIso",elmvaid_noIso,"elmvaid_noIso[nelecs]/O");
  T1->Branch("elmvaid_wpLoose",elmvaid_wpLoose,"elmvaid_wpLoose[nelecs]/O");
  T1->Branch("elmvaid_noIso_wpLoose",elmvaid_wpLoose_noIso,"elmvaid_wpLoose_noIso[nelecs]/O");
  T1->Branch("elmvaid_Fallv2WP80",elmvaid_Fallv2WP80,"elmvaid_Fallv2WP80[nelecs]/O");
  T1->Branch("elmvaid_Fallv2WP80_noIso",elmvaid_Fallv2WP80_noIso,"elmvaid_Fallv2WP80_noIso[nelecs]/O");
  T1->Branch("elcutid_veto",elcutid_veto,"elcutid_veto[nelecs]/O");
  T1->Branch("elcutid_loose",elcutid_loose,"elcutid_loose[nelecs]/O");
  T1->Branch("elcutid_med",elcutid_med,"elcutid_med[nelecs]/O");
  T1->Branch("elcutid_tight",elcutid_tight,"elcutid_tight[nelecs]/O");
  T1->Branch("eldxytrk",eldxytrk,"eldxytrk[nelecs]/F");
  T1->Branch("eldxy_sv",eldxy_sv,"eldxy_sv[nelecs]/F");
  T1->Branch("eldztrk",eldztrk,"eldztrk[nelecs]/F");
  T1->Branch("elhovere",elhovere,"elhovere[nelecs]/F");
  T1->Branch("elchi",elchi,"elchi[nelecs]/F");
  T1->Branch("elndf",elndf,"elndf[nelecs]/I");
  T1->Branch("eletain",eletain,"eletain[nelecs]/F");
  T1->Branch("elphiin",elphiin,"elphiin[nelecs]/F");
  T1->Branch("elfbrem",elfbrem,"elfbrem[nelecs]/F");
  T1->Branch("eleoverp",eleoverp,"eleoverp[nelecs]/F");
  T1->Branch("elietaieta",elietaieta,"elietaieta[nelecs]/F");
  T1->Branch("elmisshits",elmisshits,"elmisshits[nelecs]/F");
  T1->Branch("elpfiso",elpfiso,"elpfiso[nelecs]/F");

  if(store_electron_scalnsmear){
    T1->Branch("Electron_eccalTrkEnergyPostCorr",Electron_eccalTrkEnergyPostCorr,"Electron_eccalTrkEnergyPostCorr[nelecs]/F");
    T1->Branch("Electron_energyScaleValue",Electron_energyScaleValue,"Electron_energyScaleValue[nelecs]/F");
    T1->Branch("Electron_energyScaleUp",Electron_energyScaleUp,"Electron_energyScaleUp[nelecs]/F");
    T1->Branch("Electron_energyScaleDown",Electron_energyScaleDown,"Electron_energyScaleDown[nelecs]/F");
    T1->Branch("Electron_energySigmaValue",Electron_energySigmaValue,"Electron_energySigmaValue[nelecs]/F");
    T1->Branch("Electron_energySigmaUp",Electron_energySigmaUp,"Electron_energySigmaUp[nelecs]/F");
    T1->Branch("Electron_energySigmaDown",Electron_energySigmaDown,"Electron_energySigmaDown[nelecs]/F");
  }

  T2 = new TTree("Events_All", "XtoYH");
  
  T2->Branch("ievt", &ievt, "ievt/i");
  
  if(isMC){
    T2->Branch("npu_vert",&npu_vert,"npu_vert/I");
    T2->Branch("npu_vert_true",&npu_vert_true,"npu_vert_true/I");  
    T2->Branch("Generator_weight", &Generator_weight, "Generator_weight/D") ;
    T2->Branch("LHE_weight",&LHE_weight, "LHE_weight/D");
    
  }
  
  Nevt=0;
  ncnt = 0;
  irunold = -1;
}


Leptop::~Leptop()
{
 
  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
Leptop::analyze(const edm::Event& iEvent, const edm::EventSetup& pset) {
  
  using namespace edm;
  Nevt++;
  
  irun = iEvent.id().run();
  ilumi = iEvent.luminosityBlock();
  
  ievt = iEvent.id().event();
  
  //if (Nevt%100==1)cout <<"Leptop::analyze "<<Nevt<<" "<<iEvent.id().run()<<" "<<iEvent.id().event()<<endl;
  
  wtfact = 1.;
  
  npu_vert = npu_vert_true = 0;
  
  if(isMC){
	
    // GEN info //
		
    edm::Handle<GenEventInfoProduct>eventinfo ;  
    iEvent.getByToken(tok_wt_,eventinfo) ;

    nLHEPSWeights = 0;
    
    if (eventinfo.isValid()){
		
      Generator_weight = eventinfo->weight();
      qscale = eventinfo->qScale();
      wtfact *= Generator_weight; //Debarati : Moved inside according to GMA

      // Generator information //
      Generator_x1 = (*eventinfo->pdf()).x.first;
      Generator_x2 = (*eventinfo->pdf()).x.second;
      Generator_id1 = (*eventinfo->pdf()).id.first;
      Generator_id2 = (*eventinfo->pdf()).id.second;
      Generator_xpdf1 = (*eventinfo->pdf()).xPDF.first;
      Generator_xpdf2 = (*eventinfo->pdf()).xPDF.second;
      Generator_scalePDF = (*eventinfo->pdf()).scalePDF;
       
      //cout<<"eventinfo->weights().size() "<<eventinfo->weights().size()<<" GEN weight "<<Generator_weight<<endl;
        
      // Parton shower weights //
      if(eventinfo->weights().size()>2){
	for(unsigned int i=2; i<eventinfo->weights().size(); ++i){
	  LHEPSWeights[nLHEPSWeights] = eventinfo->weights()[i]/eventinfo->weights()[1];
	  nLHEPSWeights++;
	  if(nLHEPSWeights >= nlhepsmax) break;
	}
      }
    }
    else
      {
	Generator_weight = qscale = wtfact = Generator_x1 = Generator_x2 = Generator_id1 = Generator_id2 = Generator_xpdf1 = Generator_xpdf2 = Generator_scalePDF = 0.0;
      }
    
    // LHE info //
    
    edm::Handle<LHEEventProduct>lheeventinfo ;
    iEvent.getByToken(lheEventProductToken_,lheeventinfo) ;
    
    if(lheeventinfo.isValid()){
      
      const auto & hepeup = lheeventinfo->hepeup();
      const auto & pup = hepeup.PUP;

      nLHEAllWeights = 0;
      nLHEScaleWeights = 0;
      nLHEPDFWeights = 0;
      nLHEAlpsWeights = 0;
    
      nLHEparticles = 0;
      
      for (unsigned int i = 0; i  < pup.size(); ++i) {
	if(hepeup.ISTUP[i]==1){// status==1 --> particles stay up to final state                          
	    TLorentzVector p4(pup[i][0], pup[i][1], pup[i][2], pup[i][3]);
	  LHEpartpt[nLHEparticles] = p4.Pt();
	  LHEparteta[nLHEparticles] = p4.Eta();
	  LHEpartphi[nLHEparticles] = p4.Phi();
	  LHEpartm[nLHEparticles] = p4.M();
	  LHEpartpdg[nLHEparticles] = (hepeup.IDUP[i]);
	  nLHEparticles++;
	  if(nLHEparticles>=nlhemax) break;
	}
      }
      // LHE-level weights //
      
      LHE_weight =  lheeventinfo->originalXWGTUP();
      if (LHE_weight >0) {
	LHE_weight = max(1.e-12, LHE_weight);
      } else {
	LHE_weight = min(-1.e-12, LHE_weight);
      } 
      
      for ( unsigned int index = 0; index < lheeventinfo->weights().size(); ++index ) {	
	//cout<<"Index "<<index+1<<" Id "<<lheeventinfo->weights()[index].id<<" weight "<<lheeventinfo->weights()[index].wgt/LHE_weight<<" muR "<<lheeventinfo->weights()[index].MUR<<" muF "<<lheeventinfo->weights()[index].MUF<<" DYN Scale "<<lheeventinfo->weights()[index].DYN_SCALE<<endl;

	if(index < nlheallweightsmax)
	  {
	    LHEAllWeights[nLHEAllWeights] = lheeventinfo->weights()[index].wgt;
	    nLHEAllWeights++;
	  }
	else break;
	
	if(index<nlhescalemax && nLHEScaleWeights<nlhescalemax){
	  LHEScaleWeights[nLHEScaleWeights] = lheeventinfo->weights()[index].wgt/LHE_weight;
	  nLHEScaleWeights++;
	}
	if(index>=nlhescalemax && index<(nlhescalemax+nPDFsets)  && nLHEPDFWeights<nlhepdfmax){
	  LHEPDFWeights[nLHEPDFWeights] = lheeventinfo->weights()[index].wgt/LHE_weight;
	  nLHEPDFWeights++;
	}
	if(index>=(nlhescalemax+nPDFsets) && index<(nlhescalemax+nPDFsets+nalpsmax) && nLHEAlpsWeights<nalpsmax){
	  LHEAlpsWeights[nLHEAlpsWeights] = lheeventinfo->weights()[index].wgt/LHE_weight;
	  nLHEAlpsWeights++;
	}
      }
      
    }//lheeventinfo
    
    // pileup information
    
    edm::Handle<std::vector<PileupSummaryInfo> > PupInfo;
    iEvent.getByToken(pileup_, PupInfo);
    if (PupInfo.isValid()) {
      std::vector<PileupSummaryInfo>::const_iterator PVI;
      for(PVI = PupInfo->begin(); PVI != PupInfo->end(); ++PVI) {
	if (PVI->getBunchCrossing()==0) {
	  npu_vert = PVI->getPU_NumInteractions();
	  npu_vert_true = PVI->getTrueNumInteractions();
	  break;
	}
      }
    }
  
  }//isMC

  Handle<VertexCollection> primaryVertices;
  iEvent.getByToken(tok_primaryVertices_, primaryVertices);
  reco::Vertex vertex;
  
  if (primaryVertices.isValid()) {
	  
    vertex = primaryVertices->at(0);  
    int ndofct_org=0;
    int nchict_org=0;
    int nvert_org = 0;
    int nprimi_org = 0;
    
    for (reco::VertexCollection::const_iterator vert=primaryVertices->begin(); vert<primaryVertices->end(); vert++) {
      nvert_org++;
      if (vert->isValid() && !vert->isFake()) {
	if (vert->ndof() > 4 && fabs(vert->position().z()) <= 24 && fabs(vert->position().Rho()) <= 2) {
	  nprimi_org++;
	}
	if (vert->ndof()>7) {
	  ndofct_org++;
	  if (vert->normalizedChi2()<5) nchict_org++;
	}
      }
    }
	
    nprim = min(999,nvert_org) + 1000*min(999,ndofct_org) + 1000000*min(999,nchict_org);
    //nvert = nvert_org;
    //nchict = nchict_org;
    //ndofct = ndofct_org;
    nprimi = nprimi_org;
    
  } else { 
    nprim = 0;
    nprimi = 0;
    //nvert = nchict = ndofct = 0;
  }
  
  reco::TrackBase::Point beamPoint(0,0, 0);
  edm::Handle<reco::BeamSpot> beamSpotH;
  
  iEvent.getByToken(tok_beamspot_, beamSpotH);  //Label("offlineBeamSpot",beamSpotH);
  if (beamSpotH.isValid()){
    beamPoint = beamSpotH->position();
  }

  edm::Handle<reco::VertexCompositePtrCandidateCollection> svin;
  iEvent.getByToken(tok_sv,svin);
  
  edm::Handle<double> Rho_PF;
  
  iEvent.getByToken(tok_Rho_,Rho_PF);
  Rho = *Rho_PF;
  
  const char* variab1;
  
  edm::Handle<edm::TriggerResults> trigRes;
  iEvent.getByToken(triggerBits_, trigRes);
  
  const edm::TriggerNames &names = iEvent.triggerNames(*trigRes);
  
  edm::Handle<pat::TriggerObjectStandAloneCollection> triggerObjects;
  iEvent.getByToken(triggerObjects_, triggerObjects);
  
  edm::Handle<pat::PackedTriggerPrescales> triggerPrescales;
  iEvent.getByToken(triggerPrescales_, triggerPrescales);
  
  int ihlttrg[nHLTmx+1]= {0};
  bool booltrg[nHLTmx]= {false};
  float psfactor_booltrg[nHLTmx];
  fill_n(booltrg, nHLTmx, false);
  fill_n(psfactor_booltrg, nHLTmx, 0);
  ps_column = hltPrescaleProvider_.prescaleSet(iEvent,pset);
    
  for (int jk=0; jk<nHLTmx; jk++) {
    for(unsigned ij = 0; ij<trigRes->size(); ++ij) {
      std::string name = names.triggerName(ij);
      variab1 = name.c_str(); 
      if (strstr(variab1,hlt_name[jk]) && ((strlen(variab1)-strlen(hlt_name[jk]))<5))
	{
	  if ((trigRes->accept(ij))){   //||(isMC)) {
	    ihlttrg[jk] = ihlttrg[nHLTmx] = 1;
	    booltrg[jk] = true;
	    psfactor_booltrg[jk] = hltPrescaleProvider_.prescaleValue( iEvent, pset, name);
	    break;
	  }
	}
    }//ij     
	 }//jk
  
  trig_value = 1; //In meeting
  
  for (int jk=1; jk<(nHLTmx+1); jk++) {
    if(ihlttrg[nHLTmx-jk]>0) {
      trig_value+=(1<<jk);
    }
  }
  
  vector<triggervar> alltrgobj;
  if (trigRes.isValid()) { 
    
    const char* variab2 ;
    
    alltrgobj.clear(); 
    
    for (pat::TriggerObjectStandAlone obj : *triggerObjects) {
      
      obj.unpackPathNames(names);
      std::vector<std::string> pathNamesAll  = obj.pathNames(false);
      
      for (unsigned ih = 0, n = pathNamesAll.size(); ih < n; ih++) {
	
	variab2 = pathNamesAll[ih].c_str(); 
	
	for (int jk=0; jk<nHLTmx; jk++) {
	  if (strstr(variab2,hlt_name[jk]) && (strlen(variab2)-strlen(hlt_name[jk])<5)) {
	    
	    if(obj.pt()>20 && fabs(obj.eta())<3.0) {
	      
	      triggervar tmpvec1;
	      
	      tmpvec1.both = obj.hasPathName( pathNamesAll[ih], true, true );
	      tmpvec1.highl  = obj.hasPathName( pathNamesAll[ih], false, true );
	      tmpvec1.level1 = obj.hasPathName( pathNamesAll[ih], true, false );
	      tmpvec1.trg4v = TLorentzVector(obj.px(), obj.py(), obj.pz(), obj.energy());
	      tmpvec1.pdgId = obj.pdgId();
	      tmpvec1.prescl = 1;//triggerPrescales->getPrescaleForIndex(ih);
	      tmpvec1.ihlt = jk;
	      alltrgobj.push_back(tmpvec1);
	      break;
				
	    }
	  }
	}//jk 
	     }//ih
    }
  }
  
  int xht=0;
  ntrigobjs = alltrgobj.size();
  if(ntrigobjs>njetmx) { ntrigobjs = njetmx; }
  if(ntrigobjs > 0){
    for(unsigned int iht=0; iht<(unsigned int)ntrigobjs; iht++){
      if(alltrgobj[iht].trg4v.Pt()>20 && fabs(alltrgobj[iht].trg4v.Eta())<3.0) {
	trigobjpt[xht] = alltrgobj[iht].trg4v.Pt();
	trigobjeta[xht] = alltrgobj[iht].trg4v.Eta();
	trigobjphi[xht] = alltrgobj[iht].trg4v.Phi();
	trigobjmass[xht] = alltrgobj[iht].trg4v.M();
	trigobjHLT[xht] = alltrgobj[iht].highl;
	trigobjL1[xht] = alltrgobj[iht].level1;
	trigobjBoth[xht] = alltrgobj[iht].both;
	trigobjIhlt[xht] = alltrgobj[iht].ihlt;
	//trigobjprescale[xht] = alltrgobj[iht].prescl;
	trigobjpdgId[xht] = alltrgobj[iht].pdgId;
	xht++;
      }
      if(iht == (njetmx-1)) break;
    }
  } 
  
  // Prefire weights //
  
  if(add_prefireweights){
  
    edm::Handle< double > theprefweight;
    iEvent.getByToken(prefweight_token, theprefweight ) ;	
    prefiringweight =(*theprefweight);

    edm::Handle< double > theprefweightup;
    iEvent.getByToken(prefweightup_token, theprefweightup ) ;
    prefiringweightup =(*theprefweightup);
    
    edm::Handle< double > theprefweightdown;
    iEvent.getByToken(prefweightdown_token, theprefweightdown ) ;   
    prefiringweightdown =(*theprefweightdown);
 
  }
  
  // End of prefire weights //
  
  // ====== RECO-objects now  ==========//
  
  // MET //
    
  miset = misphi = misetsig = sumEt = genmiset = genmisphi = genmisetsig = -1000 ;
  miset_UnclusEup = miset_UnclusEdn = -100;
  misphi_UnclusEup = misphi_UnclusEdn = -100;
  
  // MET uncertainty ids are taken from: https://github.com/cms-sw/cmssw/blob/CMSSW_8_0_X/DataFormats/PatCandidates/interface/MET.h#L152-L158 //
  
  // CHS MET //
  
  edm::Handle<pat::METCollection> pfmet_ ;
  iEvent.getByToken(tok_mets_,pfmet_) ;
  
  if(pfmet_.isValid()){
	  
    const pat::MET &met = pfmet_->front();
    
    miset = met.corPt(); //met.pt();
    misphi = met.corPhi();//met.phi();
    misetsig = met.significance();
    sumEt = met.corSumEt();//sumEt();
    
    miset_UnclusEup = met.shiftedPt(pat::MET::METUncertainty(10));
    miset_UnclusEdn = met.shiftedPt(pat::MET::METUncertainty(11));
	
    misphi_UnclusEup = met.shiftedPhi(pat::MET::METUncertainty(10));
    misphi_UnclusEdn = met.shiftedPhi(pat::MET::METUncertainty(11));
	    
    if(isMC){
      genmiset = met.genMET()->pt();
      genmisphi = met.genMET()->phi();
      genmisetsig = met.genMET()->significance();
    }
  }
  
  // PUPPI MET //
  
  edm::Handle<pat::METCollection> pfmet_PUPPI_ ;
  iEvent.getByToken(tok_mets_PUPPI_,pfmet_PUPPI_) ;
  
  miset_PUPPI = misphi_PUPPI = misetsig_PUPPI = sumEt_PUPPI = -100;
  miset_PUPPI_JESup = miset_PUPPI_JESdn = miset_PUPPI_JERup = miset_PUPPI_JERdn = miset_PUPPI_UnclusEup = miset_PUPPI_UnclusEdn = -100;
  misphi_PUPPI_JESup = misphi_PUPPI_JESdn = misphi_PUPPI_JERup = misphi_PUPPI_JERdn = misphi_PUPPI_UnclusEup = misphi_PUPPI_UnclusEdn = -100;
  
  if(pfmet_PUPPI_.isValid()){
	
    const pat::MET &met = pfmet_PUPPI_->front();
	  
    miset_PUPPI = met.corPt(); 
    misphi_PUPPI = met.corPhi();
    misetsig_PUPPI = met.significance();
    sumEt_PUPPI = met.corSumEt();
    
    miset_PUPPI_JESup = met.shiftedPt(pat::MET::METUncertainty(2));
    miset_PUPPI_JESdn = met.shiftedPt(pat::MET::METUncertainty(3));
    miset_PUPPI_JERup = met.shiftedPt(pat::MET::METUncertainty(0));
    miset_PUPPI_JERdn = met.shiftedPt(pat::MET::METUncertainty(1));
    miset_PUPPI_UnclusEup = met.shiftedPt(pat::MET::METUncertainty(10));
    miset_PUPPI_UnclusEdn = met.shiftedPt(pat::MET::METUncertainty(11));
	
    misphi_PUPPI_JESup = met.shiftedPhi(pat::MET::METUncertainty(2));
    misphi_PUPPI_JESdn = met.shiftedPhi(pat::MET::METUncertainty(3));
    misphi_PUPPI_JERup = met.shiftedPhi(pat::MET::METUncertainty(0));
    misphi_PUPPI_JERdn = met.shiftedPhi(pat::MET::METUncertainty(1));
    misphi_PUPPI_UnclusEup = met.shiftedPhi(pat::MET::METUncertainty(10));
    misphi_PUPPI_UnclusEdn = met.shiftedPhi(pat::MET::METUncertainty(11));
	
    //See DataFormats/PatCandidates/interface/MET.h for the names of uncertainty sources //
	
  }
 
  
  edm::Handle<edm::View<pat::Jet>> pfjetAK8s;
  edm::Handle<reco::GenJetCollection> genjetAK8s;
  edm::Handle<edm::View<pat::Jet>> pfsubjetAK8s;
  
  JetDefinition pfjetAK8Def(antikt_algorithm,0.8,E_scheme);
  SoftDrop sd(beta,z_cut,0.8);
    
  edm::Handle<edm::View<pat::Jet>> pfjetAK4s;
  edm::Handle<reco::GenJetCollection> genjetAK4s;
  
  edm::Handle<std::vector<reco::GenParticle>> genparticles;
  edm::Handle<pat::PackedCandidateCollection> pfs;
  iEvent.getByToken(tok_pfcands_, pfs);
  
  npfjetAK8 = 0;
  
  iEvent.getByToken(tok_pfjetAK8s_, pfjetAK8s);	
  if(isMC){
    iEvent.getByToken(tok_genjetAK8s_, genjetAK8s);
  }
  
  if(pfjetAK8s.isValid()){
    
    for (unsigned jet = 0; jet< pfjetAK8s->size(); jet++) {
      
      const auto &ak8jet = (*pfjetAK8s)[jet];

      TLorentzVector pfjetAK84v(ak8jet.correctedP4("Uncorrected").px(),ak8jet.correctedP4("Uncorrected").py(),ak8jet.correctedP4("Uncorrected").pz(), ak8jet.correctedP4("Uncorrected").energy());
      TLorentzVector tmpjetAK84v(ak8jet.px(),ak8jet.py(),ak8jet.pz(), ak8jet.energy());

      double tmprecpt = pfjetAK84v.Pt();
      
      double total_cor =1;
      
      jecL1FastAK8->setJetPt(tmprecpt); jecL1FastAK8->setJetA(ak8jet.jetArea()); jecL1FastAK8->setRho(*Rho_PF);jecL1FastAK8->setJetEta(pfjetAK84v.Eta());
      double corFactorL1Fast = jecL1FastAK8->getCorrection();
      total_cor *= corFactorL1Fast;
      tmprecpt = tmprecpt * corFactorL1Fast;
      
      jecL2RelativeAK8->setJetPt(tmprecpt); jecL2RelativeAK8->setJetEta(pfjetAK84v.Eta());
      double corFactorL2Relative = jecL2RelativeAK8->getCorrection();
      total_cor *= corFactorL2Relative ;
      tmprecpt = tmprecpt * corFactorL2Relative;
      
      jecL3AbsoluteAK8->setJetPt(tmprecpt); jecL3AbsoluteAK8->setJetEta(pfjetAK84v.Eta());
      double corFactorL3Absolute = jecL3AbsoluteAK8->getCorrection();
      total_cor *= corFactorL3Absolute ;
      tmprecpt = tmprecpt * corFactorL3Absolute;
      
      double corFactorL2L3Residual=1.;
      
      if(isData){
	jecL2L3ResidualAK8->setJetPt(tmprecpt); jecL2L3ResidualAK8->setJetEta(pfjetAK84v.Eta());
	corFactorL2L3Residual = jecL2L3ResidualAK8->getCorrection();
	total_cor*= corFactorL2L3Residual;
	tmprecpt *=corFactorL2L3Residual;
      }
      
      pfjetAK8JEC[npfjetAK8] = total_cor;
      
      if(tmprecpt <AK8PtCut) continue;
      if(abs(pfjetAK84v.Eta())>maxEta) continue;
      
      pfjetAK8pt[npfjetAK8] = 	pfjetAK84v.Pt();
      pfjetAK8y[npfjetAK8] = pfjetAK84v.Rapidity();
      pfjetAK8eta[npfjetAK8] = pfjetAK84v.Eta();
      pfjetAK8phi[npfjetAK8] = pfjetAK84v.Phi();
      pfjetAK8mass[npfjetAK8] = ak8jet.correctedP4("Uncorrected").mass();
      
      pfjetAK8btag_DeepCSV[npfjetAK8] = ak8jet.bDiscriminator("pfDeepCSVJetTags:probb")+ak8jet.bDiscriminator("pfDeepCSVJetTags:probbb");
      pfjetAK8DeepTag_DAK8_TvsQCD[npfjetAK8] = ak8jet.bDiscriminator(toptagger_DAK8);
      pfjetAK8DeepTag_DAK8_WvsQCD[npfjetAK8] = ak8jet.bDiscriminator(Wtagger_DAK8);
      pfjetAK8DeepTag_DAK8_ZvsQCD[npfjetAK8] = ak8jet.bDiscriminator(Ztagger_DAK8);
      
      pfjetAK8DeepTag_PNet_TvsQCD[npfjetAK8] = ak8jet.bDiscriminator(toptagger_PNet);
      pfjetAK8DeepTag_PNet_WvsQCD[npfjetAK8] = ak8jet.bDiscriminator(Wtagger_PNet);
     
      if(isMC){
	
	JME::JetResolution resolution_AK8;
	resolution_AK8 = JME::JetResolution(mPtResoFileAK8.c_str());
	JME::JetResolutionScaleFactor res_sf_AK8;
	res_sf_AK8 = JME::JetResolutionScaleFactor(mPtSFFileAK8.c_str());
	
	JME::JetParameters parameters_5 = {{JME::Binning::JetPt, tmprecpt}, {JME::Binning::JetEta, pfjetAK84v.Eta()}, {JME::Binning::Rho, *Rho_PF}};
	double rp_AK8 = resolution_AK8.getResolution(parameters_5);
	double gaus_rp_AK8 = gRandom->Gaus(0.,rp_AK8);
	double sf_AK8 = res_sf_AK8.getScaleFactor(parameters_5, Variation::NOMINAL);
	double sf_up_AK8= res_sf_AK8.getScaleFactor(parameters_5, Variation::UP);
	double sf_dn_AK8= res_sf_AK8.getScaleFactor(parameters_5, Variation::DOWN);
	
	bool match_AK8 = false;
	int match_gen_AK8 = -1;
	
	for (unsigned get = 0; get<(genjetAK8s->size()); get++) {
	  TLorentzVector genjet8v((*genjetAK8s)[get].px(),(*genjetAK8s)[get].py(),(*genjetAK8s)[get].pz(), (*genjetAK8s)[get].energy());
	  if((delta2R(pfjetAK84v.Rapidity(),pfjetAK84v.Phi(),genjet8v.Rapidity(),genjet8v.Phi()) < (0.5*0.8)) &&(fabs(tmprecpt-genjet8v.Pt())<(3*fabs(rp_AK8)*tmprecpt))){
	    match_AK8 = true;
	    match_gen_AK8 = get;
	    break;
	  }
	}
	
	if(match_AK8&&(match_gen_AK8>=0)){
	  pfjetAK8reso[npfjetAK8] = (sf_AK8-1.)*(tmprecpt-(*genjetAK8s)[match_gen_AK8].pt())*1./tmprecpt;
	  pfjetAK8resoup[npfjetAK8] = (sf_up_AK8-1.)*(tmprecpt-(*genjetAK8s)[match_gen_AK8].pt())*1./tmprecpt;
	  pfjetAK8resodn[npfjetAK8] = (sf_dn_AK8-1.)*(tmprecpt-(*genjetAK8s)[match_gen_AK8].pt())*1./tmprecpt;
	  
	}else{
	  pfjetAK8reso[npfjetAK8] = sqrt(max(0.,(sf_AK8*sf_AK8-1))) * gaus_rp_AK8;
	  pfjetAK8resoup[npfjetAK8] = sqrt(max(0.,(sf_up_AK8*sf_up_AK8-1))) * gaus_rp_AK8;
	  pfjetAK8resodn[npfjetAK8] = sqrt(max(0.,(sf_dn_AK8*sf_dn_AK8-1))) * gaus_rp_AK8;
	}
      	
      }//isMC
      
      // JES uncertainty //

      pfjetAK8jesup_AbsoluteStat[npfjetAK8] = pfjetAK8jesup_AbsoluteScale[npfjetAK8] = pfjetAK8jesup_AbsoluteMPFBias[npfjetAK8] = pfjetAK8jesup_FlavorQCD[npfjetAK8] = pfjetAK8jesup_Fragmentation[npfjetAK8] = pfjetAK8jesup_PileUpDataMC[npfjetAK8] = pfjetAK8jesup_PileUpPtBB[npfjetAK8] = pfjetAK8jesup_PileUpPtEC1[npfjetAK8] = pfjetAK8jesup_PileUpPtEC2[npfjetAK8] = pfjetAK8jesup_PileUpPtHF[npfjetAK8] = pfjetAK8jesup_PileUpPtRef[npfjetAK8] = pfjetAK8jesup_RelativeFSR[npfjetAK8] = pfjetAK8jesup_RelativeJEREC1[npfjetAK8] = pfjetAK8jesup_RelativeJEREC2[npfjetAK8] = pfjetAK8jesup_RelativeJERHF[npfjetAK8] = pfjetAK8jesup_RelativePtBB[npfjetAK8] = pfjetAK8jesup_RelativePtEC1[npfjetAK8] = pfjetAK8jesup_RelativePtEC2[npfjetAK8] = pfjetAK8jesup_RelativePtHF[npfjetAK8] = pfjetAK8jesup_RelativeBal[npfjetAK8] = pfjetAK8jesup_RelativeSample[npfjetAK8] = pfjetAK8jesup_RelativeStatEC[npfjetAK8] = pfjetAK8jesup_RelativeStatHF[npfjetAK8] = pfjetAK8jesup_RelativeStatFSR[npfjetAK8] = pfjetAK8jesup_SinglePionECAL[npfjetAK8] = pfjetAK8jesup_SinglePionHCAL[npfjetAK8] = pfjetAK8jesup_TimePtEta[npfjetAK8] = pfjetAK8jesup_Total[npfjetAK8] = 1;
      
      for(int isrc =0 ; isrc<njecmcmx; isrc++){
	
        double sup = 1.0 ;
	
	if((isrc>0)&&(isrc<=nsrc)){
		  
	  JetCorrectionUncertainty *jecUnc = vsrcAK8[isrc-1];
	  jecUnc->setJetEta(ak8jet.eta());
	  jecUnc->setJetPt(tmprecpt);
		  
	  sup += jecUnc->getUncertainty(true);
	  switch(isrc){
	  case 1:  pfjetAK8jesup_AbsoluteStat[npfjetAK8] = sup; break;
	  case 2:  pfjetAK8jesup_AbsoluteScale[npfjetAK8] = sup; break;
	  case 3:  pfjetAK8jesup_AbsoluteMPFBias[npfjetAK8] = sup; break;
	  case 4:  pfjetAK8jesup_FlavorQCD[npfjetAK8] = sup; break;
	  case 5:  pfjetAK8jesup_Fragmentation[npfjetAK8] = sup; break;
	  case 6:  pfjetAK8jesup_PileUpDataMC[npfjetAK8] = sup; break;
	  case 7:  pfjetAK8jesup_PileUpPtBB[npfjetAK8] = sup; break;
	  case 8:  pfjetAK8jesup_PileUpPtEC1[npfjetAK8] = sup; break;
	  case 9:  pfjetAK8jesup_PileUpPtEC2[npfjetAK8] = sup; break;
	  case 10:  pfjetAK8jesup_PileUpPtHF[npfjetAK8] = sup; break;
	  case 11:  pfjetAK8jesup_PileUpPtRef[npfjetAK8] = sup; break;
	  case 12:  pfjetAK8jesup_RelativeFSR[npfjetAK8] = sup; break;
	  case 13:  pfjetAK8jesup_RelativeJEREC1[npfjetAK8] = sup; break;
	  case 14:  pfjetAK8jesup_RelativeJEREC2[npfjetAK8] = sup; break;
	  case 15:  pfjetAK8jesup_RelativeJERHF[npfjetAK8] = sup; break;
	  case 16:  pfjetAK8jesup_RelativePtBB[npfjetAK8] = sup; break;
	  case 17:  pfjetAK8jesup_RelativePtEC1[npfjetAK8] = sup; break;
	  case 18:  pfjetAK8jesup_RelativePtEC2[npfjetAK8] = sup; break;
	  case 19:  pfjetAK8jesup_RelativePtHF[npfjetAK8] = sup; break;
	  case 20:  pfjetAK8jesup_RelativeBal[npfjetAK8] = sup; break;
	  case 21:  pfjetAK8jesup_RelativeSample[npfjetAK8] = sup; break;
	  case 22:  pfjetAK8jesup_RelativeStatEC[npfjetAK8] = sup; break;
	  case 23:  pfjetAK8jesup_RelativeStatHF[npfjetAK8] = sup; break;
	  case 24:  pfjetAK8jesup_RelativeStatFSR[npfjetAK8] = sup; break;
	  case 25:  pfjetAK8jesup_SinglePionECAL[npfjetAK8] = sup; break;
	  case 26:  pfjetAK8jesup_SinglePionHCAL[npfjetAK8] = sup; break;
	  case 27:  pfjetAK8jesup_TimePtEta[npfjetAK8] = sup; break;
	  case 28:  pfjetAK8jesup_Total[npfjetAK8] = sup; break;
	  default: continue;
	  }
	}
	else if(isrc>nsrc){
		  
	  JetCorrectionUncertainty *jecUnc = vsrcAK8[isrc-1-nsrc];
	  jecUnc->setJetEta(ak8jet.eta());
	  jecUnc->setJetPt(tmprecpt);
		  
	  sup -= jecUnc->getUncertainty(false);
		  
	  switch(isrc){
	  case (nsrc+1):  pfjetAK8jesdn_AbsoluteStat[npfjetAK8] = sup; break;
	  case (nsrc+2):  pfjetAK8jesdn_AbsoluteScale[npfjetAK8] = sup; break;
	  case (nsrc+3):  pfjetAK8jesdn_AbsoluteMPFBias[npfjetAK8] = sup; break;
	  case (nsrc+4):  pfjetAK8jesdn_FlavorQCD[npfjetAK8] = sup; break;
	  case (nsrc+5):  pfjetAK8jesdn_Fragmentation[npfjetAK8] = sup; break;
	  case (nsrc+6):  pfjetAK8jesdn_PileUpDataMC[npfjetAK8] = sup; break;
	  case (nsrc+7):  pfjetAK8jesdn_PileUpPtBB[npfjetAK8] = sup; break;
	  case (nsrc+8):  pfjetAK8jesdn_PileUpPtEC1[npfjetAK8] = sup; break;
	  case (nsrc+9):  pfjetAK8jesdn_PileUpPtEC2[npfjetAK8] = sup; break;
	  case (nsrc+10):  pfjetAK8jesdn_PileUpPtHF[npfjetAK8] = sup; break;
	  case (nsrc+11):  pfjetAK8jesdn_PileUpPtRef[npfjetAK8] = sup; break;
	  case (nsrc+12):  pfjetAK8jesdn_RelativeFSR[npfjetAK8] = sup; break;
	  case (nsrc+13):  pfjetAK8jesdn_RelativeJEREC1[npfjetAK8] = sup; break;
	  case (nsrc+14):  pfjetAK8jesdn_RelativeJEREC2[npfjetAK8] = sup; break;
	  case (nsrc+15):  pfjetAK8jesdn_RelativeJERHF[npfjetAK8] = sup; break;
	  case (nsrc+16):  pfjetAK8jesdn_RelativePtBB[npfjetAK8] = sup; break;
	  case (nsrc+17):  pfjetAK8jesdn_RelativePtEC1[npfjetAK8] = sup; break;
	  case (nsrc+18):  pfjetAK8jesdn_RelativePtEC2[npfjetAK8] = sup; break;
	  case (nsrc+19):  pfjetAK8jesdn_RelativePtHF[npfjetAK8] = sup; break;
	  case (nsrc+20):  pfjetAK8jesdn_RelativeBal[npfjetAK8] = sup; break;
	  case (nsrc+21):  pfjetAK8jesdn_RelativeSample[npfjetAK8] = sup; break;
	  case (nsrc+22):  pfjetAK8jesdn_RelativeStatEC[npfjetAK8] = sup; break;
	  case (nsrc+23):  pfjetAK8jesdn_RelativeStatHF[npfjetAK8] = sup; break;
	  case (nsrc+24):  pfjetAK8jesdn_RelativeStatFSR[npfjetAK8] = sup; break;
	  case (nsrc+25):  pfjetAK8jesdn_SinglePionECAL[npfjetAK8] = sup; break;
	  case (nsrc+26):  pfjetAK8jesdn_SinglePionHCAL[npfjetAK8] = sup; break;
	  case (nsrc+27):  pfjetAK8jesdn_TimePtEta[npfjetAK8] = sup; break;
	  case (nsrc+28):  pfjetAK8jesdn_Total[npfjetAK8] = sup; break;
	  default: continue;
	  }
	}
		
      }
      
      // Jet id //      
      
	   pfjetAK8CHF[npfjetAK8] = ak8jet.chargedHadronEnergyFraction();
      pfjetAK8NHF[npfjetAK8] = ak8jet.neutralHadronEnergyFraction();
      pfjetAK8CEMF[npfjetAK8] = ak8jet.chargedEmEnergyFraction();
      pfjetAK8NEMF[npfjetAK8] = ak8jet.neutralEmEnergyFraction();
      pfjetAK8MUF[npfjetAK8] = ak8jet.muonEnergyFraction();
      pfjetAK8PHF[npfjetAK8] = ak8jet.photonEnergyFraction();
      pfjetAK8EEF[npfjetAK8] = ak8jet.electronEnergyFraction();
      pfjetAK8HFHF[npfjetAK8] = ak8jet.HFHadronEnergyFraction();
      
      pfjetAK8CHM[npfjetAK8] = ak8jet.chargedHadronMultiplicity();
      pfjetAK8NHM[npfjetAK8] = ak8jet.neutralHadronMultiplicity();
      pfjetAK8MUM[npfjetAK8] = ak8jet.muonMultiplicity();
      pfjetAK8PHM[npfjetAK8] = ak8jet.photonMultiplicity();
      pfjetAK8EEM[npfjetAK8] = ak8jet.electronMultiplicity();
      pfjetAK8HFHM[npfjetAK8] = ak8jet.HFHadronMultiplicity();
      
      pfjetAK8Chcons[npfjetAK8] = ak8jet.chargedMultiplicity();
      pfjetAK8Neucons[npfjetAK8] = ak8jet.neutralMultiplicity();
      pfjetAK8chrad[npfjetAK8] = 0;
      
      JetIDVars idvars; 
      idvars.NHF = pfjetAK8NHF[npfjetAK8];
      idvars.NEMF = pfjetAK8NEMF[npfjetAK8];
      idvars.MUF = pfjetAK8MUF[npfjetAK8];
      idvars.CHF = pfjetAK8CHF[npfjetAK8];
      idvars.CEMF = pfjetAK8CEMF[npfjetAK8];
      idvars.NumConst = (pfjetAK8Chcons[npfjetAK8]+pfjetAK8Neucons[npfjetAK8]);
      idvars.NumNeutralParticle = pfjetAK8Neucons[npfjetAK8];
      idvars.CHM = pfjetAK8CHM[npfjetAK8];
      
      pfjetAK8jetID[npfjetAK8] = getJetID(idvars,"PUPPI",year,pfjetAK8eta[npfjetAK8],false,isUltraLegacy);
      pfjetAK8jetID_tightlepveto[npfjetAK8] = getJetID(idvars,"PUPPI",year,pfjetAK8eta[npfjetAK8],true,isUltraLegacy);
      
      float sumpt = 0, sumpt2 = 0;
      float leadjtrackpt = -100; //int leadjtrackid = -1;
      
      std::vector<reco::CandidatePtr> daught(ak8jet.daughterPtrVector());
      
      float el_maxpt(-100);
      int el_indx(-100);
      for (unsigned int i3 = 0; i3< daught.size(); ++i3) {
	if (abs((*daught[i3]).pdgId()) == 11){
	  if ((*daught[i3]).pt() > el_maxpt) {
	    el_maxpt = (*daught[i3]).pt();
	    el_indx = i3;
	  }
	}
      }
      if (el_indx >= 0) {
	TLorentzVector elInjet;
	elInjet.SetPtEtaPhiE((*daught[el_indx]).pt(),(*daught[el_indx]).eta(),(*daught[el_indx]).phi(),(*daught[el_indx]).energy());
	pfjetAK8elinpt[npfjetAK8] =  elInjet.Pt();
	pfjetAK8elineta[npfjetAK8] =  elInjet.Eta();
	pfjetAK8elinphi[npfjetAK8] =  elInjet.Phi();
	//if (elInjet.M() < 0.) std::cout << " negative mass value for el " << elInjet.M() << " negative mass value for el pT " << elInjet.Pt() << " negative mass value for el Eta() " << elInjet.Eta() << " " << " negative energy value for el " << elInjet.E() << " raw electron mass " << (*daught[el_indx]).mass() << std::endl;
	pfjetAK8elinmass[npfjetAK8] = elInjet.M();
      }
      else {
	pfjetAK8elinpt[npfjetAK8] = -100;
        pfjetAK8elineta[npfjetAK8] = -100;
        pfjetAK8elinphi[npfjetAK8] = -100; 
	pfjetAK8elinmass[npfjetAK8] = -100;
      }
      
      float mu_maxpt(-100);
      int mu_indx(-100);
      for (unsigned int i4 = 0; i4< daught.size(); ++i4) {
        if (abs((*daught[i4]).pdgId()) == 13){
          if ((*daught[i4]).pt() > mu_maxpt) {
            mu_maxpt = (*daught[i4]).pt();
            mu_indx = i4;
	  }
	}
      }
      if (mu_indx >= 0) {
	TLorentzVector muInjet;
	muInjet.SetPtEtaPhiE((*daught[mu_indx]).pt(),(*daught[mu_indx]).eta(),(*daught[mu_indx]).phi(),(*daught[mu_indx]).energy());
	pfjetAK8muinpt[npfjetAK8] =  muInjet.Pt();
	pfjetAK8muineta[npfjetAK8] =  muInjet.Eta();
        pfjetAK8muinphi[npfjetAK8] =  muInjet.Phi();
	//if (muInjet.M() < 0.) std::cout << " negative mass value for mu " << muInjet.M() << " negative mass value for mu pT " << muInjet.Pt() << " negative mass value for mu Eta() " << muInjet.Eta() << " " << std::endl;
	pfjetAK8muinmass[npfjetAK8] =  muInjet.M();
      }
      else {
	pfjetAK8muinpt[npfjetAK8] = -100;
        pfjetAK8muineta[npfjetAK8] = -100;
	pfjetAK8muinphi[npfjetAK8] = -100;
	pfjetAK8muinmass[npfjetAK8] =  -100;
      }
      
      std::sort(daught.begin(), daught.end(), [](const reco::CandidatePtr &p1, const reco::CandidatePtr &p2)
      { return p1->pt() > p2->pt(); });
      
      for (unsigned int i2 = 0; i2< daught.size(); ++i2) {
	
	float pt2 = ((daught[i2])->pt()) * ((daught[i2])->pt());
	float delR = delta2R((*daught[i2]).rapidity(), (*daught[i2]).phi(),pfjetAK8y[npfjetAK8],pfjetAK8phi[npfjetAK8]);
	
	sumpt2 += pt2;
	sumpt += daught[i2]->pt();
	
	pfjetAK8chrad[npfjetAK8] +=  (*daught[i2]).charge() * (daught[i2])->pt() * delR;
	
	if(fabs((*daught[i2]).charge())>0 && (daught[i2])->pt()>leadjtrackpt){
	  leadjtrackpt = (daught[i2])->pt();
	}
      }
      
      daught.clear();
      
      pfjetAK8chrad[npfjetAK8] *= (sumpt>0) ? 1./sumpt : 0;
      
      pfjetAK8pTD[npfjetAK8] = (sumpt2>0 && sumpt>0) ? sqrt(sumpt2)*1./sumpt : 0;
      
      pfjetAK8sub1pt[npfjetAK8] = pfjetAK8sub1eta[npfjetAK8] = pfjetAK8sub1phi[npfjetAK8] = pfjetAK8sub1mass[npfjetAK8] = pfjetAK8sub1btag[npfjetAK8] = pfjetAK8sub1chhadfrac[npfjetAK8] = pfjetAK8sub1neuhadfrac[npfjetAK8] =pfjetAK8sub1emfrac[npfjetAK8] = pfjetAK8sub1neuemfrac[npfjetAK8] = pfjetAK8sub1phofrac[npfjetAK8] = pfjetAK8sub1mufrac[npfjetAK8] = pfjetAK8sub1hadfrac[npfjetAK8] = -100;              
      pfjetAK8sub2pt[npfjetAK8] = pfjetAK8sub2eta[npfjetAK8] = pfjetAK8sub2phi[npfjetAK8] = pfjetAK8sub2mass[npfjetAK8] = pfjetAK8sub2btag[npfjetAK8] = pfjetAK8sub2chhadfrac[npfjetAK8] = pfjetAK8sub2neuhadfrac[npfjetAK8] = pfjetAK8sub2emfrac[npfjetAK8] = pfjetAK8sub2neuemfrac[npfjetAK8] = pfjetAK8sub2phofrac[npfjetAK8] = pfjetAK8sub2mufrac[npfjetAK8] = pfjetAK8sub2hadfrac[npfjetAK8] = -100;                                                        
      pfjetAK8sdmass[npfjetAK8] = -100;                                                                      
      pfjetAK8elinsubpt[npfjetAK8] = -100;                                                                   
      pfjetAK8elinsubeta[npfjetAK8] = -100;                                                                  
      pfjetAK8elinsubphi[npfjetAK8] = -100;                                                                  
      pfjetAK8elinsubmass[npfjetAK8] = -100;                                                                 
      pfjetAK8elinsubjpt[npfjetAK8] = -100;                                                                  
      pfjetAK8elinsubjeta[npfjetAK8] = -100;                                                                 
      pfjetAK8elinsubjphi[npfjetAK8] = -100;                                                                 
      pfjetAK8elinsubjmass[npfjetAK8] = -100;                                                                
      pfjetAK8muinsubpt[npfjetAK8] = -100;
      pfjetAK8muinsubeta[npfjetAK8] = -100;
      pfjetAK8muinsubphi[npfjetAK8] = -100;
            
      pfjetAK8muinsubmass[npfjetAK8] = -100;
      pfjetAK8muinsubjpt[npfjetAK8] = -100;
      pfjetAK8muinsubjeta[npfjetAK8] = -100;
      pfjetAK8muinsubjphi[npfjetAK8] = -100;
      pfjetAK8muinsubjmass[npfjetAK8] = -100;

    
      pfjetAK8muinsubIfar[npfjetAK8] = -100;
      pfjetAK8muinsubI0[npfjetAK8] = -100;
      pfjetAK8muinsubInear[npfjetAK8] = -100;

      pfjetAK8elinsubIfar[npfjetAK8] = -100;
      pfjetAK8elinsubI0[npfjetAK8] = -100;
      pfjetAK8elinsubInear[npfjetAK8] = -100;

      if(isSoftDrop){
	
	pfjetAK8tau1[npfjetAK8] = ak8jet.userFloat(tau1);
	pfjetAK8tau2[npfjetAK8] = ak8jet.userFloat(tau2);
	pfjetAK8tau3[npfjetAK8] = ak8jet.userFloat(tau3);

	pfjetAK8sdmass[npfjetAK8] = (ak8jet.groomedMass(subjets) > 0)? ak8jet.groomedMass(subjets) : 0;
	
	if((ak8jet.subjets(subjets)).size()>1){   ////subjets = "SoftDropPuppi"
	  
	  TLorentzVector elInsubjet1, elInsubjet2, subjet1_wel, subjet2_wel;
	  TLorentzVector muInsubjet1, muInsubjet2, subjet1_wmu, subjet2_wmu;
	  
	  std::vector<TLorentzVector> elInsubjet1vec, elInsubjet2vec;
	  std::vector<TLorentzVector> muInsubjet1vec, muInsubjet2vec;
	
	  for(unsigned int isub=0; isub<((ak8jet.subjets(subjets)).size()); isub++){
	    
	    const auto ak8subjet = (ak8jet.subjets(subjets))[isub];
	    std::vector<reco::CandidatePtr> subdaught((ak8jet.subjets(subjets))[isub]->daughterPtrVector());
				
	    if (isub==0 || isub==1) {
					
	      float el_maxpt(-100);
	      int el_indx(-100);
	      float mu_maxpt(-100);
	      int mu_indx(-100);
					
	      for(unsigned int i2=0; i2 < subdaught.size(); i2++){
		if (abs((*subdaught[i2]).pdgId()) == 11){
		  if ((*subdaught[i2]).pt() > el_maxpt) {
		    el_maxpt = (*subdaught[i2]).pt();
		    el_indx = i2;
		  }
		}
		else if (abs((*subdaught[i2]).pdgId()) == 13){
		  if ((*subdaught[i2]).pt() > mu_maxpt) {
		    mu_maxpt = (*subdaught[i2]).pt();
		    mu_indx = i2;
		  }
		}
	      }//i2
					
	      if (el_indx >= 0 && isub==0) {
		elInsubjet1.SetPtEtaPhiE((*subdaught[el_indx]).pt(),(*subdaught[el_indx]).eta(),(*subdaught[el_indx]).phi(),(*subdaught[el_indx]).energy());
		subjet1_wel.SetPtEtaPhiM(ak8subjet->pt(),ak8subjet->eta(),ak8subjet->phi(),ak8subjet->mass());
		elInsubjet1vec.push_back(elInsubjet1);
	      }
	      if (el_indx >= 0 && isub==1) {
		elInsubjet2.SetPtEtaPhiE((*subdaught[el_indx]).pt(),(*subdaught[el_indx]).eta(),(*subdaught[el_indx]).phi(),(*subdaught[el_indx]).energy());
		subjet2_wel.SetPtEtaPhiM(ak8subjet->pt(),ak8subjet->eta(),ak8subjet->phi(),ak8subjet->mass());
		elInsubjet2vec.push_back(elInsubjet2);
	      }
	      if (mu_indx >= 0 && isub==0) {
		muInsubjet1.SetPtEtaPhiE((*subdaught[mu_indx]).pt(),(*subdaught[mu_indx]).eta(),(*subdaught[mu_indx]).phi(),(*subdaught[mu_indx]).energy());
		subjet1_wmu.SetPtEtaPhiM(ak8subjet->pt(),ak8subjet->eta(),ak8subjet->phi(),ak8subjet->mass());
		muInsubjet1vec.push_back(muInsubjet1);
	      }
	      if (mu_indx >= 0 && isub==1) {
		muInsubjet2.SetPtEtaPhiE((*subdaught[mu_indx]).pt(),(*subdaught[mu_indx]).eta(),(*subdaught[mu_indx]).phi(),(*subdaught[mu_indx]).energy());
		subjet2_wmu.SetPtEtaPhiM(ak8subjet->pt(),ak8subjet->eta(),ak8subjet->phi(),ak8subjet->mass());
		muInsubjet2vec.push_back(muInsubjet2);
	      }
	    }
	    
	    float emsub=0, phosub=0, musub=0, chhad=0, neuhad=0;
				
	    for(unsigned int i2=0; i2 < subdaught.size(); i2++){    
	      switch (abs((*subdaught[i2]).pdgId())){
	      case 11 :
		emsub += (*subdaught[i2]).energy();
		break;
	      case 13 :	
		musub += (*subdaught[i2]).energy();
		break;
	      case 22 :
		phosub += (*subdaught[i2]).energy();
		break;
	      case 211 :
		chhad += (*subdaught[i2]).energy();
		break;
	      case 130 :
		neuhad += (*subdaught[i2]).energy();
		break;
	      }
	    }
	    
	    if(isub==0){
	      pfjetAK8sub1pt[npfjetAK8] = ak8subjet->pt();
	      pfjetAK8sub1eta[npfjetAK8] = ak8subjet->eta();
	      pfjetAK8sub1phi[npfjetAK8] = ak8subjet->phi();
	      pfjetAK8sub1mass[npfjetAK8] = ak8subjet->mass();	 
	      pfjetAK8sub1btag[npfjetAK8] = ak8subjet->bDiscriminator("pfDeepCSVJetTags:probb")+ak8subjet->bDiscriminator("pfDeepCSVJetTags:probbb");
	      pfjetAK8sub1emfrac[npfjetAK8] = emsub*1./ak8subjet->correctedP4("Uncorrected").energy();
	      pfjetAK8sub1mufrac[npfjetAK8] = musub*1./ak8subjet->correctedP4("Uncorrected").energy();
	      pfjetAK8sub1phofrac[npfjetAK8] = phosub*1./ak8subjet->correctedP4("Uncorrected").energy();
	      pfjetAK8sub1chhadfrac[npfjetAK8] = chhad*1./ak8subjet->correctedP4("Uncorrected").energy();
	      pfjetAK8sub1neuhadfrac[npfjetAK8] = neuhad*1./ak8subjet->correctedP4("Uncorrected").energy();
	      pfjetAK8sub1hadfrac[npfjetAK8] = (chhad+neuhad)*1./ak8subjet->correctedP4("Uncorrected").energy();
	    }
	    else if(isub==1){
	      pfjetAK8sub2pt[npfjetAK8] = ak8subjet->pt();
	      pfjetAK8sub2eta[npfjetAK8] = ak8subjet->eta();
	      pfjetAK8sub2phi[npfjetAK8] = ak8subjet->phi();
	      pfjetAK8sub2mass[npfjetAK8] = ak8subjet->mass();	 
	      pfjetAK8sub2btag[npfjetAK8] = ak8subjet->bDiscriminator("pfDeepCSVJetTags:probb")+ak8subjet->bDiscriminator("pfDeepCSVJetTags:probbb");
	      pfjetAK8sub2emfrac[npfjetAK8] = emsub*1./ak8subjet->correctedP4("Uncorrected").energy();
	      pfjetAK8sub2mufrac[npfjetAK8] = musub*1./ak8subjet->correctedP4("Uncorrected").energy();
	      pfjetAK8sub2phofrac[npfjetAK8] = phosub*1./ak8subjet->correctedP4("Uncorrected").energy();
	      pfjetAK8sub2chhadfrac[npfjetAK8] = chhad*1./ak8subjet->correctedP4("Uncorrected").energy();
	      pfjetAK8sub2neuhadfrac[npfjetAK8] = neuhad*1./ak8subjet->correctedP4("Uncorrected").energy();
	      pfjetAK8sub2hadfrac[npfjetAK8] = (chhad+neuhad)*1./ak8subjet->correctedP4("Uncorrected").energy();
	    }	  
	  }
	  
	  pfjetAK8subhaddiff[npfjetAK8] = diff_func(pfjetAK8sub1hadfrac[npfjetAK8],pfjetAK8sub2hadfrac[npfjetAK8]);
	  pfjetAK8subemdiff[npfjetAK8] = diff_func(pfjetAK8sub1emfrac[npfjetAK8],pfjetAK8sub2emfrac[npfjetAK8]);
	  pfjetAK8subptdiff[npfjetAK8] = diff_func(pfjetAK8sub1pt[npfjetAK8],pfjetAK8sub2pt[npfjetAK8]);
	  
	  if (pfjetAK8sub1hadfrac[npfjetAK8] >= 0 && pfjetAK8sub2hadfrac[npfjetAK8] >= 0) {
	    if (pfjetAK8sub1hadfrac[npfjetAK8] < pfjetAK8sub2hadfrac[npfjetAK8]) {
	      if (elInsubjet1vec.size() > 0) {
						
		pfjetAK8elinsubpt[npfjetAK8] =  elInsubjet1.Pt();
		pfjetAK8elinsubeta[npfjetAK8] =  elInsubjet1.Eta();
		pfjetAK8elinsubphi[npfjetAK8] =  elInsubjet1.Phi();
		pfjetAK8elinsubmass[npfjetAK8] =  elInsubjet1.M();
						
		pfjetAK8elinsubjpt[npfjetAK8] =  subjet1_wel.Pt();
		pfjetAK8elinsubjeta[npfjetAK8] = subjet1_wel.Eta();
		pfjetAK8elinsubjphi[npfjetAK8] = subjet1_wel.Phi();
		pfjetAK8elinsubjmass[npfjetAK8] =  subjet1_wel.M();
	      }
	      if (muInsubjet1vec.size() > 0) {
						
		pfjetAK8muinsubpt[npfjetAK8] =  muInsubjet1.Pt();
		pfjetAK8muinsubeta[npfjetAK8] =  muInsubjet1.Eta();
		pfjetAK8muinsubphi[npfjetAK8] =  muInsubjet1.Phi();
		pfjetAK8muinsubmass[npfjetAK8] =  muInsubjet1.M();
						
		pfjetAK8muinsubjpt[npfjetAK8] =  subjet1_wmu.Pt();
		pfjetAK8muinsubjeta[npfjetAK8] = subjet1_wmu.Eta();
		pfjetAK8muinsubjphi[npfjetAK8] = subjet1_wmu.Phi();
		pfjetAK8muinsubjmass[npfjetAK8] =  subjet1_wmu.M();
	      }
	    }
	    else if (pfjetAK8sub1hadfrac[npfjetAK8] > pfjetAK8sub2hadfrac[npfjetAK8]){
	      if (elInsubjet2vec.size() > 0) {
						
		pfjetAK8elinsubpt[npfjetAK8] =  elInsubjet2.Pt();
		pfjetAK8elinsubeta[npfjetAK8] =  elInsubjet2.Eta();
		pfjetAK8elinsubphi[npfjetAK8] =  elInsubjet2.Phi();
		pfjetAK8elinsubmass[npfjetAK8] =  elInsubjet2.M();
		
		pfjetAK8elinsubjpt[npfjetAK8] =  subjet2_wel.Pt();
		pfjetAK8elinsubjeta[npfjetAK8] = subjet2_wel.Eta();
		pfjetAK8elinsubjphi[npfjetAK8] = subjet2_wel.Phi();
		pfjetAK8elinsubjmass[npfjetAK8] =  subjet2_wel.M();
	      }
	      if (muInsubjet2vec.size() > 0) {
	
		pfjetAK8muinsubpt[npfjetAK8] =  muInsubjet2.Pt();
		pfjetAK8muinsubeta[npfjetAK8] =  muInsubjet2.Eta();
		pfjetAK8muinsubphi[npfjetAK8] =  muInsubjet2.Phi();
		pfjetAK8muinsubmass[npfjetAK8] =  muInsubjet2.M();
		
		pfjetAK8muinsubjpt[npfjetAK8] =  subjet2_wmu.Pt();
		pfjetAK8muinsubjeta[npfjetAK8] = subjet2_wmu.Eta();
		pfjetAK8muinsubjphi[npfjetAK8] = subjet2_wmu.Phi();
		pfjetAK8muinsubjmass[npfjetAK8] =  subjet2_wmu.M();
	      }
	    }
	    
	  }
			
			
	  if (pfjetAK8elinsubpt[npfjetAK8] >-99 && pfjetAK8elinsubeta[npfjetAK8] >-99) {
	    float elIfar(0.), elInear(0.), elI0(0.);
	    for (unsigned int i = 0, n = pfs->size(); i < n; ++i) {
	      const pat::PackedCandidate &pf = (*pfs)[i];
	      double dR = delta2R(pfjetAK8elinsubeta[npfjetAK8],pfjetAK8elinsubphi[npfjetAK8],pf.eta(),pf.phi());
	      if ( dR < 0.4 && dR  > 0.00001) {
		elIfar = elIfar + pf.pt()*(pow(dR,2.0));
		elInear = elInear + pf.pt()*(pow(dR,-2.0));
		elI0 = elI0 + pf.pt();
	      }
	    }
	    pfjetAK8elinsubIfar[npfjetAK8] = elIfar;
	    pfjetAK8elinsubInear[npfjetAK8] = elInear;
	    pfjetAK8elinsubI0[npfjetAK8] = elI0;
	  }
			
	  if (pfjetAK8muinsubpt[npfjetAK8] >-99 && pfjetAK8muinsubeta[npfjetAK8] > -99) {
	    float Ifar(0.), Inear(0.), I0(0.);
	    for (unsigned int i = 0, n = pfs->size(); i < n; ++i) {
	      const pat::PackedCandidate &pf = (*pfs)[i];
	      float dR = delta2R(pfjetAK8muinsubeta[npfjetAK8],pfjetAK8muinsubphi[npfjetAK8],pf.eta(),pf.phi());
	      if (dR < 0.4 && dR > 0.00001) {
		Ifar = Ifar + pf.pt()*(pow(dR,2.0));
		Inear = Inear + pf.pt()*(pow(dR,-2.0));
		I0 = I0 + pf.pt();
	      }
	    }
	    
	    pfjetAK8muinsubIfar[npfjetAK8] = Ifar;
	    pfjetAK8muinsubInear[npfjetAK8] = Inear;
	    pfjetAK8muinsubI0[npfjetAK8] = I0;
			
	  }
	
	}
	 
      }//isSoftDrop
      
      npfjetAK8++;	
      if(npfjetAK8 >= njetmxAK8) { break;}
      
    }
  }

  if(npfjetAK8>0){ // skimming condition

    if(isMC){

      // Flavor tagging of GEN jets using ghost-matching //                                                             

	edm::Handle<reco::JetFlavourInfoMatchingCollection> jetFlavourInfos;
      iEvent.getByToken(jetFlavourInfosToken_, jetFlavourInfos);

      iEvent.getByToken(tok_genjetAK4s_, genjetAK4s);
 
      std::vector<int> partonFlavour_AK4;
      std::vector<uint8_t> hadronFlavour_AK4;
      
      for (const reco::GenJet & jet : *genjetAK4s) {
	bool matched = false;
	for (const reco::JetFlavourInfoMatching & jetFlavourInfoMatching : *jetFlavourInfos) {
	  if (deltaR(jet.p4(), jetFlavourInfoMatching.first->p4()) < 0.1) {
	    partonFlavour_AK4.push_back(jetFlavourInfoMatching.second.getPartonFlavour());
	    hadronFlavour_AK4.push_back(jetFlavourInfoMatching.second.getHadronFlavour());
	    matched = true;
	    break;
	  }
	}
		
	if (!matched) {
	  partonFlavour_AK4.push_back(-100);
	  hadronFlavour_AK4.push_back(-100);
	}
		
      }
      
      std::vector<int> partonFlavour_AK8;
      std::vector<uint8_t> hadronFlavour_AK8;

      for (const reco::GenJet & jet : *genjetAK8s) {
	bool matched = false;
	for (const reco::JetFlavourInfoMatching & jetFlavourInfoMatching : *jetFlavourInfos) {
	  if (deltaR(jet.p4(), jetFlavourInfoMatching.first->p4()) < 0.1) {
	    partonFlavour_AK8.push_back(jetFlavourInfoMatching.second.getPartonFlavour());
	    hadronFlavour_AK8.push_back(jetFlavourInfoMatching.second.getHadronFlavour());
	    matched = true;
	    break;
	  }
	}
	if (!matched) {
	  partonFlavour_AK8.push_back(-100);
	  hadronFlavour_AK8.push_back(-100);
	}
      }

      
      ngenjetAK8 = 0;
      
      for(unsigned gjet = 0; gjet<genjetAK8s->size(); gjet++)	{
	
	TLorentzVector genjetAK84v((*genjetAK8s)[gjet].px(),(*genjetAK8s)[gjet].py(),(*genjetAK8s)[gjet].pz(), (*genjetAK8s)[gjet].energy());
	if(genjetAK84v.Pt()<AK8GenPtCut) continue;
	if(abs(genjetAK84v.Eta())>maxgenEta) continue;
	
	genjetAK8pt[ngenjetAK8] = genjetAK84v.Pt();
	genjetAK8eta[ngenjetAK8] = genjetAK84v.Eta();
	genjetAK8phi[ngenjetAK8] = genjetAK84v.Phi();
	genjetAK8mass[ngenjetAK8] = (*genjetAK8s)[gjet].mass();
	genjetAK8hadronflav[ngenjetAK8] = (int)hadronFlavour_AK8[gjet];
	genjetAK8partonflav[ngenjetAK8] = partonFlavour_AK8[gjet];
	
	std::vector<reco::CandidatePtr> daught((*genjetAK8s)[gjet].daughterPtrVector());
	
	vector <fastjet::PseudoJet> fjInputs;
	fjInputs.resize(0);
	
	for (unsigned int i2 = 0; i2< daught.size(); ++i2) {
	  
	  PseudoJet psjet = PseudoJet( (*daught[i2]).px(),(*daught[i2]).py(),(*daught[i2]).pz(),(*daught[i2]).energy() );
	  psjet.set_user_index(i2);
	  fjInputs.push_back(psjet);
	  
	} //i2
	
	vector <fastjet::PseudoJet> sortedJets;
	fastjet::ClusterSequence clustSeq(fjInputs, pfjetAK8Def);
	fjInputs.clear();
	sortedJets    = sorted_by_pt(clustSeq.inclusive_jets());
	
	if(sortedJets.size()>0){
	  genjetAK8sdmass[ngenjetAK8] = (sd(sortedJets[0])).m();
	}
	
	if (++ngenjetAK8>=njetmx) break;
	
      }
      
      
      ngenjetAK4 = 0;
	
      for(unsigned gjet = 0; gjet<genjetAK4s->size(); gjet++)	{
	
	TLorentzVector genjetAK44v((*genjetAK4s)[gjet].px(),(*genjetAK4s)[gjet].py(),(*genjetAK4s)[gjet].pz(), (*genjetAK4s)[gjet].energy());
	if(genjetAK44v.Pt()<minGenPt) continue;
	if(abs(genjetAK44v.Eta())>maxgenEta) continue;
	
	genjetAK4pt[ngenjetAK4] = genjetAK44v.Pt();
	genjetAK4eta[ngenjetAK4] = genjetAK44v.Eta();
	genjetAK4phi[ngenjetAK4] = genjetAK44v.Phi();
	genjetAK4mass[ngenjetAK4] = (*genjetAK4s)[gjet].mass();
	genjetAK4hadronflav[ngenjetAK4] = (int)hadronFlavour_AK4[gjet];
	genjetAK4partonflav[ngenjetAK4] = partonFlavour_AK4[gjet];

	if (++ngenjetAK4>=njetmx) break;
      }
      
      ngenparticles = 0;
      
      iEvent.getByToken(tok_genparticles_,genparticles);
      
      if(genparticles.isValid()){
		  
	for(unsigned ig=0; ig<(genparticles->size()); ig++){
	  
	  if(!(((*genparticles)[ig].status()==1)||(abs((*genparticles)[ig].status())==22)||((*genparticles)[ig].status()==23)|((*genparticles)[ig].status()==2))) continue; 
	  
	  //if(!((*genparticles)[ig].isHardProcess() || ((*genparticles)[ig].mother() &&  abs((*genparticles)[ig].mother()->pdgId()) == 15 )) continue;
	  if(!((*genparticles)[ig].isHardProcess()||(*genparticles)[ig].fromHardProcessBeforeFSR()||(*genparticles)[ig].isLastCopyBeforeFSR()||(*genparticles)[ig].isDirectPromptTauDecayProductFinalState())) continue;
	  
	  if(!((abs((*genparticles)[ig].pdgId())>=1 && abs((*genparticles)[ig].pdgId())<=6) || (abs((*genparticles)[ig].pdgId())>=11 && abs((*genparticles)[ig].pdgId())<=16) || (abs((*genparticles)[ig].pdgId())>=22 && abs((*genparticles)[ig].pdgId())<=24))) continue;
	  
	  genpartstatus[ngenparticles] = (*genparticles)[ig].status();
	  genpartpdg[ngenparticles] = (*genparticles)[ig].pdgId();

	  int mompdg, momstatus, grmompdg;
	  mompdg = momstatus = grmompdg = -100;
	  
	  if((*genparticles)[ig].numberOfMothers()>0){
	    // mother pdg id //
	    const Candidate * mom = (*genparticles)[ig].mother();
	    while(mom->pdgId() == (*genparticles)[ig].pdgId())
	      {
		mom = mom->mother();
	      }
	    if(!(*genparticles)[ig].isPromptFinalState() && !(*genparticles)[ig].isDirectPromptTauDecayProductFinalState()){
	      while(mom->status()==2){
		mom = mom->mother();	
	      }
	    }
	    
	    mompdg = mom->pdgId();
	    momstatus = mom->status();
	    
	    // grand-mother pdg id //
	    
	    if(mom->numberOfMothers()>0){
	      
	      const Candidate * grmom = mom->mother();
	      
	      while(grmom->pdgId() == mompdg)
		{
		  if(grmom->numberOfMothers()>0){
		    grmom = grmom->mother();
		  }
		  else{ break; }
		}
	      
	      grmompdg  = grmom->pdgId();	
	    } 
	    
	  }
	  
	  genpartmompdg[ngenparticles] = mompdg;
	  genpartmomstatus[ngenparticles] = momstatus;
	  genpartgrmompdg[ngenparticles] = grmompdg; 
	  
	  genpartdaugno[ngenparticles] = (*genparticles)[ig].numberOfDaughters();
	  genpartfromhard[ngenparticles] = (*genparticles)[ig].isHardProcess();
	  genpartfromhardbFSR[ngenparticles] = (*genparticles)[ig].fromHardProcessBeforeFSR();
	  genpartisLastCopyBeforeFSR[ngenparticles] = (*genparticles)[ig].isLastCopyBeforeFSR();
	  genpartisPromptFinalState[ngenparticles] = (*genparticles)[ig].isPromptFinalState();
	  genpartpt[ngenparticles] = (*genparticles)[ig].pt();
	  genparteta[ngenparticles] = (*genparticles)[ig].eta();
	  genpartphi[ngenparticles] = (*genparticles)[ig].phi();
	  genpartm[ngenparticles] = (*genparticles)[ig].mass();
	  /*
	    if(mom->numberOfMothers()>0){
	    const Candidate * grmom  = mom->mother();
	    genpartgrmompdg[ngenparticles]  = grmom->pdgId();
	    }
	    else{
	    genpartgrmompdg[ngenparticles]  = -10000000;
	    }
	  */
	  
	  ngenparticles++;
	  if(ngenparticles>=npartmx) break;
		
	}
      }
      
    }//isMC
 
    nmuons = 0;                                                                                                                                        
    std::vector<pat::Muon> tlvmu;
    edm::Handle<edm::View<pat::Muon>> muons;                                                                                                          
    iEvent.getByToken(tok_muons_, muons);                                                                                                             
    
    if(muons.isValid() && muons->size()>0) {                                                                                                           
    
      edm::View<pat::Muon>::const_iterator muon1;                                                                                                      
      
      for( muon1 = muons->begin(); muon1 < muons->end(); muon1++ ) {    
		                                                                                 
	if ((muon1->isTrackerMuon() || muon1->isGlobalMuon()) && (muon1->isPFMuon())) {                                                                
		
	  if (muon1->pt()<10.0) continue;                   
	  /*                                                                                           
	  //Defining MiniIsolation old version for muon here//      
	  *** deprecated ***    (should be removed)                                                                              
	  float chiso = 0, nhiso = 0, phiso = 0, puiso = 0;                                                                                            
	  float deadcone_ch = 0.0001;                                                                                                                  
	  float deadcone_pu = 0.01;                                                                                                                    
	  float deadcone_ph = 0.01;                                                                                                                    
	  float deadcone_nh = 0.01;                                                                                                                    
	  float ptthresh(0.5);                                                                                                                         
	  float dZ_cut(0.0);                                                                                                                           
	  float drcut = std::max(float(0.05),std::min(float(0.2),float(10.0/muon1->pt())));                                                            
		
	  for (const pat::PackedCandidate &pfc : *pfs) {                                                                                               
	  float dr = delta2R(muon1->eta(),muon1->phi(),pfc.eta(),pfc.phi());                                                                         
	  if (dr > drcut) continue;                                                                                                                  
	  int id = std::abs(pfc.pdgId());                                                                                                                      
	  if (id == 211 || id == 321 || id == 2212) {                                                                  
	  bool fromPV = (pfc.fromPV() > 1 || fabs(pfc.dz()) < dZ_cut);                                                                             
	  if (fromPV && dr > deadcone_ch) {                                                                                                        
	  // if charged hadron and from primary vertex, add to charged hadron isolation                                                          
	  chiso += pfc.pt();                                                                                                                     
	  } else if (!fromPV && pfc.pt() > ptthresh && dr > deadcone_pu) {                                                                         
	  // if charged hadron and NOT from primary vertex, add to pileup isolation                                                              
	  puiso += pfc.pt();                                                                                                                     
	  }                                                                                                                                        
	  }                                                                                                                                          
	  // if neutral hadron, add to neutral hadron isolation                                                                                      
	  if (id == 130 && pfc.pt() > ptthresh && dr > deadcone_nh)                                                                        
	  nhiso += pfc.pt();                                                                                                                       
	  // if photon, add to photon isolation                                                                                                      
	  if (id == 22 && pfc.pt() > ptthresh && dr > deadcone_ph)                                                                         
	  phiso += pfc.pt();                                                                                                                       
	  }
			                                                                                                                                            
	  double iso(0.), iso_nch(0.);                                                                                                                 
	  //if (charged_only)                                                                                                                          
	  iso = chiso;
	  iso_nch = phiso + nhiso;                                                                                                                     
	  iso_nch -= 0.5*puiso;                                                                                                                        
	  if (iso_nch>0) iso_nch += chiso;                                                                                                             
	  else iso_nch = chiso;                                                                                                                        
	  iso = iso/muon1->pt();                                                                                                                       
	  iso_nch = iso_nch/muon1->pt();                                                                                                               
	  */        
                                                                                                                                             
	  //Defining MiniIsolation recent version for muon here//    
			                                                                                  
							     pat::PFIsolation muiso = muon1->miniPFIsolation();                                                                                           
	                                                                                                        
	  muonchiso[nmuons] = muiso.chargedHadronIso();                                                                                                                     
	  muonnhiso[nmuons] = muiso.neutralHadronIso();                                                                                                                     
	  muonphiso[nmuons] = muiso.photonIso();                                                                                                                     
			
	  float coneta = muon1->eta();                                                                                                                 
	  float ea = ea_miniiso_->getEffectiveArea(fabs(coneta));                                                                                      
	  float R = 10.0 / std::min(std::max(muon1->pt(), 50.0), 200.0);                                                                               
	  ea *= std::pow(R / 0.3, 2);                                                                                                                  
	  //float scale = relative_ ? 1.0 / muon1->pt() : 1;                                                                                           
	  muonminisoall[nmuons] = (muonchiso[nmuons] + std::max(0., muonnhiso[nmuons] + muonphiso[nmuons] - (*Rho_PF) * ea));                                                                    
	  //std::cout << " miniIsoChg " << scale * chg << " " << " miniIsoAll " << scale * (chg + std::max(0.0, neu + pho - (*Rho_PF) * ea)) << " " << std::endl;                                                                                                       
			
	  muonisPF[nmuons] = muon1->isPFMuon();                                                                                                        
	  muonisGL[nmuons] = muon1->isGlobalMuon();                                                                                                    
	  muonisTRK[nmuons] = muon1->isTrackerMuon();                                                                                                  
	  muonisLoose[nmuons] = (muon::isLooseMuon(*muon1));                                                                                           
	  muonisMed[nmuons] = (muon::isMediumMuon(*muon1));                                                                                            
	  muonisMedPr[nmuons] = false;                                                                          
	  if(muon::isMediumMuon(*muon1)) {                                                                                                             
	    if ((std::abs(muon1->muonBestTrack()->dz(vertex.position())) < 0.1) && (std::abs(muon1->muonBestTrack()->dxy(vertex.position())) < 0.02)){                                                                                                                  
	      muonisMedPr[nmuons] = true;                                                                                                              
	    }                                                                                                                                          
	  }                                                                                                                                            
	  muonisGoodGL[nmuons] = (muon1->isGlobalMuon() && muon1->globalTrack()->normalizedChi2() < 3 && muon1->combinedQuality().chi2LocalPosition < 12 && muon1->combinedQuality().trkKink < 20 && (muon::segmentCompatibility(*muon1)) > 0.303);                     
	  muonisTight[nmuons] = (muon::isTightMuon(*muon1,vertex));                                                                                    
	  muonisHighPt[nmuons] = (muon::isHighPtMuon(*muon1,vertex));                                                                                  
	  muonisHighPttrk[nmuons] = (muon::isTrackerHighPtMuon(*muon1,vertex));                                                                        
	  muonecal[nmuons] = (muon1->calEnergy()).em;                                                                                                  
	  muonhcal[nmuons] = (muon1->calEnergy()).had;                                                                                  
	  muonpt[nmuons] = muon1->pt();                                                                         	
	  TrackRef trktrk = muon1->innerTrack();                                                                                                       
	  muonp[nmuons] = trktrk->p()*muon1->charge();                                                                                                                 
	  muoneta[nmuons] = muon1->eta();                                                                                                              
	  muonphi[nmuons] = muon1->phi();                                                                                                              
	  muonposmatch[nmuons] = muon1->combinedQuality().chi2LocalPosition;                                                                           
	  muontrkink[nmuons] = muon1->combinedQuality().trkKink;                                                                                       
	  muonsegcom[nmuons] = muon::segmentCompatibility(*muon1);                                                                                     
	  muontrkvtx[nmuons] = muon1->muonBestTrack()->dxy(vertex.position());                                                                         
	  muondz[nmuons] = muon1->muonBestTrack()->dz(vertex.position());                                                                              
	  float dzmumin = 1000;                                                                                                                        
	  float dxymumin = 1000;                                                                                                                       
	  if(svin.isValid()){                                                                                                                          
	    for(unsigned int isv=0; isv<(svin->size()); isv++){                                                                                        
	      const auto &sv = (*svin)[isv];                                                                                                           
	      reco::TrackBase::Point svpoint(sv.vx(),sv.vy(),sv.vz());
	      float dztmp = fabs(muon1->muonBestTrack()->dz(svpoint));
	      if(dztmp < dzmumin){
		dzmumin = dztmp;                                                                                   
		dxymumin = muon1->muonBestTrack()->dxy(svpoint);                                                                                       
	      }                                                                                                                                        
	    }                                                                                                                                          
	  }                                                                                                                                            
	  mudxy_sv[nmuons] = dxymumin;                                                                                                                 
	  muonpter[nmuons] = trktrk->ptError();    
			                                                                                                    
	  TrackRef trkglb =muon1->globalTrack();                                                                                                       
	  if ((!muon1->isGlobalMuon())) {                                                                                                              
	    if (muon1->isTrackerMuon()) {                                                                                                              
	      trkglb =muon1->innerTrack();                                                                                                             
	    } else {                                                                                                                                   
	      trkglb =muon1->outerTrack();                                                                                                             
	    }                                                                                                                                          
	  }                                                                                                                                            
			
	  muonchi[nmuons] = trkglb->normalizedChi2();                                                                                                  
	  muonndf[nmuons] = (int)trkglb->ndof();                                                                                                       
	  muonhit[nmuons] = trkglb->hitPattern().numberOfValidMuonHits();                                                                              
	  muonmst[nmuons] = muon1->numberOfMatchedStations();                                                                                          
	  muonpixhit[nmuons] = trktrk->hitPattern().numberOfValidPixelHits();                                                                          
	  muontrklay[nmuons] = trktrk->hitPattern().trackerLayersWithMeasurement();                                                                    
	  muonvalfrac[nmuons] = trktrk->validFraction();                                                        
			
	  muonpfiso[nmuons] = (muon1->pfIsolationR04().sumChargedHadronPt + max(0., muon1->pfIsolationR04().sumNeutralHadronEt + muon1->pfIsolationR04().sumPhotonEt - 0.5*muon1->pfIsolationR04().sumPUPt))/muon1->pt();                                               

	  TLorentzVector tlmu;
	  bool mu_id = Muon_TightID(muonisGL[nmuons],muonisPF[nmuons],
				    muonchi[nmuons],muonhit[nmuons],muonmst[nmuons],
				    muontrkvtx[nmuons],muondz[nmuons],muonpixhit[nmuons],muontrklay[nmuons]);

	  // Application of Rochester correction //
	  
	  float rcSF, rcSF_error;
	  
	  if(!isMC){
	    // Data
	    rcSF = roch_cor.kScaleDT(muon1->charge(), muonpt[nmuons], muoneta[nmuons], muonphi[nmuons]); 
	    rcSF_error = roch_cor.kScaleDTerror(muon1->charge(), muonpt[nmuons], muoneta[nmuons], muonphi[nmuons]); 
	  }
	  else{
	    // MC
	    bool gen_match = false;
	    float match_genpt = -100;
	    float dR_cut = 0.1;
	    for(int ipart=0; ipart<ngenparticles; ipart++)
	      {
		if((genpartstatus[ipart]==1) && (genpartpdg[ipart]==(-1*muon1->charge()*13)) && (delta2R(genparteta[ipart],genpartphi[ipart],muoneta[nmuons], muonphi[nmuons])<dR_cut))
		  {
		    dR_cut = delta2R(genparteta[ipart],genpartphi[ipart],muoneta[nmuons], muonphi[nmuons]);
		    gen_match = true;
		    match_genpt = genpartpt[ipart];
		  }
	      }
	    if(gen_match){
	      // when matched gen muon is available
	      rcSF = roch_cor.kSpreadMC(muon1->charge(), muonpt[nmuons], muoneta[nmuons], muonphi[nmuons], match_genpt); 
	      rcSF_error = roch_cor.kSpreadMCerror(muon1->charge(), muonpt[nmuons], muoneta[nmuons], muonphi[nmuons], match_genpt);
	    } 
	    else{
	      // when matched gen muon is not available
	      rcSF = roch_cor.kSmearMC(muon1->charge(), muonpt[nmuons], muoneta[nmuons], muonphi[nmuons], muontrklay[nmuons], gRandom->Rndm()); 
	      rcSF_error = roch_cor.kSmearMCerror(muon1->charge(), muonpt[nmuons], muoneta[nmuons], muonphi[nmuons], muontrklay[nmuons], gRandom->Rndm());
	    }
	  }
	  
	  Muon_corrected_pt[nmuons] = muonpt[nmuons]*rcSF;
	  Muon_correctedUp_pt[nmuons] = muonpt[nmuons]*max(rcSF+rcSF_error,float(0.));
	  Muon_correctedDown_pt[nmuons] = muonpt[nmuons]*max(rcSF-rcSF_error,float(0.));
			
	  // End of Rochester correction //

	  /*	    
		    if (mu_id == true && fabs(muoneta[nmuons])<2.5) {
		    tlmu.SetPtEtaPhiE(muonpt[nmuons],muoneta[nmuons],muonphi[nmuons],muon1->energy());
		    tlvmu.push_back(tlmu);
		    }
	  */ 
	  //Changed by Suman
	  if (fabs(muoneta[nmuons])<2.5 && Muon_corrected_pt[nmuons] > 30) {
	    tlvmu.push_back(*muon1);
	  }


			
	  if (++nmuons>=njetmx) break;                                                                                                                 
	}                                                                                                                                              
      }                                                                                                                                               
    }
    

    nelecs = 0;             
    std::vector<pat::Electron> tlvel;
    int iE1 = 0;                              
                                                                                                             
    for(const auto& electron1 : iEvent.get(tok_electrons_) ) {     
		                                                                                    
      GsfTrackRef gsftrk1 = electron1.gsfTrack();                                                                                                      
      if (gsftrk1.isNull()) continue;                                                                                                                  
      TrackRef ctftrk = electron1.closestCtfTrackRef();                                                                                                
      //HepLorentzVector tmpelectron1(electron1.px(),electron1.py(),electron1.pz(), sqrt(electron1.p()*electron1.p()+el_mass*el_mass));                
      iE1++;                                                                                                                                           
      //if (tmpelectron1.perp()<10.0) continue;                                                                                                        
      if (electron1.pt()<10.0) continue;                                                                                                               
      if (gsftrk1->ndof() <9) continue;
      
      elmvaid[nelecs] = electron1.electronID(melectronID_isowp90);                                
      elmvaid_noIso[nelecs] = electron1.electronID(melectronID_noisowp90);           
      elmvaid_Fallv2WP80[nelecs] = electron1.electronID(melectronID_isowp80);                         
      elmvaid_Fallv2WP80_noIso[nelecs] = electron1.electronID(melectronID_noisowp80);  
      elmvaid_wpLoose[nelecs] = electron1.electronID(melectronID_isowploose);                                
      elmvaid_wpLoose_noIso[nelecs] = electron1.electronID(melectronID_noisowploose);
	
      elcutid_veto[nelecs] = electron1.electronID(melectronID_veto);
      elcutid_loose[nelecs] = electron1.electronID(melectronID_loose);
      elcutid_med[nelecs] = electron1.electronID(melectronID_med);
      elcutid_tight[nelecs] = electron1.electronID(melectronID_tight);
      
      elpt[nelecs] = electron1.pt();                                                                                                                   
      eleta[nelecs] = electron1.eta();                                                                                                                 
      elphi[nelecs] = electron1.phi();                                                                                                                 
      ele[nelecs] = electron1.ecalEnergy();                                                                                                            
      elp[nelecs] = electron1.trackMomentumAtVtx().R()*electron1.charge();    
      
      eldxytrk[nelecs] = gsftrk1->dxy(vertex.position());                                                                                              
      eldztrk[nelecs] = gsftrk1->dz(vertex.position());                                                                                                   
                                                                                                                                                                                                   
      elsigmaieta[nelecs] = electron1.full5x5_sigmaIetaIeta();                                                                                         
      elsigmaiphi[nelecs] = electron1.full5x5_sigmaIphiIphi();                                                                                         
      elr9full[nelecs] = electron1.full5x5_r9();                                                                                                       
      elhcaloverecal[nelecs] = electron1.full5x5_hcalOverEcal();  
      
      elsupcl_eta[nelecs] = electron1.superCluster()->eta();                                                                                           
      elsupcl_phi[nelecs] = electron1.superCluster()->phi();       
      elsupcl_rawE[nelecs] = electron1.superCluster()->rawEnergy();
      elsupcl_e[nelecs] = electron1.superCluster()->energy(); 
      elsupcl_etaw[nelecs] = electron1.superCluster()->etaWidth();                                                                                     
      elsupcl_phiw[nelecs] = electron1.superCluster()->phiWidth();
      electron1.superCluster()->energy(); 
                                                                                           
      elcloctftrkn[nelecs] = electron1.closestCtfTrackNLayers();                                                                                       
      elcloctftrkchi2[nelecs] = electron1.closestCtfTrackNormChi2();                                                                                   
      ele1x5bye5x5[nelecs] = 1.-electron1.full5x5_e1x5()/electron1.full5x5_e5x5();                                                                     
      elnormchi2[nelecs] =  electron1.gsfTrack()->normalizedChi2();                                                                                    
      elhitsmiss[nelecs] =  electron1.gsfTrack()->hitPattern().numberOfLostHits(reco::HitPattern::MISSING_INNER_HITS);                                 
      eltrkmeasure[nelecs] = electron1.gsfTrack()->hitPattern().trackerLayersWithMeasurement();                                                        
      elconvtxprob[nelecs] = electron1.convVtxFitProb();                                                                                               
      elecloverpout[nelecs] = electron1.eEleClusterOverPout();                                                                                         
      elecaletrkmomentum[nelecs] = 1.0/(electron1.ecalEnergy())-1.0/(electron1.trackMomentumAtVtx().R());                                              
      eldeltaetacltrkcalo[nelecs] = electron1.deltaEtaSeedClusterTrackAtCalo();                                                                        
      elsupcl_preshvsrawe[nelecs] = electron1.superCluster()->preshowerEnergy()/electron1.superCluster()->rawEnergy();                                 
      elpfisolsumphet[nelecs] = electron1.pfIsolationVariables().sumPhotonEt;                                                                          
      elpfisolsumchhadpt[nelecs] = electron1.pfIsolationVariables().sumChargedHadronPt;                                                                
      elpfsiolsumneuhadet[nelecs] = electron1.pfIsolationVariables().sumNeutralHadronEt;                                                               
      eleoverp[nelecs] = electron1.eSuperClusterOverP();                                                                                               
      elhovere[nelecs] = electron1.hadronicOverEm();                                                                                                   
      elietaieta[nelecs] = electron1.sigmaIetaIeta();                                                                                                  
      eletain[nelecs] = electron1.deltaEtaSuperClusterTrackAtVtx();                                                                                    
      elphiin[nelecs] = electron1.deltaPhiSuperClusterTrackAtVtx();                                                                                    
      elfbrem[nelecs] = electron1.fbrem();     
                                                                                                              
      const reco::GsfElectron::PflowIsolationVariables& pfIso = electron1.pfIsolationVariables();                                                      
      elpfiso[nelecs] = pfIso.sumChargedHadronPt + max(0., pfIso.sumNeutralHadronEt + pfIso.sumPhotonEt - 0.5*pfIso.sumPUPt);                          
                                                                                        
      float dzmin = 1000;                                                                                                                              
      float dxymin = 1000;
      if(svin.isValid()){                                                                                                                              
	for(unsigned int isv=0; isv<(svin->size()); isv++){                                                                                            
	  const auto &sv = (*svin)[isv];                                                                                                               
	  reco::TrackBase::Point svpoint(sv.vx(),sv.vy(),sv.vz());
	  float dztmp =fabs(gsftrk1->dz(svpoint));
	  if(dztmp < dzmin){                                                                                                      
	    dzmin = dztmp;                                                                                                        
	    dxymin = gsftrk1->dxy(svpoint);                                                                                                            
	  }                                                                                                                                            
	}                                                                                                                                              
      }                                                                                                                                                
      eldxy_sv[nelecs] = dxymin;    
                                                                                                                         
      elchi[nelecs] = gsftrk1->chi2();                                                                                                                 
      elndf[nelecs] = (int)gsftrk1->ndof();
      elmisshits[nelecs] = (int)gsftrk1->hitPattern().numberOfLostHits(reco::HitPattern::MISSING_INNER_HITS);

      // scaling & smearing factors //
      Electron_eccalTrkEnergyPostCorr[nelecs] = Electron_energyScaleValue[nelecs] = Electron_energySigmaValue[nelecs] = Electron_energyScaleUp[nelecs] = Electron_energyScaleDown[nelecs] = Electron_energySigmaUp[nelecs] = Electron_energySigmaDown[nelecs] = 1;
      
      if(store_electron_scalnsmear){
	Electron_eccalTrkEnergyPostCorr[nelecs] = electron1.userFloat("ecalTrkEnergyPostCorr");
	Electron_energyScaleValue[nelecs] = electron1.userFloat("energyScaleValue");
	Electron_energySigmaValue[nelecs] = electron1.userFloat("energySigmaValue");
	Electron_energyScaleUp[nelecs] = electron1.userFloat("energyScaleUp");
	Electron_energyScaleDown[nelecs] = electron1.userFloat("energyScaleDown");
	Electron_energySigmaUp[nelecs] = electron1.userFloat("energySigmaUp");
	Electron_energySigmaDown[nelecs] = electron1.userFloat("energySigmaDown");
      }
      // end of scaling & smearing factors //
    
      bool impact_pass = 	((fabs(elsupcl_eta[nelecs])<1.4442 && fabs(eldxytrk[nelecs])<0.05 && fabs(eldztrk[nelecs])<0.1)
				 ||(fabs(elsupcl_eta[nelecs])>1.5660 && fabs(eldxytrk[nelecs])<(2*0.05) && fabs(eldztrk[nelecs])<(2*0.1)));
    
      /*  TLorentzVector tlel;
	  if (elmvaid_noIso[nelecs] && fabs(eleta[nelecs])<2.5) {
	  tlel.SetPtEtaPhiE(elpt[nelecs],eleta[nelecs],elphi[nelecs],electron1.energy());
	  tlvel.push_back(tlel);
	  }*/
      // Part below is added by Suman
      if (elpt[nelecs]*Electron_energyScaleValue[nelecs] > 30 && fabs(eleta[nelecs])<2.5) {
	tlvel.push_back(electron1);
      }
      
	
      if(++nelecs>=njetmx) break;                                                                                                                      
    }
    
    npfjetAK4 = 0;
    iEvent.getByToken(tok_pfjetAK4s_, pfjetAK4s);
    if(isMC){
      iEvent.getByToken(tok_genjetAK4s_, genjetAK4s);
    }
    
    for (unsigned jet = 0; jet< pfjetAK4s->size(); jet++) {
      
      const auto &ak4jet = (*pfjetAK4s)[jet];
      TLorentzVector pfjetAK44v(ak4jet.correctedP4("Uncorrected").px(),ak4jet.correctedP4("Uncorrected").py(),ak4jet.correctedP4("Uncorrected").pz(), ak4jet.correctedP4("Uncorrected").energy());
      
      /*
	double tmprecpt = pfjetAK44v.Pt();
      
	if (tlvmu.size()>0) {                                                                                           
	
	for (unsigned int imu = 0; imu<tlvmu.size(); imu++) {
	  
	bool mumember = false;
	int mu_index(-1);
	  
	for(unsigned int ic = 0 ; ic < ak4jet.numberOfDaughters() ; ++ic) {                                            
	    
	const pat::PackedCandidate* con = dynamic_cast<const pat::PackedCandidate*>(ak4jet.daughter(ic));          
            
	//TLorentzVector tlvcon(con->px(), con->py(), con->pz(), con->energy());
	if (delta2R(tlvmu[imu].Eta(),tlvmu[imu].Phi(),con->eta(),con->phi()) < 0.00001)                      
	{                                                                                                       
	mumember = true;                                                                                      
	mu_index = int(imu);
	break;
	}
	}
	  
	if (mumember) {
	// TLorentzVector hep_muv(tlvmu[mu_index].Px(),tlvmu[mu_index].Py(),tlvmu[mu_index].Pz(),tlvmu[mu_index].E());
	pfjetAK44v = pfjetAK44v - tlvmu[mu_index];
	//tmprecpt = pfjetAK44v.perp();
	}
	}
	}
      
	if (tlvel.size()>0) {
	for (unsigned int iel = 0; iel<tlvel.size(); iel++) {
	  
	bool elmember = false;
	int el_index(-1);
	  
	for(unsigned int c = 0 ; c < ak4jet.numberOfDaughters() ; ++c) {
	const pat::PackedCandidate* con = dynamic_cast<const pat::PackedCandidate*>(ak4jet.daughter(c));
	// TLorentzVector tlvcon(con->px(), con->py(), con->pz(), con->energy());
	if (delta2R(tlvel[iel].Eta(),tlvel[iel].Phi(),con->eta(),con->phi()) < 0.00001)
	{
	elmember = true;
	el_index = int(iel);
	break;
	}
	}
	  
	if (elmember) {
	// TLorentzVector hep_elv(tlvel[el_index].Px(),tlvel[el_index].Py(),tlvel[el_index].Pz(),tlvel[el_index].E());
	pfjetAK44v = pfjetAK44v - tlvel[el_index];
	//tmprecpt = pfjetAK44v.perp();
	}
	}
	}
      */
      // Changed by Suman 
	   pfjetAK44v = LeptonJet_subtraction(tlvmu,ak4jet,pfjetAK44v);
      pfjetAK44v = LeptonJet_subtraction(tlvel,ak4jet,pfjetAK44v);
      
      double tmprecpt = pfjetAK44v.Pt();
      if(tmprecpt<minPt) continue;
      if(fabs(pfjetAK44v.Eta())>maxEta) continue;
      
      pfjetAK4pt[npfjetAK4] = 	tmprecpt;
      pfjetAK4eta[npfjetAK4] = 	pfjetAK44v.Eta();
      pfjetAK4y[npfjetAK4] = pfjetAK44v.Rapidity();
      pfjetAK4phi[npfjetAK4] = pfjetAK44v.Phi();
      //if (ak4jet.correctedP4("Uncorrected").mass()<0) { 
      //std::cout << " mass " << pfjetAK44v.m() << " calculated mass " << sqrt(pfjetAK44v.e()*pfjetAK44v.e() - (pfjetAK44v.px()*pfjetAK44v.px() + pfjetAK44v.py()*pfjetAK44v.py() + pfjetAK44v.pz()*pfjetAK44v.pz())) << " stored mass " << ak4jet.correctedP4("Uncorrected").mass() << std::endl;
      //}
      pfjetAK4mass[npfjetAK4] = pfjetAK44v.M(); //ak4jet.correctedP4("Uncorrected").mass();
      
      pfjetAK4btag_DeepCSV[npfjetAK4] = ak4jet.bDiscriminator("pfDeepCSVJetTags:probb")+ak4jet.bDiscriminator("pfDeepCSVJetTags:probbb");
      pfjetAK4btag_DeepFlav[npfjetAK4] = ak4jet.bDiscriminator("pfDeepFlavourJetTags:probb") + ak4jet.bDiscriminator("pfDeepFlavourJetTags:probbb")+ak4jet.bDiscriminator("pfDeepFlavourJetTags:problepb");
      
      double total_cor =1;
      
      jecL1FastAK4->setJetPt(tmprecpt); jecL1FastAK4->setJetA(ak4jet.jetArea()); jecL1FastAK4->setRho(*Rho_PF);jecL1FastAK4->setJetEta(pfjetAK44v.Eta());
      double corFactorL1Fast = jecL1FastAK4->getCorrection();
      total_cor*= corFactorL1Fast;
      tmprecpt = tmprecpt * corFactorL1Fast;
      
      jecL2RelativeAK4->setJetPt(tmprecpt); jecL2RelativeAK4->setJetEta(pfjetAK44v.Eta());
      double corFactorL2Relative = jecL2RelativeAK4->getCorrection();
      total_cor*= corFactorL2Relative ;
      tmprecpt = tmprecpt * corFactorL2Relative;
      
      jecL3AbsoluteAK4->setJetPt(tmprecpt); jecL3AbsoluteAK4->setJetEta(pfjetAK44v.Eta());
      double corFactorL3Absolute = jecL3AbsoluteAK4->getCorrection();
      total_cor*= corFactorL3Absolute ;
      tmprecpt = tmprecpt * corFactorL3Absolute;
      
      double corFactorL2L3Residual=1.;
      
      if(isData){
	
	jecL2L3ResidualAK4->setJetPt(tmprecpt); jecL2L3ResidualAK4->setJetEta(pfjetAK44v.Eta());
	
	corFactorL2L3Residual = jecL2L3ResidualAK4->getCorrection();
	total_cor*= corFactorL2L3Residual;
	tmprecpt *=corFactorL2L3Residual;
      }
      
      pfjetAK4JEC[npfjetAK4] = total_cor;

      pfjetAK4hadronflav[npfjetAK4] = ak4jet.hadronFlavour();
      pfjetAK4partonflav[npfjetAK4] = ak4jet.partonFlavour();
      
      pfjetAK4qgl[npfjetAK4] = ak4jet.userFloat("QGTagger:qgLikelihood");
      pfjetAK4PUID[npfjetAK4] = ak4jet.userFloat("pileupJetId:fullDiscriminant");
      
      BTagEntry::JetFlavor btv_flav;
      if(abs(pfjetAK4hadronflav[npfjetAK4])==5){ btv_flav = BTagEntry::FLAV_B; }
      else if (abs(pfjetAK4hadronflav[npfjetAK4])==4){ btv_flav = BTagEntry::FLAV_C; }
      else { btv_flav = BTagEntry::FLAV_UDSG; }
      
      if(read_btagSF){
	
	pfjetAK4btag_DeepCSV_SF[npfjetAK4] = reader_deepcsv.eval_auto_bounds("central",btv_flav,fabs(pfjetAK44v.Eta()),tmprecpt); 
	pfjetAK4btag_DeepCSV_SF_up[npfjetAK4] = reader_deepcsv.eval_auto_bounds("up",btv_flav,fabs(pfjetAK44v.Eta()),tmprecpt);
	pfjetAK4btag_DeepCSV_SF_dn[npfjetAK4] = reader_deepcsv.eval_auto_bounds("down",btv_flav,fabs(pfjetAK44v.Eta()),tmprecpt);
	
	pfjetAK4btag_DeepFlav_SF[npfjetAK4] = reader_deepflav.eval_auto_bounds("central",btv_flav,fabs(pfjetAK44v.Eta()),tmprecpt); 
	pfjetAK4btag_DeepFlav_SF_up[npfjetAK4] = reader_deepflav.eval_auto_bounds("up",btv_flav,fabs(pfjetAK44v.Eta()),tmprecpt);
	pfjetAK4btag_DeepFlav_SF_dn[npfjetAK4] = reader_deepflav.eval_auto_bounds("down",btv_flav,fabs(pfjetAK44v.Eta()),tmprecpt);
      }
      
      if(isMC){
	
	JME::JetResolution resolution_AK4;
	resolution_AK4 = JME::JetResolution(mPtResoFileAK4.c_str());
	JME::JetResolutionScaleFactor res_sf_AK4;
	res_sf_AK4 = JME::JetResolutionScaleFactor(mPtSFFileAK4.c_str());
	
	JME::JetParameters parameters_5 = {{JME::Binning::JetPt, tmprecpt}, {JME::Binning::JetEta, pfjetAK44v.Eta()}, {JME::Binning::Rho, *Rho_PF}};
	double rp_AK4 = resolution_AK4.getResolution(parameters_5);
	double gaus_rp_AK4 = gRandom->Gaus(0.,rp_AK4);
	double sf_AK4 = res_sf_AK4.getScaleFactor(parameters_5, Variation::NOMINAL);
	double sf_up_AK4 = res_sf_AK4.getScaleFactor(parameters_5, Variation::UP);
	double sf_dn_AK4 = res_sf_AK4.getScaleFactor(parameters_5, Variation::DOWN);
	
	bool match_AK4 = false;
	int match_gen_AK4 = -1;
	
	for (unsigned get = 0; get<(genjetAK4s->size()); get++) {
	  TLorentzVector genjet4v((*genjetAK4s)[get].px(),(*genjetAK4s)[get].py(),(*genjetAK4s)[get].pz(), (*genjetAK4s)[get].energy());
	  if((delta2R(pfjetAK44v.Rapidity(),pfjetAK44v.Phi(),genjet4v.Rapidity(),genjet4v.Phi()) < (0.5*0.4)) &&(fabs(tmprecpt-genjet4v.Pt())<(3*fabs(rp_AK4)*tmprecpt))){
	    match_AK4 = true;
	    match_gen_AK4 = get;
	    break;
	  }
	}
	
	pfjetAK4GenMatch[npfjetAK4] = match_gen_AK4;
	
	if(match_AK4&&(match_gen_AK4>=0)){
	  pfjetAK4reso[npfjetAK4] = (sf_AK4-1.)*(tmprecpt-(*genjetAK4s)[match_gen_AK4].pt())*1./tmprecpt;
	  pfjetAK4resoup[npfjetAK4] = (sf_up_AK4-1.)*(tmprecpt-(*genjetAK4s)[match_gen_AK4].pt())*1./tmprecpt;
	  pfjetAK4resodn[npfjetAK4] = (sf_dn_AK4-1.)*(tmprecpt-(*genjetAK4s)[match_gen_AK4].pt())*1./tmprecpt;
	}else{
	  pfjetAK4reso[npfjetAK4] = sqrt(max(0.,(sf_AK4*sf_AK4-1))) * gaus_rp_AK4;
	  pfjetAK4resoup[npfjetAK4] = sqrt(max(0.,(sf_up_AK4*sf_up_AK4-1))) * gaus_rp_AK4;
	  pfjetAK4resodn[npfjetAK4] = sqrt(max(0.,(sf_dn_AK4*sf_dn_AK4-1))) * gaus_rp_AK4;
	}
      }//isMC
      
      // JES Uncertainty //

      pfjetAK4jesup_AbsoluteStat[npfjetAK4] = pfjetAK4jesup_AbsoluteScale[npfjetAK4] = pfjetAK4jesup_AbsoluteMPFBias[npfjetAK4] = pfjetAK4jesup_FlavorQCD[npfjetAK4] = pfjetAK4jesup_Fragmentation[npfjetAK4] = pfjetAK4jesup_PileUpDataMC[npfjetAK4] = pfjetAK4jesup_PileUpPtBB[npfjetAK4] = pfjetAK4jesup_PileUpPtEC1[npfjetAK4] = pfjetAK4jesup_PileUpPtEC2[npfjetAK4] = pfjetAK4jesup_PileUpPtHF[npfjetAK4] = pfjetAK4jesup_PileUpPtRef[npfjetAK4] = pfjetAK4jesup_RelativeFSR[npfjetAK4] = pfjetAK4jesup_RelativeJEREC1[npfjetAK4] = pfjetAK4jesup_RelativeJEREC2[npfjetAK4] = pfjetAK4jesup_RelativeJERHF[npfjetAK4] = pfjetAK4jesup_RelativePtBB[npfjetAK4] = pfjetAK4jesup_RelativePtEC1[npfjetAK4] = pfjetAK4jesup_RelativePtEC2[npfjetAK4] = pfjetAK4jesup_RelativePtHF[npfjetAK4] = pfjetAK4jesup_RelativeBal[npfjetAK4] = pfjetAK4jesup_RelativeSample[npfjetAK4] = pfjetAK4jesup_RelativeStatEC[npfjetAK4] = pfjetAK4jesup_RelativeStatHF[npfjetAK4] = pfjetAK4jesup_RelativeStatFSR[npfjetAK4] = pfjetAK4jesup_SinglePionECAL[npfjetAK4] = pfjetAK4jesup_SinglePionHCAL[npfjetAK4] = pfjetAK4jesup_TimePtEta[npfjetAK4] = pfjetAK4jesup_Total[npfjetAK4] = 1;
	
      for(int isrc =0 ; isrc<njecmcmx; isrc++){
	
	double sup = 1.0 ;
	
	if((isrc>0)&&(isrc<=nsrc)){
	  
	  JetCorrectionUncertainty *jecUnc = vsrc[isrc-1];
	  jecUnc->setJetEta(ak4jet.eta());
	  jecUnc->setJetPt(tmprecpt);
	  
	  sup += jecUnc->getUncertainty(true);
	  switch(isrc){
	  case 1:  pfjetAK4jesup_AbsoluteStat[npfjetAK4] = sup; break;
	  case 2:  pfjetAK4jesup_AbsoluteScale[npfjetAK4] = sup; break;
	  case 3:  pfjetAK4jesup_AbsoluteMPFBias[npfjetAK4] = sup; break;
	  case 4:  pfjetAK4jesup_FlavorQCD[npfjetAK4] = sup; break;
	  case 5:  pfjetAK4jesup_Fragmentation[npfjetAK4] = sup; break;
	  case 6:  pfjetAK4jesup_PileUpDataMC[npfjetAK4] = sup; break;
	  case 7:  pfjetAK4jesup_PileUpPtBB[npfjetAK4] = sup; break;
	  case 8:  pfjetAK4jesup_PileUpPtEC1[npfjetAK4] = sup; break;
	  case 9:  pfjetAK4jesup_PileUpPtEC2[npfjetAK4] = sup; break;
	  case 10:  pfjetAK4jesup_PileUpPtHF[npfjetAK4] = sup; break;
	  case 11:  pfjetAK4jesup_PileUpPtRef[npfjetAK4] = sup; break;
	  case 12:  pfjetAK4jesup_RelativeFSR[npfjetAK4] = sup; break;
	  case 13:  pfjetAK4jesup_RelativeJEREC1[npfjetAK4] = sup; break;
	  case 14:  pfjetAK4jesup_RelativeJEREC2[npfjetAK4] = sup; break;
	  case 15:  pfjetAK4jesup_RelativeJERHF[npfjetAK4] = sup; break;
	  case 16:  pfjetAK4jesup_RelativePtBB[npfjetAK4] = sup; break;
	  case 17:  pfjetAK4jesup_RelativePtEC1[npfjetAK4] = sup; break;
	  case 18:  pfjetAK4jesup_RelativePtEC2[npfjetAK4] = sup; break;
	  case 19:  pfjetAK4jesup_RelativePtHF[npfjetAK4] = sup; break;
	  case 20:  pfjetAK4jesup_RelativeBal[npfjetAK4] = sup; break;
	  case 21:  pfjetAK4jesup_RelativeSample[npfjetAK4] = sup; break;
	  case 22:  pfjetAK4jesup_RelativeStatEC[npfjetAK4] = sup; break;
	  case 23:  pfjetAK4jesup_RelativeStatHF[npfjetAK4] = sup; break;
	  case 24:  pfjetAK4jesup_RelativeStatFSR[npfjetAK4] = sup; break;
	  case 25:  pfjetAK4jesup_SinglePionECAL[npfjetAK4] = sup; break;
	  case 26:  pfjetAK4jesup_SinglePionHCAL[npfjetAK4] = sup; break;
	  case 27:  pfjetAK4jesup_TimePtEta[npfjetAK4] = sup; break;
	  case 28:  pfjetAK4jesup_Total[npfjetAK4] = sup; break;
	  default: continue;
	  }
	}
	
	else if(isrc>nsrc){
	  
	  JetCorrectionUncertainty *jecUnc = vsrc[isrc-1-nsrc];
	  jecUnc->setJetEta(ak4jet.eta());
	  jecUnc->setJetPt(tmprecpt);
	  
	  sup -= jecUnc->getUncertainty(false);
	  switch(isrc){
	  case (nsrc+1):  pfjetAK4jesdn_AbsoluteStat[npfjetAK4] = sup; break;
	  case (nsrc+2):  pfjetAK4jesdn_AbsoluteScale[npfjetAK4] = sup; break;
	  case (nsrc+3):  pfjetAK4jesdn_AbsoluteMPFBias[npfjetAK4] = sup; break;
	  case (nsrc+4):  pfjetAK4jesdn_FlavorQCD[npfjetAK4] = sup; break;
	  case (nsrc+5):  pfjetAK4jesdn_Fragmentation[npfjetAK4] = sup; break;
	  case (nsrc+6):  pfjetAK4jesdn_PileUpDataMC[npfjetAK4] = sup; break;
	  case (nsrc+7):  pfjetAK4jesdn_PileUpPtBB[npfjetAK4] = sup; break;
	  case (nsrc+8):  pfjetAK4jesdn_PileUpPtEC1[npfjetAK4] = sup; break;
	  case (nsrc+9):  pfjetAK4jesdn_PileUpPtEC2[npfjetAK4] = sup; break;
	  case (nsrc+10):  pfjetAK4jesdn_PileUpPtHF[npfjetAK4] = sup; break;
	  case (nsrc+11):  pfjetAK4jesdn_PileUpPtRef[npfjetAK4] = sup; break;
	  case (nsrc+12):  pfjetAK4jesdn_RelativeFSR[npfjetAK4] = sup; break;
	  case (nsrc+13):  pfjetAK4jesdn_RelativeJEREC1[npfjetAK4] = sup; break;
	  case (nsrc+14):  pfjetAK4jesdn_RelativeJEREC2[npfjetAK4] = sup; break;
	  case (nsrc+15):  pfjetAK4jesdn_RelativeJERHF[npfjetAK4] = sup; break;
	  case (nsrc+16):  pfjetAK4jesdn_RelativePtBB[npfjetAK4] = sup; break;
	  case (nsrc+17):  pfjetAK4jesdn_RelativePtEC1[npfjetAK4] = sup; break;
	  case (nsrc+18):  pfjetAK4jesdn_RelativePtEC2[npfjetAK4] = sup; break;
	  case (nsrc+19):  pfjetAK4jesdn_RelativePtHF[npfjetAK4] = sup; break;
	  case (nsrc+20):  pfjetAK4jesdn_RelativeBal[npfjetAK4] = sup; break;
	  case (nsrc+21):  pfjetAK4jesdn_RelativeSample[npfjetAK4] = sup; break;
	  case (nsrc+22):  pfjetAK4jesdn_RelativeStatEC[npfjetAK4] = sup; break;
	  case (nsrc+23):  pfjetAK4jesdn_RelativeStatHF[npfjetAK4] = sup; break;
	  case (nsrc+24):  pfjetAK4jesdn_RelativeStatFSR[npfjetAK4] = sup; break;
	  case (nsrc+25):  pfjetAK4jesdn_SinglePionECAL[npfjetAK4] = sup; break;
	  case (nsrc+26):  pfjetAK4jesdn_SinglePionHCAL[npfjetAK4] = sup; break;
	  case (nsrc+27):  pfjetAK4jesdn_TimePtEta[npfjetAK4] = sup; break;
	  case (nsrc+28):  pfjetAK4jesdn_Total[npfjetAK4] = sup; break;
	  default: continue;
	  }
	}
	
      }
      
      // JES uncertainty Ends //
    
      // Jet id //
     
      pfjetAK4CHF[npfjetAK4] = ak4jet.chargedHadronEnergyFraction();
      pfjetAK4NHF[npfjetAK4] = ak4jet.neutralHadronEnergyFraction();
      pfjetAK4CEMF[npfjetAK4] = ak4jet.chargedEmEnergyFraction();
      pfjetAK4NEMF[npfjetAK4] = ak4jet.neutralEmEnergyFraction();
      pfjetAK4MUF[npfjetAK4] = ak4jet.muonEnergyFraction();
      
      pfjetAK4PHF[npfjetAK4] = ak4jet.photonEnergyFraction();
      pfjetAK4EEF[npfjetAK4] = ak4jet.electronEnergyFraction();
      pfjetAK4HFEMF[npfjetAK4] = ak4jet.HFEMEnergyFraction();
      
      pfjetAK4CHM[npfjetAK4] = ak4jet.chargedHadronMultiplicity();
      pfjetAK4NHM[npfjetAK4] = ak4jet.neutralHadronMultiplicity();
      
      pfjetAK4MUM[npfjetAK4] = ak4jet.muonMultiplicity();
      pfjetAK4PHM[npfjetAK4] = ak4jet.photonMultiplicity();
      pfjetAK4EEM[npfjetAK4] = ak4jet.electronMultiplicity();
      pfjetAK4HFEMM[npfjetAK4] = ak4jet.HFEMMultiplicity();
      
      pfjetAK4Chcons[npfjetAK4] = ak4jet.chargedMultiplicity();
      pfjetAK4Neucons[npfjetAK4] = ak4jet.neutralMultiplicity();
      
      JetIDVars AK4idvars;
      
      AK4idvars.NHF = pfjetAK4NHF[npfjetAK4];
      AK4idvars.NEMF = pfjetAK4NEMF[npfjetAK4];
      AK4idvars.MUF = pfjetAK4MUF[npfjetAK4];
      AK4idvars.CHF = pfjetAK4CHF[npfjetAK4];
      AK4idvars.CEMF = pfjetAK4CEMF[npfjetAK4];
      AK4idvars.NumConst = (pfjetAK4Chcons[npfjetAK4]+pfjetAK4Neucons[npfjetAK4]);
      AK4idvars.NumNeutralParticle = pfjetAK4Neucons[npfjetAK4];
      AK4idvars.CHM = pfjetAK4CHM[npfjetAK4];
      
      pfjetAK4jetID[npfjetAK4] = getJetID(AK4idvars,"CHS",year,pfjetAK4eta[npfjetAK4],false,isUltraLegacy);
      pfjetAK4jetID_tightlepveto[npfjetAK4] = getJetID(AK4idvars,"CHS",year,pfjetAK4eta[npfjetAK4],true,isUltraLegacy);
      
      npfjetAK4++;	
      if(npfjetAK4 >= njetmx) { break;}
    }
  
  
    //booltrg
    for(int jk=0; jk<nHLTmx; jk++) {
    
      switch(jk) {
	
      case 0 :
	hlt_IsoMu24 = booltrg[jk];
	psfactor_hlt_IsoMu24 = psfactor_booltrg[jk];
	break;
      
      case 1 :
	hlt_Mu50 = booltrg[jk];
	psfactor_hlt_Mu50 = psfactor_booltrg[jk];
	break;
      
      case 2 :
	hlt_Ele50_PFJet165 = booltrg[jk];
	psfactor_hlt_Ele50_PFJet165 = psfactor_booltrg[jk];
	break;
      
      case 3 :
	hlt_Ele115 = booltrg[jk];
	psfactor_hlt_Ele115 = psfactor_booltrg[jk];
	break;
      
      case 4 :
	hlt_AK8PFJet500 = booltrg[jk];
	psfactor_hlt_AK8PFJet500 = psfactor_booltrg[jk];
	break;
      
      case 5 :
	hlt_Photon200 = booltrg[jk];
	psfactor_hlt_Photon200 = psfactor_booltrg[jk];
	break;
      
      case 6 :
	hlt_Mu37Ele27 = booltrg[jk];
	psfactor_hlt_Mu37Ele27 = psfactor_booltrg[jk];
	break;
      
      case 7 :
	hlt_Mu27Ele37 = booltrg[jk];
	psfactor_hlt_Mu27Ele37 = psfactor_booltrg[jk];
	break;
      
      case 8 :
	hlt_Mu37TkMu27 = booltrg[jk];
	psfactor_hlt_Mu37TkMu27 = psfactor_booltrg[jk];
	break;
      
      case 9 :
	hlt_OldMu100 = booltrg[jk];
	psfactor_hlt_OldMu100 = psfactor_booltrg[jk];
	break;
	  
      case 10 :
	hlt_TkMu100 = booltrg[jk];
	psfactor_hlt_TkMu100 = psfactor_booltrg[jk];
	break;
      
      case 11 :
	hlt_DoubleEle25 = booltrg[jk];
	psfactor_hlt_DoubleEle25 = psfactor_booltrg[jk];
	break;

      case 12 :
	hlt_PFMET250 = booltrg[jk];
	psfactor_hlt_PFMET250 = psfactor_booltrg[jk];
	break;
      
      case 13 :
	hlt_PFMET300 = booltrg[jk];
	psfactor_hlt_PFMET300 = psfactor_booltrg[jk];
	break;

      case 14 :
	hlt_PFMET200 = booltrg[jk];
	psfactor_hlt_PFMET200 = psfactor_booltrg[jk];
	break;

      case 15 :
	hlt_PFMET200_TypeOne = booltrg[jk];
	psfactor_hlt_PFMET200_TypeOne = psfactor_booltrg[jk];
	break;

      case 16 :
	hlt_AK8PFHT800_TrimMass50 = booltrg[jk];
	psfactor_hlt_AK8PFHT800_TrimMass50 = psfactor_booltrg[jk];
	break;

      case 17 :
	hlt_AK8PFHT900_TrimMass50 = booltrg[jk];
	psfactor_hlt_AK8PFHT900_TrimMass50 = psfactor_booltrg[jk];
	break;

      case 18 :
	hlt_AK8PFJet400_TrimMass30 = booltrg[jk];
	psfactor_hlt_AK8PFJet400_TrimMass30 = psfactor_booltrg[jk];
	break;
	
      case 19 :
	hlt_AK8PFJet420_TrimMass30 = booltrg[jk];
	psfactor_hlt_AK8PFJet420_TrimMass30 = psfactor_booltrg[jk];
	break;
	
      case 20 :
	hlt_AK8PFJet550 = booltrg[jk];
	psfactor_hlt_AK8PFJet550 = psfactor_booltrg[jk];
	break;
	
      case 21 :
	hlt_CaloJet500_NoJetID = booltrg[jk];
	psfactor_hlt_CaloJet500_NoJetID = psfactor_booltrg[jk];
	break;
	
      case 22 :
	hlt_PFHT1050 = booltrg[jk];
	psfactor_hlt_PFHT1050 = psfactor_booltrg[jk];
	break;
	
      case 23 :
	hlt_PFJet500 = booltrg[jk];
	psfactor_hlt_PFJet500 = psfactor_booltrg[jk];
	break;

      case 24 :
	hlt_AK8PFJet320 = booltrg[jk];
	psfactor_hlt_AK8PFJet320 = psfactor_booltrg[jk];
	break;

      case 25 :
	hlt_AK8PFJet330_PFAK8BTagDeepCSV = booltrg[jk];
	psfactor_hlt_AK8PFJet330_PFAK8BTagDeepCSV = psfactor_booltrg[jk];
	break;

      case 26 :
	hlt_AK8PFJet360_TrimMass30 = booltrg[jk];
	psfactor_hlt_AK8PFJet360_TrimMass30 = psfactor_booltrg[jk];
	break;

      case 27 :
	hlt_DiPFJetAve400 = booltrg[jk];
	psfactor_hlt_DiPFJetAve400 = psfactor_booltrg[jk];
	break;

      case 28 :
	hlt_PFJet400 = booltrg[jk];
	psfactor_hlt_PFJet400 = psfactor_booltrg[jk];
	break;
	
      case 29 :
	hlt_PFJet320 = booltrg[jk];
	psfactor_hlt_PFJet320 = psfactor_booltrg[jk];
	break;
	
      case 30 :
	hlt_PFJet200 = booltrg[jk];
	psfactor_hlt_PFJet200 = psfactor_booltrg[jk];
	break;
	
      case 31 :
	hlt_CaloMET100_HBHECleaned = booltrg[jk];
	psfactor_hlt_CaloMET100_HBHECleaned = psfactor_booltrg[jk];
	break;
	
      case 32 :
	hlt_CaloMET250_HBHECleaned = booltrg[jk];
	psfactor_hlt_CaloMET250_HBHECleaned = psfactor_booltrg[jk];
	break;
	
      case 33 :
	hlt_CaloMET90_HBHECleaned = booltrg[jk];
	psfactor_hlt_CaloMET90_HBHECleaned = psfactor_booltrg[jk];
	break;

      case 34 :
	hlt_CaloMET70_HBHECleaned = booltrg[jk];
	psfactor_hlt_CaloMET70_HBHECleaned = psfactor_booltrg[jk];
	break;

      case 35 :
	hlt_PFMETTypeOne140_PFMHT140_IDTight = booltrg[jk];
	psfactor_hlt_PFMETTypeOne140_PFMHT140_IDTight = psfactor_booltrg[jk];
	break;

      case 36 :
	hlt_PFMETTypeOne120_PFMHT120_IDTight = booltrg[jk];
	psfactor_hlt_PFMETTypeOne120_PFMHT120_IDTight = psfactor_booltrg[jk];
	break;

      case 37 :
	hlt_CaloMET80_HBHECleaned = booltrg[jk];
	psfactor_hlt_CaloMET80_HBHECleaned = psfactor_booltrg[jk];
	break;
      }
    }	  
    //  cout<<"done!"<<endl;
    //std::cout << " npfjetAK8 " << npfjetAK8 << std::endl;
    T1->Fill();
  
  }// skimming condition
  
  if (isMC) { T2->Fill();} // filling the tree used to get sumofweights
}


// ------------ method called once each job just before starting event loop  ------------
void 
Leptop::beginJob()
{
  
  Nevt = 0;
  /* 
     for(int ij=0; ij<nomassbins; ij++){
     massbins[ij] = 10*ij ;
     }
     
     rhobins[0] = 0.005;
     
     for(int ij=1; ij<norhobins; ij++){
     rhobins[ij] = width*rhobins[ij-1] ;
     }
  */
  ////JEC /////
  L1FastAK4       = new JetCorrectorParameters(mJECL1FastFileAK4.c_str());
  L2RelativeAK4   = new JetCorrectorParameters(mJECL2RelativeFileAK4.c_str());
  L3AbsoluteAK4   = new JetCorrectorParameters(mJECL3AbsoluteFileAK4.c_str());
  L2L3ResidualAK4 = new JetCorrectorParameters(mJECL2L3ResidualFileAK4.c_str());
  
  vecL1FastAK4.push_back(*L1FastAK4);
  vecL2RelativeAK4.push_back(*L2RelativeAK4);
  vecL3AbsoluteAK4.push_back(*L3AbsoluteAK4);
  vecL2L3ResidualAK4.push_back(*L2L3ResidualAK4);
  
  jecL1FastAK4       = new FactorizedJetCorrector(vecL1FastAK4);
  jecL2RelativeAK4   = new FactorizedJetCorrector(vecL2RelativeAK4);
  jecL3AbsoluteAK4   = new FactorizedJetCorrector(vecL3AbsoluteAK4);
  jecL2L3ResidualAK4 = new FactorizedJetCorrector(vecL2L3ResidualAK4);
  
  L1FastAK8       = new JetCorrectorParameters(mJECL1FastFileAK8.c_str());
  L2RelativeAK8   = new JetCorrectorParameters(mJECL2RelativeFileAK8.c_str());
  L3AbsoluteAK8   = new JetCorrectorParameters(mJECL3AbsoluteFileAK8.c_str());
  L2L3ResidualAK8 = new JetCorrectorParameters(mJECL2L3ResidualFileAK8.c_str());
  
  vecL1FastAK8.push_back(*L1FastAK8);
  vecL2RelativeAK8.push_back(*L2RelativeAK8);
  vecL3AbsoluteAK8.push_back(*L3AbsoluteAK8);
  vecL2L3ResidualAK8.push_back(*L2L3ResidualAK8);
  
  jecL1FastAK8       = new FactorizedJetCorrector(vecL1FastAK8);
  jecL2RelativeAK8   = new FactorizedJetCorrector(vecL2RelativeAK8);
  jecL3AbsoluteAK8   = new FactorizedJetCorrector(vecL3AbsoluteAK8);
  jecL2L3ResidualAK8 = new FactorizedJetCorrector(vecL2L3ResidualAK8);
  
  for (int isrc = 0; isrc < nsrc; isrc++) {
    const char *name = jecsrcnames[isrc];
    JetCorrectorParameters *pAK4 = new JetCorrectorParameters(mJECUncFileAK4.c_str(), name) ;
    JetCorrectionUncertainty *uncAK4 = new JetCorrectionUncertainty(*pAK4);
    vsrc.push_back(uncAK4);
    JetCorrectorParameters *pAK8 = new JetCorrectorParameters(mJECUncFileAK8.c_str(), name) ;
    JetCorrectionUncertainty *uncAK8 = new JetCorrectionUncertainty(*pAK8);
    vsrcAK8.push_back(uncAK8);
  }
  
  if(read_btagSF){
    calib_deepcsv = BTagCalibration("DeepCSV", mBtagSF_DeepCSV.c_str());
    reader_deepcsv = BTagCalibrationReader(BTagEntry::OP_MEDIUM, "central", {"up", "down"}); 
    reader_deepcsv.load(calib_deepcsv, BTagEntry::FLAV_B, "comb");
    reader_deepcsv.load(calib_deepcsv, BTagEntry::FLAV_C, "comb");
    reader_deepcsv.load(calib_deepcsv, BTagEntry::FLAV_UDSG, "incl");
    
    calib_deepflav = BTagCalibration("DeepJet", mBtagSF_DeepFlav.c_str());
    reader_deepflav = BTagCalibrationReader(BTagEntry::OP_MEDIUM, "central", {"up", "down"}); 
    reader_deepflav.load(calib_deepflav, BTagEntry::FLAV_B, "comb");
    reader_deepflav.load(calib_deepflav, BTagEntry::FLAV_C, "comb");
    reader_deepflav.load(calib_deepflav, BTagEntry::FLAV_UDSG, "incl");
  }
  
  //**Important**//
  //For precision top physics, change "comb" to "mujets" in BTagCalibrationReader above //
  //https://twiki.cern.ch/twiki/bin/view/CMS/BtagRecommendation106XUL18#Additional_information
  
  if(isUltraLegacy)
    {
      if(year==2018){
	roch_cor.init((mRochcorFolder+"RoccoR2018UL.txt").c_str()); 
      }
      if(year==2017){
	roch_cor.init((mRochcorFolder+"RoccoR2017UL.txt").c_str()); 
      }
      if(year==2016){
	roch_cor.init((mRochcorFolder+"RoccoR2016aUL.txt").c_str()); 
      }
    }
  else{
    roch_cor.init((mRochcorFolder+"RoccoR2017.txt").c_str()); 
  }
  
}

// ------------ method called once each job just after ending the event loop  ------------
void 
Leptop::endJob() 
{
    
  theFile->cd();
  theFile->Write();
  theFile->Close();
}

// ------------ method called when starting to processes a run  ------------
void 
Leptop::beginRun(edm::Run const& iRun, edm::EventSetup const& pset)
{
  bool changed(true);
  hltPrescaleProvider_.init(iRun,pset,theHLTTag,changed);
  HLTConfigProvider const&  hltConfig_ = hltPrescaleProvider_.hltConfigProvider();
  hltConfig_.dump("Triggers");
  hltConfig_.dump("PrescaleTable");
}

// ------------ method called when ending the processing of a run  ------------
void 
Leptop::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
Leptop::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
Leptop::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
Leptop::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(Leptop);
