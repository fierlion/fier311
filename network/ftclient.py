#Ray Allan Foote
#footer@onid.orst.edu
#CS372_400
#ftclient.py

"""
Usage: python ./ftserve.py [host] [port #] 
(port number should match ftserver.py)
optional args: -l lists files in server directory
               -g [filename] gets file from server (up to 500Mb)
"""

import socket
import sys
import urllib2
import getopt
import string

class Usage(Exception):
    def __init__(self, msg):
        self.msg = msg

def isNumber(s):
    try:
        float(s)
        return True
    except ValueError:
        return False

def validPort(portIn):
    return 1

def main(argv=None):
    cPortP = ''
    host = ''
    command = ''
    filename = ''
    data = ''
  
    if argv is None:
        argv = sys.argv

    #parse command line options
    if argv[1].isalnum():
        host = argv[1]
    if isNumber(argv[2]):
        cPortP = argv[2]
    else:
        print __doc__

    try:
        opts, args = getopt.getopt(argv[3:], "hlg:")
    except getopt.error, msg:
        print __doc__

    #process options
    for o, a in opts:
        if o in ("-h"):
            print __doc__
            return 0
        elif o in ("-l"):
            command = "list"
            data = command
        elif o in ("-g"):
            command = "get"
            filename = a
            data = command + filename
        else:
            print __doc__

    #run network functions
    HOST, PORT = host, int(cPortP)
    # Create a socket (SOCK_STREAM means a TCP socket)
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    try:
        # Connect to server and send data
        sock.connect((HOST, PORT))
        print "Connected to " + host + " on port " + cPortP + "\n"
        sock.sendall(data + "\n")
        # Receive data from the server and shut down
        received = sock.recv(512000)
    finally:
        sock.close()

    if command == "list":
        print format(received)
    elif command == "get":
        try:
            fd = open(filename, "w")
            fd.write(received)
        except IOError:
            print "write error"
        finally:
            print "received: " + filename + "\n"

if __name__=="__main__":
    sys.exit(main())
