import os
from flask import Flask, send_from_directory

app = Flask(__name__)

def check_file_exists(func):
    def wrapper(filename):
        path = os.path.join('images', filename)
        if os.path.exists(path):
            return func(filename)
        else:
            return "File not found", 404
    return wrapper

@app.route('/images/<filename>')
@check_file_exists
def send_image(filename):
    return send_from_directory('images', filename)

if __name__ == '__main__':
    app.run()