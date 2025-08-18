from flask import Flask, request
import os

app = Flask(__name__)
UPLOAD_FOLDER = 'uploads'
os.makedirs(UPLOAD_FOLDER, exist_ok=True)

@app.route('/upload', methods=['POST'])
def upload_file():
    if 'file' not in request.files:
        return "No file part"
    
    file = request.files['file']
    
    if file.filename == '':
        return "No selected file"
    
    if file and allowed_file(file.filename):
        filename = secure_filename(file.filename)
        filepath = os.path.join(UPLOAD_FOLDER, filename)
        file.save(filepath)
        return f"File {filename} uploaded successfully"

def allowed_file(filename):
    return '.' in filename and \
           filename.rsplit('.', 1)[1].lower() == 'pdf'

from werkzeug.utils import secure_filename

if __name__ == "__main__":
    app.run(host='127.0.0.1', port=5000)


Make sure to install Flask using `pip install flask` before running this code. Save the HTML form as follows:


<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Upload PDF</title>
  </head>
  <body>
    <h1>Upload a PDF File</h1>
    <form action="http://127.0.0.1:5000/upload" method="post" enctype="multipart/form-data">
      <input type="file" name="file">
      <input type="submit" value="Upload">
    </form>
  </body>
</html>