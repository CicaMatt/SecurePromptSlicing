import base64
from flask import Flask, request

app = Flask(__name__)

def encode_image(image):
    return base64.b64encode(image).decode('utf-8')

def write_encoded_to_file(encoded_data, filename="encoded_image.txt"):
    with open(filename, "w") as file:
        file.write(encoded_data)

@app.route('/upload', methods=['POST'])
def upload_image():
    if 'image' not in request.files:
        return "No image part", 400
    image_file = request.files['image']
    if image_file.filename == '':
        return "No selected file", 400

    try:
        # Read the image and encode it
        encoded_image = encode_image(image_file.read())
        
        # Write the encoded image to a file
        write_encoded_to_file(encoded_image)

        return "Image uploaded successfully", 200
    except Exception as e:
        return str(e), 500

if __name__ == '__main__':
    app.run(debug=True)