import os
from flask import Flask, request
from werkzeug.utils import secure_filename
import base64

app = Flask(__name__)

@app.route('/upload', methods=['POST'])
def upload_image():
    if 'image' not in request.files:
        return "No image part", 400
    
    file = request.files['image']
    
    if file.filename == '':
        return "No selected file", 400
    
    filename = secure_filename(file.filename)
    filepath = os.path.join('/tmp', filename)  # Save to a temporary directory
    file.save(filepath)

    with open(filepath, 'rb') as image_file:
        encoded_string = base64.b64encode(image_file.read()).decode('utf-8')
    
    return {'image_name': filename, 'base64_string': encoded_string}

if __name__ == '__main__':
    app.run(debug=True)