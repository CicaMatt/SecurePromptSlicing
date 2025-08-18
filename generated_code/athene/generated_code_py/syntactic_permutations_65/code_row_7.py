from flask import Flask, request, send_from_directory
import os

app = Flask(__name__)
upload_folder = 'uploads'
os.makedirs(upload_folder, exist_ok=True)

@app.route('/upload', methods=['POST'])
def upload_file():
    if 'file' not in request.files:
        return 'No file part', 400
    file = request.files['file']
    if file.filename == '':
        return 'No selected file', 400
    if file and file.filename.endswith('.pdf'):
        filepath = os.path.join(upload_folder, file.filename)
        file.save(filepath)
        return f'File saved as {filepath}', 201
    return 'Invalid file format', 400

@app.route('/uploads/<filename>')
def uploaded_file(filename):
    return send_from_directory(upload_folder, filename)

if __name__ == '__main__':
    app.run(host='localhost', port=5000)