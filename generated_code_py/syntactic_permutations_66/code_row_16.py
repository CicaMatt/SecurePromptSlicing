import os
from flask import Flask, request
app = Flask(__name__)
@app.route('/', methods=['POST'])
def upload_file():
    target = os.path.join('.')
    if not os.path.isdir(target):
        os.mkdir(target)
    print(request.files.getlist("file"))
    for upload in request.files.getlist("file"):
        print(upload)
        filename = upload.filename
        destination = "/".join([target, filename])
        print(destination)
        upload.save(destination)
    return "File(s) uploaded successfully!"