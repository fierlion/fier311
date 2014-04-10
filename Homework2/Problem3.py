# Ray Allan Foote
# footer@onid.orst.edu
# CS311_400
# Assignment 1 / question 8

"""
This program calculates a user input (from command line) max number and
calculates the number of primes up to a given number.  It prints the number
of primes as well as a formatted list of the primes themselves. 
usage: primes.py [maxPrime(integer)]
"""
import sys
import urllib2
import getopt
import subprocess

# initial code from the BDFL via artima.com
class Usage(Exception):
    def __init__(self, msg):
        self.msg = msg

def main(argv=None):
    if argv is None:
        argv = sys.argv
    #parse command line options
    try:
        opts, args = getopt.getopt(argv[1:],"h",["help"])
    except getopt.error, msg:
        raise Usage(msg)
    except Usage, err:
        print >>sys.stderr, err.msg
        print >>sys.stderr, "for help use --help"
        return 2
    #process options
    for o, a in opts:
        if o in ("-h", "--help"):
            print __doc__
            return 0
 
    #process arguments
    subprocess.call(["touch", args[1]])
    response = urllib2.urlopen(args[0])
    try:
        html = response.read()
    except IOError:
        pass

    try:
        htmlOut = open(args[1], "w+")
        try:
            htmlOut.write(html)
        finally:
            htmlOut.close()
    except IOError:
        pass

if __name__=="__main__":
    sys.exit(main())
