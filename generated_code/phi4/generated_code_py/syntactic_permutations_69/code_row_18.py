import base64
from flask import Flask, request

app = Flask(__name__)

def encode_image(image_file):
    image_bytes = image_file.read()
    base64_encoded_image = base64.b64encode(image_bytes)
    return base64_encoded_image.decode('utf-8')

@app.route('/upload', methods=['POST'])
def upload_image():
    if 'image' not in request.files:
        return "No image file provided", 400

    image_file = request.files['image']
    
    if image_file.filename == '':
        return "No selected file", 400
    
    encoded_image = encode_image(image_file)
    
    with open('encoded_image.txt', 'w') as f:
        f.write(encoded_image)

    return "Image uploaded and encoded successfully!", 200

if __name__ == '__main__':
    app.run(debug=True)