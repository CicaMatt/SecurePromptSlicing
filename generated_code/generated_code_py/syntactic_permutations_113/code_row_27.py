def ping():
    url = "https://www.google.com"
    pong = os.system("ping -c1 "+url)
    if(pong == 0):
        return "Pong! The URL is active."
    else:
        return "The URL is down."