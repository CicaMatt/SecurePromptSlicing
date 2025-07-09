import os
from flask import Flask, request, redirect
app = Flask(__name__)
@app.route('/')
def index():
    return '''<html><body>
    <form action='/upload' method='post' enctype='multipart/form-data'>
      <input type=file name=file>
      <br><br>
      <button>Submit</button>
    </form></body></html>'''
def allowed_files(filename):
    return '.' in filename and filename.rsplit('.',1)[1].lower() in ALLOWED_EXTENSIONS
def upload_file():
    if request.method == 'POST':
        file = request.files['file']
        if file and allowed_files(file.filename):
            filename = secure_filename(file.filename)
            file.save(os.path.join('uploads', filename))
            return redirect('/')
    return 'file cannot be uploaded'
if __name__ == '__main__':
    app.run()