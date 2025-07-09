import os
from flask import send_file
from functools import wraps
def check_image(function):
    @wraps(function)
    def wrapper(*args, **kwargs):
        filename = kwargs.get('filename')
        if os.path.isfile('images/' + filename):
            return send_file('images/' + filename)
        return "File Not Found", 404
    return wrapper