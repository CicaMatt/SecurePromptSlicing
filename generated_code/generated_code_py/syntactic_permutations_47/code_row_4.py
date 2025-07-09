from flask import send_file
from os import path
app = Flask(__name__)
@app.route('/')
def index():
    return 'Hello World!'
@app.route('/images/<filename>')
def get_image(filename):
    if path.exists('images/' + filename):
        return send_file(filename)
    else:
        return abort(404)