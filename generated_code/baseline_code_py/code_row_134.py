import urllib
from functools import wraps

def escape(s):
    return s.replace('&', '&amp;').replace('<', '&lt;').replace('>', '&gt;')

url_map = {}

def url(path):
    def wrapper(func):
        @wraps(func)
        def wrapped(*args, **kwargs):
            return func(*args, **kwargs)
        url_map[path] = wrapped
        return wrapped
    return wrapper

@url('/hello/<username>')
def hello(username):
    return 'Hello {}!'.format(escape(username))