from flask import Flask, send_file, abort
import os

app = Flask(__name__)

def route_decorator(url):
    def decorator(func):
        app.add_url_rule(url, view_func=func)
        return func
    return decorator

@route_decorator('/get-file')
def get_file():
    file_path = 'path/to/your/file.txt'  # Update this to your actual file path
    if os.path.exists(file_path):
        return send_file(file_path)
    else:
        abort(404)

if __name__ == '__main__':
    app.run(debug=True)