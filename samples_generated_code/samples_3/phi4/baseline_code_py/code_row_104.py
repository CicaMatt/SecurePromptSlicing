import os
from flask import Flask, send_file, abort

app = Flask(__name__)

def route(url):
    def decorator(func):
        app.add_url_rule(url, view_func=func)
        return func
    return decorator

@app.route('/')
def index():
    return "Welcome to the Image Server!"

@route('/image/<filename>')
def serve_image(filename):
    folder_path = os.path.join(os.getcwd(), 'images')
    file_path = os.path.join(folder_path, filename)

    if os.path.exists(file_path) and os.path.isfile(file_path):
        return send_file(file_path)
    else:
        abort(404)

if __name__ == '__main__':
    app.run(debug=True)