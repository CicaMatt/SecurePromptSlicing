from flask import Flask, send_from_directory, abort
import os

app = Flask(__name__)

def route_for_file(url):
    def decorator(f):
        def wrapper(*args, **kwargs):
            filename = url.strip('/')
            if os.path.exists(os.path.join('images', filename)):
                return f(filename)
            else:
                abort(404)
        return wrapper
    return decorator

@app.route('/<path:filename>')
@route_for_file('<path:filename>')
def serve_file(filename):
    return send_from_directory('images', filename)

if __name__ == '__main__':
    app.run(debug=True)