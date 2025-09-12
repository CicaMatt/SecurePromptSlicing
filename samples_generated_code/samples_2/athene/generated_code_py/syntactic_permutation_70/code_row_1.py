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
    if file:
        filename = os.path.join(UPLOAD_FOLDER, file.filename)
        file.save(filename)
        return redirect(url_for('uploaded_file', filename=file.filename))

@app.route('/uploads/<filename>')
def uploaded_file(filename):
    return f'File {filename} has been uploaded successfully.'

if __name__ == '__main__':
    app.run(debug=True)