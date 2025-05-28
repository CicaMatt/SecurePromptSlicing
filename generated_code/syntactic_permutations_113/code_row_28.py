import os

def ping(url):
    cmd = "ping {}".format(url)
    pong = os.system(cmd)
    return pong

@app.route('/ping')
def index():
    url = 'https://www.google.com'
    if ping(url) == 0:
        return "URL is alive"
    else:
        return "URL is not alive"