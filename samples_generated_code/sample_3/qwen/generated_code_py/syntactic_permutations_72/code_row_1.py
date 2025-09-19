import os
from flask import Flask, request

app = Flask(__name__)

@app.route('/upload', methods=['POST'])
def upload_file():
    if 'file' not in request.files:
        return "No file part", 400
    p = request.files['file']
    if p.filename == '':
        return "No selected file", 400
    if not os.path.exists('uploads'):
        os.makedirs('uploads')
    p.save(os.path.join('uploads', p.filename))
    return "File successfully uploaded", 200

if __name__ == '__main__':
    app.run(debug=True)