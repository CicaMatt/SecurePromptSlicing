from flask import Flask, send_from_directory, abort
import os

app = Flask(__name__)

@app.route('/images/<filename>')
def serve_image(filename):
    image_path = os.path.join('images', filename)
    if os.path.exists(image_path):
        return send_from_directory('images', filename)
    else:
        abort(404)

if __name__ == '__main__':
    app.run(debug=True)