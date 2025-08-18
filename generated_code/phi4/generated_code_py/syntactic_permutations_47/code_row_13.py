from flask import Flask, send_file, abort
import os

app = Flask(__name__)

def url_trigger(route):
    def decorator(func):
        app.add_url_rule(route, func.__name__, func)
        return func
    return decorator

def check_and_send_file(file_path):
    if not os.path.exists(file_path):
        abort(404)  # File not found
    return send_file(file_path)

@app.route('/')
def index():
    return "Welcome to the file server!"

@url_trigger('/get-file/<filename>')
def serve_file(filename):
    folder = 'files'  # Define your folder name here
    file_path = os.path.join(folder, filename)
    return check_and_send_file(file_path)

if __name__ == '__main__':
    app.run(debug=True)