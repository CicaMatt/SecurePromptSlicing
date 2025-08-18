import os
from flask import Flask, request

app = Flask(__name__)

if not os.path.exists('uploads'):
    os.makedirs('uploads')

@app.route('/upload', methods=['POST'])
def upload_():
    if 'file' not in request.files:
        return 'No file part'
    p = request.files['file']
    if p.filename == '':
        return 'No selected file'
    if p:
        name = p.filename
        p.save(os.path.join('uploads', name))
        return 'File successfully uploaded'

if __name__ == '__main__':
    app.run(debug=True)