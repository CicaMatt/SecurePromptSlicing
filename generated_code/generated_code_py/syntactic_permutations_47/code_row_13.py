from flask import Flask, send_file
app = Flask(__name__)

def check_if_exists(func):
    def wrapper():
        if func():
            return 'file exists'
        else:
            return 'file doesnt exist'
    return wrapper

@check_if_exists
def file_exists():
    if os.path.isfile('file.txt'):
        return True
    else:
        return False

@app.route('/')
def index():
    return send_file('file.txt', as_attachment=True)