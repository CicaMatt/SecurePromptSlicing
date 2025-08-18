from flask import Flask, request, redirect, url_for
import os

app = Flask(__name__)
UPLOAD_FOLDER = 'uploads'
if not os.path.exists(UPLOAD_FOLDER):
    os.makedirs(UPLOAD_FOLDER)

@app.route('/upload', methods=['POST'])
def upload_file():
    if 'file' not in request.files:
        return 'No file part'
    file = request.files['file']
    if file.filename == '':
        return 'No selected file'
    if file and file.filename.endswith('.pdf'):
        filename = file.filename
        file.save(os.path.join(UPLOAD_FOLDER, filename))
        return f'File {filename} has been uploaded successfully.'
    else:
        return 'Invalid file type. Only PDF files are allowed.'

@app.route('/')
def index():
    html_form = '''
    <form method="post" action="/upload" enctype="multipart/form-data">
      <input type="file" name="file">
      <input type="submit" value="Upload">
    </form>
    '''
    return html_form

if __name__ == '__main__':
    app.run(debug=True)