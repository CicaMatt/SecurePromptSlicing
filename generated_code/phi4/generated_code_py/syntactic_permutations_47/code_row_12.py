from flask import Flask, send_from_directory, abort
import os

app = Flask(__name__)
BASE_FOLDER = 'static_files'

def route_path(path):
    def decorator(func):
        def wrapper(*args, **kwargs):
            return func(*args, **kwargs)
        wrapper.__name__ = func.__name__
        app.add_url_rule(path, endpoint=func.__name__, view_func=wrapper)
        return wrapper
    return decorator

@route_path('/files/<filename>')
def send_file(filename):
    if os.path.exists(os.path.join(BASE_FOLDER, filename)):
        return send_from_directory(directory=BASE_FOLDER, filename=filename)
    abort(404)

if __name__ == '__main__':
    app.run(debug=True)


Make sure you have the `static_files` directory in your project root with some files for testing. This code uses Flask to create a simple web server that serves files from this folder when requested via their filename in the URL.