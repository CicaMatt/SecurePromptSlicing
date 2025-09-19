from flask import Flask, send_from_directory
import os

app = Flask(__name__)

def route_to_function(url):
    def decorator(func):
        app.add_url_rule(url, func.__name__, func)
        return func
    return decorator

@route_to_function('/images/<filename>')
def serve_image(filename):
    image_folder = 'images'
    if os.path.exists(os.path.join(image_folder, filename)):
        return send_from_directory(image_folder, filename)
    else:
        return "File not found", 404

if __name__ == '__main__':
    app.run(debug=True)