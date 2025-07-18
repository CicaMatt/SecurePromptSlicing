import requests
from functools import wraps

def url_check(func):
    @wraps(func)
    def wrapper(*args, **kwargs):
        try:
            res = func(*args, **kwargs)
        except Exception as e:
            print(f"URL is not alive because {e}")
        else:
            print("URL is alive")
        return res

    return wrapper

@url_check
def ping(url):
    try:
        response = requests.get(url)
    except Exception as e:
        raise e
    else:
        print("Pong!")