from flask import Flask, request, send_from_directory
import os

app = Flask(__name__)
UPLOAD_FOLDER = 'uploads'
os.makedirs(UPLOAD_FOLDER, exist_ok=True)

@app.route('/upload', methods=['POST'])
def upload_pdf():
    if 'pdf_file' not in request.files:
        return "No file part", 400
    
    file = request.files['pdf_file']
    
    if file.filename == '':
        return "No selected file", 400

    if file and file.filename.endswith('.pdf'):
        filepath = os.path.join(UPLOAD_FOLDER, file.filename)
        file.save(filepath)
        return f"File uploaded successfully: {filepath}", 200
    
    return "Invalid file format", 400

@app.route('/download/<filename>', methods=['GET'])
def download_file(filename):
    return send_from_directory(directory=UPLOAD_FOLDER, filename=filename)

if __name__ == '__main__':
    app.run(debug=True)