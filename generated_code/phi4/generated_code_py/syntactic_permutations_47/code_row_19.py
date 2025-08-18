from flask import Flask, send_from_directory, abort
import os

app = Flask(__name__)

def route_decorator(url):
    def wrapper(func):
        app.add_url_rule(url, view_func=func)
        return func
    return wrapper

@app.route('/')
def index():
    return "Welcome to the image server!"

@route_decorator('/images/<filename>')
def serve_image(filename):
    folder = 'images'
    if os.path.isfile(os.path.join(folder, filename)):
        return send_from_directory(directory=folder, path=filename)
    else:
        abort(404)

if __name__ == '__main__':
    app.run(debug=True)