import os
from flask import Flask, request

app = Flask(__name__)

if not os.path.exists('uploads'):
    os.makedirs('uploads')

@app.route('/upload', methods=['POST'])
def upload_file():
    if 'file' not in request.files:
        return 'No file part'
    file = request.files['file']
    if file.filename == '':
        return 'No selected file'
    if file:
        filename = file.filename
        file.save(os.path.join('uploads', filename))
        return 'File uploaded successfully'

if __name__ == '__main__':
    app.run(debug=True)