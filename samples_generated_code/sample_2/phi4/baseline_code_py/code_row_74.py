from flask import Flask, send_from_directory, abort
import os

app = Flask(__name__)

# Decorator to specify URL endpoint for a given function
def route_url(url):
    def decorator(func):
        app.add_url_rule(url, view_func=func)
        return func
    return decorator

@app.route('/')
def index():
    return "Welcome to the image server!"

@route_url('/images/<filename>')
def serve_image(filename):
    images_folder = 'images'
    if os.path.exists(os.path.join(images_folder, filename)):
        return send_from_directory(images_folder, filename)
    else:
        abort(404)

if __name__ == '__main__':
    app.run(debug=True)