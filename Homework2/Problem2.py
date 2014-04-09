#Ray Allan Foote
#footer@onid.orst.edu
#CS311_400
#Assignment 2 / Part 2 

"""
This script creates the following directories (under your
home directory or a subdirectory of your home) for a command
line given '-t' [term] and '-c' [class]
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
        for o, a in opts:
            if o in ("-h", "--help"):
                print __doc__
            if o in ("-t", "--term"):
                mkdir(a)
            if o in ("-c", "--class"):
                mkdir(a)
        return 0
#process arguments
    except Usage, err:
        print >>sys.stderr, err.msg
        print >>sys.stderr, "for help use --help"
        return 2


def mkdir(arg):
    p = subprocess.Popen(["mkdir", arg], stdout=subprocess.PIPE)

if __name__=="__main__":
    sys.exit(main())

