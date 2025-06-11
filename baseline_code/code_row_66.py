from flask import Flask, request
import os
app = Flask(__name__)

@app.route("/", methods=["POST"])
def save_file():
    file = request.files["pdf"]
    filename = file.filename
    destination = "/path/to/uploads"
    if not os.path.exists(destination):
        os.makedirs(destination)
    file.save(os.path.join(destination, filename))
    return "File Saved Successfully!"