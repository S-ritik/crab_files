import fileinput, string, sys, os, time, datetime
import argparse as arg

parser = arg.ArgumentParser(description='inputs discription')
parser.add_argument('-y', '--year', dest='inputs', type=str, nargs=1, help="Year [UL2016preVFP, UL2016postVFP, UL2017, UL2018]")
args = parser.parse_args()


if args.inputs == None:
        print "USAGE: %s [-h] [-y <Data year>]"%(sys.argv [0])
        sys.exit (1)

if args.inputs[0] not in ['UL2018']:
    print('Error: Incorrect choice of year, use -h for help')
    exit()

print "year = ",args.inputs[0]
year   = args.inputs[0]
date   = datetime.datetime.today().strftime('%d_%m_%Y')

if(year == 'UL2018'):
    from mcdataset_UL2018 import *
    Datasets = Datasets_MC_2018

RequestName = Datasets.keys()
print "len(Datasets) = ",len(Datasets)

cfgfile = "crabConfig_JERCL5_MCsamples.py"
outputDir = "/store/user/rsaxena/boosted_ttbar_15june_2022/"

f = open("check_status_crab.txt", "a")

def replacemachine(fileName, sourceText, replaceText):
    ##################################################################
    for line in fileinput.input(fileName, inplace=True):
        if line.strip().startswith(sourceText):
        	line = replaceText
    	sys.stdout.write(line)
    print "All went well, the modifications are done"
    ##################################################################

#print RequestName
for i in range(0,len(Datasets)):
        print RequestName[i], " : ",Datasets[RequestName[i]]
        update_RequestName = "config.General.requestName = '" + RequestName[i] + "_" + date + "'\n" 
        update_Dataset = "config.Data.inputDataset = '" + Datasets[RequestName[i]] + "'\n"
        update_DirBase = "config.Data.outLFNDirBase = '" + outputDir + "'\n"
        update_InputFiles = "config.JobType.inputFiles = ['Summer19UL18_V5_MC','Summer19UL18_JRV2_MC','BtagRecommendation106XUL18','roccor.Run2.v5']\n"
        update_WorkArea = "config.General.workArea = '" + "logs/" + RequestName[i] + "_" + year + "'\n"
    
        #update_DatasetTag = "config.Data.outputDatasetTag = 'Tree_"+date.strftime("%d")+"_"+date.strftime("%b")+date.strftime("%y")+"_MC"+year+"_"+RequestName[i]+"_check'\n"
     
        print "RequestName = ",update_RequestName ,"\tDatasets = ",update_Dataset,"\tDirBase = ",update_DirBase
        print "InputFiles = ",update_InputFiles
        
        replacemachine(cfgfile,'config.General.requestName', update_RequestName)
        replacemachine(cfgfile,'config.Data.inputDataset', update_Dataset )
        replacemachine(cfgfile,'config.Data.outLFNDirBase', update_DirBase )
        replacemachine(cfgfile,'config.JobType.inputFiles', update_InputFiles )
        replacemachine(cfgfile,'config.General.workArea', update_WorkArea )
        #replacemachine(cfgfile,'config.Data.outputDatasetTag', update_DatasetTag )
     
        cmd_crab_submit = "crab submit -c " + cfgfile
        os.system(cmd_crab_submit)  
        
        ln = "crab status -d " + "logs/" + RequestName[i] + "_" + year + "/crab_" + RequestName[i] + "_" + date + "\n";
        f.write(ln)


        cmd_crab_kill = "crab kill -d " + "logs/" + RequestName[i] + "_" + year + "/crab_" + RequestName[i] + "_" + date
        #os.system(cmd_crab_kill)
        
        cmd_rm_dir = "rm -rf " + "logs/" + RequestName[i] + "_" + year + "/crab_" + RequestName[i] + "_" + date
        #os.system(cmd_rm_dir)
        
        
        print "DONE -----",RequestName[i],"--------------------------------------------------------------------------------------------"
        #time.sleep(10) 
    
f.close()
