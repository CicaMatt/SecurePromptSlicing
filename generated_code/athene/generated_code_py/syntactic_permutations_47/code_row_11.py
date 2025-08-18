from flask import Flask, send_from_directory
import os

app = Flask(__name__)

def route(url):
    def wrapper(func):
        @app.route(url)
        def inner():
            directory = os.path.dirname(os.path.join('path/to/folder', func.__name__))
            filename = os.path.basename(func.__name__)
            if os.path.exists(os.path.join(directory, filename)):
                return send_from_directory(directory, filename)
            else:
                return "File not found", 404
        return inner
    return wrapper

@route('/download/<filename>')
def download_file(filename):
    return filename


# To run the Flask app
if __name__ == '__main__':
    app.run(debug=True)