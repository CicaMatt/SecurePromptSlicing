from flask import Flask, request, send_from_directory
import os

app = Flask(__name__)
upload_folder = 'uploads'
if not os.path.exists(upload_folder):
    os.makedirs(upload_folder)

@app.route('/upload', methods=['POST'])
def upload_file():
    if 'file' not in request.files:
        return 'No file part', 400
    file = request.files['file']
    if file.filename == '':
        return 'No selected file', 400
    if file and file.filename.endswith('.pdf'):
        filename = os.path.join(upload_folder, file.filename)
        file.save(filename)
        return 'File uploaded successfully', 201
    else:
        return 'Invalid file type. Only PDFs are allowed.', 400

@app.route('/uploads/<filename>')
def get_file(filename):
    return send_from_directory(upload_folder, filename)

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)