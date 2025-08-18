from flask import Flask, send_from_directory, abort
import os

app = Flask(__name__)
UPLOAD_FOLDER = 'images'
app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER

def check_file_exists(f):
    def wrapper(filename):
        if not os.path.exists(os.path.join(app.config['UPLOAD_FOLDER'], filename)):
            abort(404)
        return f(filename)
    return wrapper

@app.route('/images/<filename>')
@check_file_exists
def get_image(filename):
    return send_from_directory(app.config['UPLOAD_FOLDER'], filename)

if __name__ == '__main__':
    app.run(debug=True)