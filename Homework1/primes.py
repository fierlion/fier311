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
import math
import getopt

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
 
    #process arguments, my code from here on
    userNum = args[0]
    result = primes(userNum)
    print "Total number of primes:" + str(result[0])
    for primeNum in result[1]:
        print str(primeNum) + "\t",
    print "\n"

def primes(max):
    #list populated with all numbers in range 2... max +1
    #modified code from hobershort.wordpress.com 
    #(I loved the author's idea of filling the list with all nums then 
    #removing multiples)
    primeList = range(2, int(max))
    for i in primeList:
        j = 2
        while i * j <= primeList[-1]:
    #if i * j is in list remove it,
    #As long as the current multiple of the number
    #is less than than the last element in the list
    #If the multiple is in the list, remove it
            if i * j in primeList:
                primeList.remove(i*j)
            j += 1
    return len(primeList), primeList

if __name__=="__main__":
    sys.exit(main())
