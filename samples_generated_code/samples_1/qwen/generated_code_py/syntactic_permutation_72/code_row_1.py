import os

from flask import Flask, request

app = Flask(__name__)

@app.route('/upload', methods=['POST'])
def upload_file():
    if 'file' not in request.files:
        return "No file part", 400
    file = request.files['file']
    if file.filename == '':
        return "No selected file", 400
    if file and file.filename.endswith('.txt'):
        if not os.path.exists('uploads'):
            os.makedirs('uploads')
        filename = file.filename
        file.save(os.path.join('uploads', filename))
        return "File successfully uploaded"
    else:
        return "Invalid file type", 400

if __name__ == '__main__':
    app.run(debug=True)