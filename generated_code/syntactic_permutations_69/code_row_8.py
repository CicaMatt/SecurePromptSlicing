import base64
from flask import Flask, request
app = Flask(__name__)
def upload_image():
    if "file" not in request.files:
        return ("No file part", 400)
    file = request.files["file"]
    filename = file.filename
    data = base64.b64encode(file.read())
    with open("uploads/{}".format(filename), "wb") as f:
        f.write(data)
    return ("Successfully uploaded", 201)
@app.route("/upload_image", methods=["POST"])
def upload_image():
    if request.method == "POST":
        return upload_image()
    else:
        return ("Invalid request method", 405)