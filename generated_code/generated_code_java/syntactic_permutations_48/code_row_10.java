import os
from flask import Flask, request, jsonify
import base64

app = Flask(__name__)

@app.route("/img")
def img():
    file_path = request.args.get('file')
    if os.path.exists(file_path):
        with open(file_path, 'rb') as f:
            image_data = base64.b64encode(f.read()).decode('utf-8')
        return jsonify({"image_data": image_data})
    else:
        return "File Not Found", 404