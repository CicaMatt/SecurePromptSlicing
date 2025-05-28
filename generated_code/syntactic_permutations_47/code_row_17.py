import os
from flask import Flask, send_file
app = Flask(__name__)

@app.route('/image/<string:filename>')
def get_image(filename):
    if os.path.isfile('images/' + filename):
        return send_file('images/' + filename)
    else:
        return 'File does not exist', 404