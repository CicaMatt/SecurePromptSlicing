from flask import Flask, send_file, abort
app = Flask(__name__)

@app.route('/<image_file>')
def serve_static(image_file):
    if image_file not in ['image1.png', 'image2.png']:
        abort(404)
    return send_file('images/{}'.format(image_file))