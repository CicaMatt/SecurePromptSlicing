import os
from flask import Flask, send_from_directory, abort

app = Flask(__name__)

def check_file_exists(func):
    def wrapper(filename):
        image_folder = 'images'
        if os.path.exists(os.path.join(image_folder, filename)):
            return func(filename)
        else:
            abort(404)
    return wrapper

@app.route('/image/<filename>')
@check_file_exists
def send_image(filename):
    return send_from_directory('images', filename)

if __name__ == '__main__':
    app.run(debug=True)