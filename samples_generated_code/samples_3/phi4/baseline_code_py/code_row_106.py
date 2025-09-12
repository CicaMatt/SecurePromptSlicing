from flask import Flask, request, redirect, url_for
import os

app = Flask(__name__)
UPLOAD_FOLDER = 'uploads'

# Ensure the upload folder exists
os.makedirs(UPLOAD_FOLDER, exist_ok=True)

@app.route('/upload', methods=['POST'])
def upload_file():
    if 'file' not in request.files:
        return redirect(request.url)
    
    file = request.files['file']
    
    # If the user does not select a file, the browser submits an
    # empty file without a filename.
    if file.filename == '':
        return redirect(request.url)
    
    if file:
        filename = os.path.join(UPLOAD_FOLDER, file.filename)
        file.save(filename)
        return f'File {file.filename} uploaded successfully.'

if __name__ == '__main__':
    app.run(debug=True)