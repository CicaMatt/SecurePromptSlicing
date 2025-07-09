import os
def url_alive(url):
    return os.system("ping -c 1 " + url) == 0