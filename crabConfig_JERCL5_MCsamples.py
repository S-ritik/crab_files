from CRABClient.UserUtilities import config #, getUsernameFromSiteDB
config = config()


config.General.requestName = 'WJetsToLNu_HT_70to100_19_09_2022'
config.General.workArea = 'logs/WJetsToLNu_HT_70to100_UL2018'
config.General.transferOutputs = True
config.General.transferLogs = True


config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'JEC_MC_MINIAOD_cfg.py' 
config.JobType.outputFiles = ['hist_jerc_l5.root','rootuple_jerc_l5.root']

config.JobType.inputFiles = ['Summer19UL18_V5_MC','Summer19UL18_JRV2_MC','BtagRecommendation106XUL18','roccor.Run2.v5']
config.JobType.disableAutomaticOutputCollection = True
config.JobType.maxJobRuntimeMin = 2700
#config.JobType.maxJobRuntimeMin = 1500
config.JobType.maxMemoryMB = 1999
config.JobType.allowUndistributedCMSSW = True


config.Data.inputDataset = '/WJetsToLNu_HT-70To100_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM'
config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 4
config.Data.outLFNDirBase = '/store/user/rsaxena/boosted_ttbar_15june_2022/'
config.Data.publication = False


#config.Site.storageSite = 'T3_US_FNALLPC'
config.Site.storageSite = 'T2_IN_TIFR'
config.Site.ignoreGlobalBlacklist= True
