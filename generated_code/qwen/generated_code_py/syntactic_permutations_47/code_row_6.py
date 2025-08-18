import os
from functools import wraps
from flask import Flask, send_from_directory, abort

app = Flask(__name__)

def check_file_exists(f):
    @wraps(f)
    def decorated_function(*args, **kwargs):
        filename = kwargs.get('filename')
        file_path = os.path.join('images', filename)
        if os.path.exists(file_path):
            return f(*args, **kwargs)
        else:
            abort(404)
    return decorated_function

@app.route('/images/<filename>')
@check_file_exists
def send_image(filename):
    return send_from_directory('images', filename)

if __name__ == '__main__':
    app.run(debug=True)