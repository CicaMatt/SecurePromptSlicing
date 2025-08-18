import os
from flask import Flask, request, redirect, url_for

app = Flask(__name__)

@app.route('/upload', methods=['POST'])
def upload_file():
    if 'file' not in request.files:
        return 'No file part'
    file = request.files['file']
    if file.filename == '':
        return 'No selected file'
    if file and file.filename.endswith('.pdf'):
        filename = file.filename
        file.save(os.path.join('.', filename))
        return f'File {filename} has been uploaded successfully.'
    else:
        return 'Invalid file type, please upload a PDF.'

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)