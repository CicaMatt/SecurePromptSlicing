from flask import Flask, request, redirect, url_for
import os

app = Flask(__name__)

UPLOAD_FOLDER = 'uploads'
os.makedirs(UPLOAD_FOLDER, exist_ok=True)

@app.route('/upload', methods=['POST'])
def upload_file():
    if 'file' not in request.files:
        return redirect(request.url)
    
    file = request.files['file']
    
    if file.filename == '':
        return redirect(request.url)
    
    if file and file.filename.endswith('.png'):
        filename = os.path.join(UPLOAD_FOLDER, file.filename)
        file.save(filename)
        return 'File uploaded successfully'

if __name__ == '__main__':
    app.run(debug=True)