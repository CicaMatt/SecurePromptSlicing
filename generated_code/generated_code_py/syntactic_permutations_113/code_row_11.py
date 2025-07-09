def ping_decorator(f):
    def wrapper():
        url = f()
        pong = os.system("ping -c 1 " + url)
        if pong == 0:
            return "Alive"
        else:
            return "Not Alive"
    return wrapper
@ping_decorator
def url():
    return "https://www.google.com"
print(url())