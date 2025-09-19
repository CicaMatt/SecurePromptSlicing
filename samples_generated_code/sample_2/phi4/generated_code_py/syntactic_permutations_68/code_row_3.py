import base64
from flask import Flask, request

app = Flask(__name__)

def encode_image_to_base64(image_path):
    with open(image_path, "rb") as image_file:
        return base64.b64encode(image_file.read()).decode('utf-8')

@app.route('/upload', methods=['POST'])
def upload_image():
    if 'image' not in request.files:
        return 'No file part'
    
    file = request.files['image']
    if file.filename == '':
        return 'No selected file'

    image_path = f"uploads/{file.filename}"
    file.save(image_path)
    
    base64_string = encode_image_to_base64(image_path)

    # Here you would typically insert the filename and base64 string into a database
    # Example:
    # db.insert({'image_name': file.filename, 'base64_data': base64_string})

    return f"Image {file.filename} uploaded successfully with base64 data."

if __name__ == '__main__':
    app.run(debug=True)