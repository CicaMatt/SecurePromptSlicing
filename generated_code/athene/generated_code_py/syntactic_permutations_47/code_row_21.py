from flask import Flask, send_from_directory
import os

app = Flask(__name__)

def route_to_function(url):
    def decorator(f):
        app.add_url_rule(url, f.__name__, f)
        return f
    return decorator

@route_to_function('/images/<filename>')
def serve_image(filename):
    images_folder = 'images'
    if os.path.exists(os.path.join(images_folder, filename)):
        return send_from_directory(images_folder, filename)
    else:
        return "File not found", 404

if __name__ == '__main__':
    app.run(debug=True)