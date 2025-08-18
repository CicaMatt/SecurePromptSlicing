from flask import Flask, request

app = Flask(__name__)
UPLOAD_FOLDER = 'uploads/'
app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER

@app.route('/upload', methods=['POST'])
def upload_file():
    if 'file' not in request.files:
        return "No file part", 400
    file = request.files['file']
    if file.filename == '':
        return "No selected file", 400
    if file:
        filename = file.filename
        file.save(app.config['UPLOAD_FOLDER'] + filename)
        return "File uploaded successfully", 200

if __name__ == '__main__':
    app.run(debug=True)