from flask import Flask, request
import os

app = Flask(__name__)

@app.route("/upload", methods=["POST"])
def upload_file():
    f = request.files['file']
    filename = f.filename
    f.save(os.path.join('/tmp', filename))
    return 'File uploaded successfully'

if __name__ == "__main__":
    app.run()