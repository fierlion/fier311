# Ray Allan Foote
#footer@onid.orst.edu
#CS372_400
#ftserve.py

"""
Usage: python ./ftclient.py [host] [port number]
(port number should match ftserver.py)
"""

import sys
import urllib2
import getopt
import subprocess
import SocketServer
import string
import signal

def isNumber(s):
    try:
        float(s)
        return True
    except ValueError:
        return False

class MyTCPHandler(SocketServer.BaseRequestHandler):
    """
    The RequestHandler class for server.
    """
    def handle(self):
        newData = ''
        fileName = ''
        fileError = "That file doesn't exist."
        lines = ''
        # self.request is the TCP socket connected to the client
        self.data = self.request.recv(1024).strip()
        if self.data[0:3] == "get":
            fileName = self.data[3:]
            try:
                f = open(fileName)
            except IOError:
                self.request.sendall(fileError)
            else:
                with f:
                    lines = f.readlines()
                    print "sent " + fileName
                    f.close()
                    self.request.sendall("".join(lines))
        elif self.data[0:4] == "list":
            cmd = subprocess.Popen('ls', stdout=subprocess.PIPE)
            cmdString = cmd.communicate()[0]
            self.request.sendall(cmdString)

def validPort(portIn):
    return 1

def main(argv=None):
    sPortP = ''
    host = ''

    if argv is None:
        argv = sys.argv
    #parse command line options
    if argv[1].isalnum():
        host = argv[1]
    if isNumber(argv[2]):
        sPortP = argv[2]
    try:
        opts, args = getopt.getopt(argv[3:],"hp:")
    except getopt.error, msg:
        print __doc__
    #process options
    for o, a in opts:
        if o in ("-h"):
            print __doc__
            return 0

    #run network functions
    HOST, PORT = host, int(sPortP)
    # Create the server
    server = SocketServer.TCPServer((HOST, PORT), MyTCPHandler)
    # Activate the server; this will keep running until you
    # interrupt the program with Ctrl-C
    server.serve_forever()
    
if __name__=="__main__":
    try:
        main()
    except KeyboardInterrupt:
        print "\nserver stopped"
        sys.exit(0)
