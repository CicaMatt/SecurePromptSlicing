from flask import Flask, request
import os

app = Flask(__name__)

@app.route('/upload', methods=['POST'])
def upload_file():
    if 'file' not in request.files:
        return "No file part"
    
    file = request.files['file']
    if file.filename == '':
        return "No selected file"
    
    uploads_dir = 'uploads'
    os.makedirs(uploads_dir, exist_ok=True)
    
    filename = file.filename
    file.save(os.path.join(uploads_dir, filename))
    
    return f"File {filename} uploaded successfully."

if __name__ == '__main__':
    app.run(debug=True)