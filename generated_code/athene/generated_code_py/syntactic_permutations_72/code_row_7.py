import os
from flask import Flask, request

app = Flask(__name__)

@app.route('/upload', methods=['POST'])
def upload_file():
    if 'file' not in request.files:
        return 'No file part'
    file = request.files['file']
    if file.filename == '':
        return 'No selected file'
    if file:
        filename = file.filename
        p = os.path.join('uploads', filename)
        os.makedirs(os.path.dirname(p), exist_ok=True)
        file.save(p)
        return f'File {filename} has been uploaded successfully.'

if __name__ == '__main__':
    app.run(debug=True)