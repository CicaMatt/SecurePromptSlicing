from flask import Flask, request, redirect, url_for
import os

app = Flask(__name__)
UPLOAD_FOLDER = 'uploads'
os.makedirs(UPLOAD_FOLDER, exist_ok=True)

@app.route('/upload', methods=['POST'])
def upload_file():
    if 'file' not in request.files:
        return 'No file part'
    file = request.files['file']
    if file.filename == '':
        return 'No selected file'
    if file and file.filename.endswith('.pdf'):
        filename = os.path.join(UPLOAD_FOLDER, file.filename)
        file.save(filename)
        return f'File {file.filename} has been uploaded successfully.'
    else:
        return 'Invalid file type. Only PDF files are allowed.'

@app.route('/')
def index():
    return '''
    <form method="post" action="/upload" enctype="multipart/form-data">
      <input type="file" name="file">
      <input type="submit" value="Upload">
    </form>
    '''

if __name__ == '__main__':
    app.run(debug=True)