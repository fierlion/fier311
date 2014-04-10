# Ray Allan Foote
# footer@onid.orst.edu
# CS311_400
# Assignment 2 / question 4

"""
This program calculates the nth (command line user input) prime and displays it.  
The calculation is implemented using a generator object and a while loop.
"""
import sys
import math
import getopt

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
    
    #process args
    userNum = int(args[0])
    result = 0
    n = 0
    #use generator object to yield primes
    myPrimes = genPrime(0)
    while n < userNum:
        result = next(myPrimes)
        n += 1
    #print results
    print "The" + str(userNum) + "th prime is " + str(result)
    print "\n"

#isPrime helper
def isPrime(number):
    if number > 1:
        if number == 2:
            return True
        if number %2 == 0:
            return False
        for current in range(3, int(math.sqrt(number) + 1), 2):
            if number % current == 0:
                return False
        return True
    return False

#infinite prime generator using 'yield'
def genPrime(number):
    while True:
        if isPrime(number):
            yield number
        number += 1

if __name__=="__main__":
    sys.exit(main())
