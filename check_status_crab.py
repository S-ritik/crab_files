
##  Runs with python3 only #####


import os
import subprocess as sp


f = open("check_status_crab.txt","r")
cmds = f.readlines()
f.close()

n_fail = 0
n_complete = 0
n_unsubmited = 0
n_idle = 0
n_incomp_dataset = 0
n_submitfail = 0
ncount = 0

check_commands = []
unsubmitted_jobs = []
incomplete_datasets = []
idle_jobs = []
submitfail = []
loglist = []

def get_resubmit_command(cmd):
    st = cmd.replace("status","resubmit")
    return st

for i in range(0,len(cmds)):
    out = sp.getoutput(cmds[i])

    if "SUBMITFAILED" in out:
        print(cmds[i], " has failed to submit the crab jobs")
        n_submitfail += 1
        submitfail.append(cmds[i])
        continue

    x = out.split("\n\n")

    #print(x)
    if "not a valid CRAB project directory" in out or out.startswith("Error"):
        check_commands.append(cmds[i])
    
    lin = x[1].split("\n")
    index = 0
    for ij in range(len(lin)):
        if "finished" in lin[ij]:
            index = ij
    log = cmds[i] + lin[index]
    
    loglist.append(log)
    
    if "failed" in x[1]:
        n_fail += 1
        resubmit_cmd = get_resubmit_command(cmds[i])
        os.system(resubmit_cmd)
        #print(resubmit_cmd)
    
    if "unsubmitted" in x[1]:
        str = "not found"
        for line in x[1].split("\n"):
            if "unsubmitted" in line:
                str = line
        n_unsubmited += 1
        tot = cmds[i] + str
        unsubmitted_jobs.append(tot)

    if "idle" in x[1]:
        str = "not found"
        for line in x[1].split("\n"):
            if "idle" in line:
                str = line
        tot = cmds[i] + str
        n_idle += 1
        idle_jobs.append(tot)

    if "they are only present at blacklisted" in out or "block" in out:
        n_incomp_dataset += 1
        incomplete_datasets.append(cmds[i])

    if "finished     \t\t100" in x[1] and  "\n\t\t\t" not in x[1]:
        n_complete += 1
        #print(cmds[i])
    else:
        print(out) 
    #print(cmds[i])

#n_complete = len(cmds) - n_fail - n_unsubmited - n_incomp_dataset - n_idle
if n_complete == ncount:
    print("Some thing is wrong! Check individual file and cross check numbers")


if len(check_commands) > 0:
    print("Check following commands")
    for i in check_commands:
        print(i)
    print("\n\n")

if len(unsubmitted_jobs) > 0:
    print("These jobs have unsubmitted jobs")
    for i in unsubmitted_jobs:
        print(i)
    print("\n\n")

if len(idle_jobs) > 0:
    print("These jobs have idle jobs")
    for i in idle_jobs:
        print(i)
    print("\n\n")

if len(incomplete_datasets) > 0:
    print("Thses jobs have incplete dataset")
    for i in incomplete_datasets:
        print(i)
    print("\n\n")


print("No. of total checked jobs = ",len(cmds))
print("No. of fully finished jobs = ",n_complete)
print("No. of jobs which have failed task(s) = ",n_fail)
print("No. of jobs which have unsubmitted task(s) = ",n_unsubmited)
print("No. of jobs which have idle task(s) = ",n_idle)
print("No. of jobs which have incompleted dataset on sites = ",n_incomp_dataset)
print("No. of jobs which have failed to be submitted = ",n_submitfail,"\n\n")


#loglist = sorted(loglist, key=str.casefold)
loglist.sort()
for i in range(0,len(loglist)):
    print(loglist[i])

if(n_submitfail > 0):
    print("\n\nJobs failed to  be submitted to crab are")
    for i in range(0,len(submitfail)):
        print(submitfail[i])
