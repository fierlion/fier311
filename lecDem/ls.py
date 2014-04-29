import subprocess
import shlex
import os
import sys
import stat
import time

def ls_os(path):
    files = os.listdir(path)
    files.extend('. ..'.split())

    sorted_files = []

    for f in files:
        status = os.lstat(f)
        perms = status.st_mode
        uid = status.st_uid
        gid = status.st_gid
        size = status.st_size
        mtime = status.st_mtime
        links = status.st_nlink

        file_mdata = [mtime, perms, uid, gid, size, f, links]

        sorted_files.append(file_mdata)
    sorted_files.sort()
    
    for f in sorted_files:
        print f[1], f[6], f[2], f[3], '%4s' % f[4], ' '.join(time.ctime(f[0]).split()[1:4]), 
        if os.path.islink(f[5]):
            print f[5] + '->' + os.readlink(f[5])
        else:
            print f[5]
def ls_sp():
    command = 'ls -l -a -t -r -n'
    #long format all files time ordered reverse numeric group id
    command_sequence = shlex.split(command)
    #print command_sequence

    ls = subprocess.Popen(command_sequence, stdout=subprocess.PIPE)
    ls_out = ls.stdout.readlines()

    for line in ls_out:
        print line,

if __name__=="__main__":
    ls_os('.')
