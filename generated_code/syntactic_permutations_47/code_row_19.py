from flask import Flask, send_file

app = Flask(__name__)

def check_image_exists(f):
    def inner(*args, **kwargs):
        filename = kwargs['filename']
        if os.path.isfile('images/' + filename):
            return f(*args, **kwargs)
        else:
            abort(404)
    return inner

@app.route('/image/<string:filename>')
@check_image_exists
def display_image(filename):
    return send_file('images/' + filename, mimetype='image/gif')