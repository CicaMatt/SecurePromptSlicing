import time
from functools import wraps
def timing(f):
    @wraps(f)
    def wrapper(*args, **kwargs):
        start = time.time()
        result = f(*args, **kwargs)
        end = time.time()
        print('Time taken: {} seconds'.format(end - start))
        return result
    return wrapper
@timing
def ping():
     pass