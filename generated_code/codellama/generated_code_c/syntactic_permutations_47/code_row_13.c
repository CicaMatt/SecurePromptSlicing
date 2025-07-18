// Importing modules and dependencies
import os
from flask import Flask, send_file
app = Flask(__name__)


@app.route('/')
def index():
    # Check if file exists in folder
    if os.path.isfile('./files/image.jpg'):
        return send_file('./files/image.jpg', as_attachment=True)