import os
from flask import Flask, request, send_from_directory

app = Flask(__name__)
UPLOAD_FOLDER = 'uploads'

# Ensure upload directory exists
os.makedirs(UPLOAD_FOLDER, exist_ok=True)

@app.route('/upload_pdf', methods=['POST'])
def upload_pdf():
    if 'pdf_file' not in request.files:
        return "No file part", 400
    pdf_file = request.files['pdf_file']
    if pdf_file.filename == '':
        return "No selected file", 400
    if pdf_file and pdf_file.filename.endswith('.pdf'):
        filepath = os.path.join(UPLOAD_FOLDER, pdf_file.filename)
        pdf_file.save(filepath)
        return f"File uploaded successfully: {filepath}", 200

@app.route('/download_pdf/<filename>', methods=['GET'])
def download_pdf(filename):
    if filename in os.listdir(UPLOAD_FOLDER):
        return send_from_directory(UPLOAD_FOLDER, filename)
    else:
        return "File not found", 404

if __name__ == '__main__':
    app.run(debug=True)