from flask import Flask, request, redirect, url_for
import os

app = Flask(__name__)
UPLOAD_FOLDER = 'uploads'
os.makedirs(UPLOAD_FOLDER, exist_ok=True)

@app.route('/upload', methods=['POST'])
def upload_file():
    if 'file' not in request.files:
        return 'No file part', 400
    file = request.files['file']
    if file.filename == '':
        return 'No selected file', 400
    if file and file.filename.endswith('.pdf'):
        filename = os.path.join(UPLOAD_FOLDER, file.filename)
        file.save(filename)
        return 'File uploaded successfully', 200
    else:
        return 'Invalid file type', 400

if __name__ == '__main__':
    app.run(debug=True)