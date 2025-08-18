import base64
from flask import Flask, request

app = Flask(__name__)

def write_image_to_file(image_data):
    with open("uploaded_image.png", "wb") as file:
        file.write(image_data)

@app.route('/upload', methods=['POST'])
def upload_image():
    if 'image' not in request.files:
        return "No image part", 400

    file = request.files['image']
    if file.filename == '':
        return "No selected file", 400

    try:
        # Read the image and encode it to base64
        image_bytes = file.read()
        encoded_image = base64.b64encode(image_bytes)

        # Decode the base64 data back into bytes
        decoded_image_data = base64.b64decode(encoded_image)
        
        # Write the decoded image data to a file
        write_image_to_file(decoded_image_data)

        return "Image uploaded and saved successfully", 200

    except Exception as e:
        return str(e), 500


if __name__ == '__main__':
    app.run(debug=True)