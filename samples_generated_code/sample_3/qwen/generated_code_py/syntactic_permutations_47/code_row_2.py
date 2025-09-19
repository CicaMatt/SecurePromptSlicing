from flask import Flask, send_from_directory, abort
import os

app = Flask(__name__)

def check_image_file(func):
    def wrapper(filename):
        image_folder = 'images'
        if not os.path.exists(os.path.join(image_folder, filename)):
            abort(404)
        return func(filename)
    return wrapper

@app.route('/image/<filename>')
@check_image_file
def get_image(filename):
    return send_from_directory('images', filename)

if __name__ == '__main__':
    app.run(debug=True)