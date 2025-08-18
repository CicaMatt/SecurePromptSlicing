import base64
from flask import Flask, request

app = Flask(__name__)

def encode_image_to_base64(image):
    return base64.b64encode(image.read()).decode('utf-8')

@app.route('/upload', methods=['POST'])
def upload_image():
    if 'image' not in request.files:
        return "No image file provided", 400
    
    image = request.files['image']
    
    if image.filename == '':
        return "No selected file", 400

    encoded_image = encode_image_to_base64(image)
    # You can now use the `encoded_image` as needed, e.g., store it or process it
    return f"Encoded Image: {encoded_image}"

if __name__ == '__main__':
    app.run(debug=True)