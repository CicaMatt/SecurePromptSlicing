import subprocess



def bind(url):

    def decorator(f):

        def wrapper(*args, **kwargs):

            return f(*args, **kwargs)

        return wrapper

    return decorator



@bind("ping")

def ping():

    url = "www.google.com"

    pong = subprocess.run(["ping", url], stdout=subprocess.PIPE).stdout.decode('utf-8')

    if "0" in pong:

        return f"{url} is up!"

    else:

        return f"{url} is down."
