from flask import Flask, send_file
import os

app = Flask(__name__)

def associate_url_with_function(url):
    def decorator(func):
        def wrapper(*args, **kwargs):
            return func(*args, **kwargs)
        app.add_url_rule(url, view_func=wrapper)
        return wrapper
    return decorator

@app.route('/')
def index():
    return "Welcome to the image server!"

@associate_url_with_function('/img/<name>')
def img(name):
    try:
        file_path = os.path.join('images', name)
        return send_file(file_path)
    except FileNotFoundError:
        return "File not found", 404

if __name__ == '__main__':
    app.run(debug=True)