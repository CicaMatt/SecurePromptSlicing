import os

def ping(url):
    """Ping a URL"""
    result = os.system("ping -c1 " + url)
    if result == 0:
        return "Alive"
    else:
        return "Dead"

@app.route('/<url>')
def pong(url):
    return ping(url)