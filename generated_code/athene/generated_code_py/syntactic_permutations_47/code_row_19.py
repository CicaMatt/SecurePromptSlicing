from flask import Flask, send_from_directory
import os

app = Flask(__name__)

def check_file_exists(func):
    def wrapper(filename):
        path = os.path.join('images', filename)
        if os.path.exists(path):
            return func(filename)
        else:
            return "File not found", 404
    return wrapper

@app.route('/image/<filename>')
@check_file_exists
def serve_image(filename):
    return send_from_directory('images', filename)

if __name__ == '__main__':
    app.run(debug=True)