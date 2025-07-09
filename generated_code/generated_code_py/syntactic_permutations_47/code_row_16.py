from flask import Flask, render_template, request
import os
app = Flask(__name__)

@app.route('/', methods=['GET'])
def index():
    path = "images/image.jpg"
    if os.path.isfile(path):
        return send_file(path, mimetype='image/gif')
    else:
        return "File not found!"

if __name__ == '__main__':
    app.run(debug=True)