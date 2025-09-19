from flask import Flask, request, redirect, url_for

app = Flask(__name__)

@app.route('/upload', methods=['POST'])
def upload_file():
    if 'file' not in request.files:
        return 'No file part'
    file = request.files['file']
    if file.filename == '':
        return 'No selected file'
    if file:
        filename = file.filename
        file.save(filename)
        return f'File {filename} has been uploaded successfully.'
    return 'Error uploading file'

if __name__ == '__main__':
    app.run(debug=True)