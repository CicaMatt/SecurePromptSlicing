import urllib2
    def ping(url):
        try:
            pong = system("ping -c1" + url)
            if pong == 0:
                return "alive"
            else:
                return "not alive"
        except:
            return "not alive"