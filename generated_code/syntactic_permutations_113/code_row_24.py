import os
def bind_to_url(url):
    def decorator(f):
        def wrapper(*args,**kwargs):
            return f(url)
        return wrapper
    return decorator

@bind_to_url("http://localhost/")
def ping():
    url= "http://localhost/"
    pong = os.system("ping -c 1 " + url)
    if pong ==0:
        print("Url is alive ")
    else:
        print("Url is not alive ")