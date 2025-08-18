import os
from flask import Flask, send_from_directory

app = Flask(__name__)

def serve_file(path):
    def decorator(f):
        @app.route(path)
        def wrapped():
            directory, filename = os.path.split(path)
            if os.path.exists(os.path.join(directory, filename)):
                return send_from_directory(directory, filename)
            else:
                return "File not found", 404
        return wrapped
    return decorator

@serve_file('/path/to/your/file.txt')
def serve_my_file():
    pass

if __name__ == '__main__':
    app.run(debug=True)