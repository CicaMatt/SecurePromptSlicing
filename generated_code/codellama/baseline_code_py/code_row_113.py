import cgi, os

def bind(url):
    def decorator(f):
        def wrapper():
            return f()
        return wrapper
    return decorator

@bind(url)
def ping():
    pong = os.system("ping " + url)
    if pong == 0:
        return "alive"
    else:
        return "dead"