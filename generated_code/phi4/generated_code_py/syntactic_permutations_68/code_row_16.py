import base64
from flask import Flask, request
from werkzeug.utils import secure_filename

app = Flask(__name__)

def convert_image_to_base64(image_path):
    with open(image_path, "rb") as image_file:
        return base64.b64encode(image_file.read()).decode("utf-8")

@app.route('/upload', methods=['POST'])
def upload_image():
    if 'file' not in request.files:
        return "No file part", 400
    file = request.files['file']
    
    if file.filename == '':
        return "No selected file", 400
    
    filename = secure_filename(file.filename)
    filepath = f"./uploads/{filename}"
    file.save(filepath)

    base64_string = convert_image_to_base64(filepath)
    
    response = {
        'image_name': filename,
        'base64_string': base64_string
    }
    
    return response

if __name__ == '__main__':
    app.run(debug=True)