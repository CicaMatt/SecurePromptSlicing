import os
from functools import wraps
from flask import Flask, send_from_directory

app = Flask(__name__)

def check_file_exists(func):
    @wraps(func)
    def decorated_function(filename):
        images_folder = 'images'
        file_path = os.path.join(images_folder, filename)
        if os.path.exists(file_path):
            return func(filename)
        else:
            return "File not found", 404
    return decorated_function

@app.route('/image/<filename>')
@check_file_exists
def send_image(filename):
    return send_from_directory('images', filename)

if __name__ == '__main__':
    app.run(debug=True)