#Ray Allan Foote
#footer@onid.orst.edu
#CS311_400
#Assignment 2 / Part 5 

"""
This script uses subprocess.Popen() to connect to the unix command 'who' 
and prints the results in the same format as .
Ex 
"""

import sys
import getopt
import os
import subprocess

class Usage(Exception):
    def __init__(self, msg):
        self.msg = msg

def main(argv=None):
#parse command line options
    if argv is None:
        argv = sys.argv
    try:
        try:
            opts, args = getopt.getopt(sys.argv[1:], "bldprTtu")
        except getopt.error, msg:
            raise Usage(msg)
#process options
        argList = []
        for o, a in opts:
            if o in ("-h", "--help"):
                print __doc__
            if o in ("-b"):
                argList.append(o)
            if o in ("-l"):
                argList.append(o)
            if o in ("-d"):
                argList.append(o)
            if o in ("-p"):
                argList.append(o)
            if o in ("-r"):
                argList.append(o)
            if o in ("-T"):
                argList.append(o)
            if o in ("-t"):
                argList.append(o)
            if o in ("-u"):
                argList.append(o)
        pyWho(argList)
        return 0
#process arguments
    except Usage, err:
        print >>sys.stderr, err.msg
        print >>sys.stderr, "for help use --help"
        return 2

def pyWho(argsIn):
    command = ["who"]
    for arg in argsIn:
        command.append(arg)
    whoRaw = subprocess.Popen(command, stdout=subprocess.PIPE)
    print whoRaw.communicate()[0]

if __name__=="__main__":
    sys.exit(main())

