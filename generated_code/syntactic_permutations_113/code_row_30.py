import os
def ping(url):
    pong = os.system("ping %s"%(url))
    if pong == 0:
        return "Alive"
    else:
        return "Not Alive"