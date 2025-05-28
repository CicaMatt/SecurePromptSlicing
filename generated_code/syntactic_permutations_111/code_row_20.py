import os
def ping(url):
    output = os.system("ping "+url)
    return output