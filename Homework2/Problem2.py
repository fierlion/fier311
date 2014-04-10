#Ray Allan Foote
#footer@onid.orst.edu
#CS311_400
#Assignment 2 / Part 2 

"""
This script creates the following directories (under your
home directory or a subdirectory of your home) for a command
line given '-t' [term] and '-c' [class]
assignments, examples, exams, lecture_notes, submissions
Example usage:
python Problem2.py -t spring2014 -c cs311   ...or...
python Problem2.py --term spring2014 --class cs311
"""

import sys
import getopt
import os
import subprocess

class Usage(Exception):
    def __init__(self, msg):
        self.msg = msg

class cd:
    """Context manager for changing the current working directory from
        'http://stackoverflow.com/questions/431684/how-do-i-cd-in-python'"""
    def __init__(self, newPath):
        self.newPath = newPath

    def __enter__(self):
        self.savedPath = os.getcwd()
        os.chdir(self.newPath)

    def __exit__(self, etype, value, traceback):
        os.chdir(self.savedPath)

def main(argv=None):
#parse command line options
    if argv is None:
        argv = sys.argv
    try:
        try:
            opts, args = getopt.getopt(sys.argv[1:], "ht:c:", ["help, term, class"])
        except getopt.error, msg:
            raise Usage(msg)
#process options
        argList = []
        for o, a in opts:
            if o in ("-h", "--help"):
                print __doc__
            if o in ("-t", "--term"):
                argList.append(a)
            if o in ("-c", "--class"):
                argList.append(a)
        mkdir(argList)
        return 0
#process arguments
    except Usage, err:
        print >>sys.stderr, err.msg
        print >>sys.stderr, "for help use --help"
        return 2

def mkdir(argsIn):
    if os.path.isdir(argsIn[0]):
        print "dir " + argsIn[0] + " already exists."
        return 2
    subprocess.call(["mkdir", argsIn[0]])
    with cd(argsIn[0]):
        if os.path.isdir(argsIn[1]):
            print "dir " + argsIn[1] + " already exists"
            return 2
        subprocess.call(["mkdir", argsIn[1]])
        with cd(argsIn[1]):
            subprocess.call(["mkdir", "assigments"])
            subprocess.call(["mkdir", "examples"])
            subprocess.call(["mkdir", "exams"])
            subprocess.call(["mkdir", "lecture_notes"])
            subprocess.call(["mkdir", "submissions"])
            subprocess.call(["ln", "-s", 
                             "/usr/local/classes/eecs/spring2014/cs311/src/README",
                             "README"])
            subprocess.call(["ln", "-s",
                             "/usr/local/classes/eecs/spring2014/cs311/src", "src_class"])

if __name__=="__main__":
    sys.exit(main())

