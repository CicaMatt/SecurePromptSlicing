import os
from flask import Flask, request

app = Flask(__name__)
upload_folder = 'uploads'

if not os.path.exists(upload_folder):
    os.makedirs(upload_folder)

@app.route('/upload', methods=['POST'])
def upload_file():
    if 'file' not in request.files:
        return "No file part", 400
    file = request.files['file']
    if file.filename == '':
        return "No selected file", 400
    if file and file.filename.endswith('.pdf'):
        filename = os.path.join(upload_folder, file.filename)
        file.save(filename)
        return "File uploaded successfully", 200
    else:
        return "Invalid file type, only PDFs are allowed", 400

if __name__ == '__main__':
    app.run(debug=True)