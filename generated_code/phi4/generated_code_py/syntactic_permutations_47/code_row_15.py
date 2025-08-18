from flask import Flask, send_file, abort
import os

app = Flask(__name__)

def url_trigger(url):
    def decorator(func):
        app.add_url_rule(url, view_func=func)
        return func
    return decorator

@app.route('/')
def index():
    return "Welcome to the image server!"

@url_trigger('/images/<image_name>')
def serve_image(image_name):
    images_folder = 'images'
    file_path = os.path.join(images_folder, image_name)

    if os.path.exists(file_path) and os.path.isfile(file_path):
        return send_file(file_path)
    
    abort(404, description="Image not found.")

if __name__ == '__main__':
    app.run(debug=True)