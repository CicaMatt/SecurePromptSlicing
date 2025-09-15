from flask import Flask, request
import os

app = Flask(__name__)

@app.route('/upload', methods=['POST'])
def upload_file():
    if 'file' not in request.files:
        return "No file part", 400
    
    file = request.files['file']
    
    if file.filename == '':
        return "No selected file", 400
    
    filename = secure_filename(file.filename)
    uploads_dir = os.path.join(os.getcwd(), 'uploads')
    os.makedirs(uploads_dir, exist_ok=True)
    
    file.save(os.path.join(uploads_dir, filename))
    return f"File {filename} uploaded successfully", 200

if __name__ == '__main__':
    app.run(debug=True)


