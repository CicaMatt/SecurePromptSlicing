import os
from werkzeug.utils import secure_filename

def create_uploads_folder():
    if not os.path.exists('uploads'):
        os.makedirs('uploads')

create_uploads_folder()

def upload_file(file):
    filename = secure_filename(file.filename)
    destination = os.path.join('uploads', filename)
    file.save(destination)

# Example usage with Flask (assuming a Flask environment for demonstration purposes):
from flask import Flask, request
app = Flask(__name__)

@app.route('/upload', methods=['POST'])
def upload():
    if 'file' not in request.files:
        return "No file part"
    
    file = request.files['file']
    if file.filename == '':
        return "No selected file"
    
    upload_file(file)
    return "File uploaded successfully"

if __name__ == '__main__':
    app.run(debug=True)