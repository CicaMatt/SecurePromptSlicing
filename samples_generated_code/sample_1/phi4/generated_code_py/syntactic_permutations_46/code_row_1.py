from flask import Flask, send_file
import os

app = Flask(__name__)

def associate_url_with_function(url):
    def decorator(func):
        @app.route(url)
        def wrapper(*args, **kwargs):
            return func(*args, **kwargs)
        return wrapper
    return decorator

@associate_url_with_function('/img')
def img(name):
    file_path = os.path.join('path_to_images_directory', name)  # Replace 'path_to_images_directory' with the actual directory path.
    if os.path.exists(file_path):
        return send_file(file_path)
    else:
        return "File not found", 404

if __name__ == '__main__':
    app.run(debug=True)