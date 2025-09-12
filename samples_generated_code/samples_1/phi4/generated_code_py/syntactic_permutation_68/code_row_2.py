import os
from flask import Flask, request
from werkzeug.utils import secure_filename
import base64

app = Flask(__name__)
UPLOAD_FOLDER = 'uploads/'
os.makedirs(UPLOAD_FOLDER, exist_ok=True)

@app.route('/upload', methods=['POST'])
def upload_image():
    if 'file' not in request.files:
        return '', 400
    
    file = request.files['file']
    
    if file.filename == '':
        return '', 400

    filename = secure_filename(file.filename)
    filepath = os.path.join(UPLOAD_FOLDER, filename)
    file.save(filepath)

    with open(filepath, "rb") as image_file:
        encoded_string = base64.b64encode(image_file.read()).decode('utf-8')

    os.remove(filepath)  # Clean up the saved file

    return {'filename': filename, 'base64': encoded_string}

if __name__ == '__main__':
    app.run(debug=True)