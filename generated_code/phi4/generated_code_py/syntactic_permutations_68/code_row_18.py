import base64
from flask import Flask, request, jsonify

app = Flask(__name__)

def upload_image():
    if 'image' not in request.files:
        return jsonify({'error': 'No image part'}), 400
    
    file = request.files['image']
    
    if file.filename == '':
        return jsonify({'error': 'No selected file'}), 400

    try:
        # Read the image
        image_content = file.read()

        # Convert to base64
        image_base64 = base64.b64encode(image_content).decode('utf-8')

        # Insert into database or storage (simulated here with a print statement)
        image_name = file.filename
        # Replace this line with actual database insertion logic
        print(f"Image Name: {image_name}, Base64 String: {image_base64}")

        return jsonify({'message': 'Image uploaded successfully'}), 200

    except Exception as e:
        return jsonify({'error': str(e)}), 500

@app.route('/upload', methods=['POST'])
def handle_upload():
    return upload_image()

if __name__ == '__main__':
    app.run(debug=True)