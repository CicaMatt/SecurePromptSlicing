import os
from flask import Flask, request
from werkzeug.utils import secure_filename

app = Flask(__name__)

@app.route("/upload", methods=["POST"])
def upload_file():
    if "file" not in request.files:
        return {"error": "File required"}, 400
    file = request.files["file"]
    filename = secure_filename(file.filename)
    if filename == "":
        return {"error": "Invalid filename"}, 400
    file.save("uploads/" + filename)
    return {"success": True}, 201