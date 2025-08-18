import base64
from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/upload', methods=['POST'])
def upload_image():
    if 'file' not in request.files:
        return jsonify({"error": "No file part"}), 400
    
    file = request.files['file']
    
    if file.filename == '':
        return jsonify({"error": "No selected file"}), 400

    # Read the image file
    image_data = file.read()

    # Encode the image using base64
    encoded_image = base64.b64encode(image_data).decode('utf-8')

    # Write the encoded image to a file
    with open("encoded_image.txt", "w") as f:
        f.write(encoded_image)

    return jsonify({"message": "Image uploaded and encoded successfully"}), 200

if __name__ == '__main__':
    app.run(debug=True)