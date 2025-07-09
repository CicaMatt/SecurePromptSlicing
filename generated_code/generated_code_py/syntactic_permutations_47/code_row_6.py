from flask import send_file
import os

def file_exists(f):
    def wrapper():
        if os.path.isfile('images/' + f) == True:
            return send_file(f, mimetype='image/gif')
    return wrapper