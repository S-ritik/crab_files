from CRABClient.UserUtilities import config
config = config()
config.General.requestName = 'crab_L5JERC_DoubleMuon_2018A_20UL18_JERCL5_Run1'
config.General.workArea = 'crab_L5JERC_DoubleMuon_2018A_20UL18_JERCL5_TestRun'
config.General.transferOutputs = True
config.General.transferLogs = True
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'JEC_Data_2018A_MINIAOD_cfg.py' 
config.JobType.inputFiles = ['Summer19UL18_RunA_V5_DATA','Summer19UL18_JRV2_MC_SF_AK8PFPuppi.txt','Summer19UL18_JRV2_MC_SF_AK4PFchs.txt','Summer19UL18_JRV2_MC_PtResolution_AK4PFchs.txt','Summer19UL18_JRV2_MC_PtResolution_AK8PFPuppi.txt']
config.JobType.disableAutomaticOutputCollection = True
config.JobType.outputFiles = ['hist_jerc_l5.root','rootuple_jerc_l5.root']
#config.JobType.maxJobRuntimeMin = 2700
#config.JobType.maxMemoryMB = 2480
config.JobType.allowUndistributedCMSSW = True
config.Data.inputDataset = '/DoubleMuon/Run2018A-12Nov2019_UL2018-v2/MINIAOD'
config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 6
config.Data.lumiMask ='/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions18/13TeV/Legacy_2018/Cert_314472-325175_13TeV_Legacy2018_Collisions18_JSON.txt'
#/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions18/13TeV/ReReco/Cert_314472-325175_13TeV_17SeptEarlyReReco2018ABC_PromptEraD_Collisions18_JSON.txt'
#config.Data.runRange = '258214-258287' # '193093-194075'
config.Data.outLFNDirBase = '/store/user/rsaxena/' #% (getUsernameFromSiteDB())
config.Data.publication = False
#config.Data.publishDataName = 'May2015_Data_analysis'

config.Site.storageSite = 'T2_IN_TIFR'
#config.Site.whitelist = ["T2_IN_TIFR"]
config.Site.blacklist=['T2_US_Caltech','T2_US_UCSD']
