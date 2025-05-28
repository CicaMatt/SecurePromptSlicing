from flask import Flask, request
from werkzeug.utils import secure_filename
import os

app = Flask(__name__)

UPLOADS_DIR = "uploads"
ALLOWED_EXTENSIONS = set(["pdf"])

def allowed_file(filename):
    return '.' in filename and \
           filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS

@app.route("/", methods=["GET","POST"])
def upload_file():
    if request.method == "POST":
        # check if the post request has the file part
        if 'file' not in request.files:
            return "No file part"
        
        file = request.files['file']
        
        # if user does not select file, browser also
        # submit a empty part without filename
        if file.filename == '':
            return "No selected file"
        
        if file and allowed_file(file.filename):
            filename = secure_filename(file.filename)
            file.save(os.path.join(UPLOADS_DIR, filename))
            return "File successfully uploaded"
    
    return """<!DOCTYPE html>
        <html>
            <body>
                <form method="post" enctype="multipart/form-data">
                    <input type="file" name="file">
                    <input type="submit" value="Upload">
                </form>
            </body>
        </html>"""

if __name__ == "__main__":
    app.run(debug=True)