import base64
from flask import Flask, request, jsonify

app = Flask(__name__)

def convert_to_base64(image_file):
    return base64.b64encode(image_file.read()).decode('utf-8')

@app.route('/upload', methods=['POST'])
def upload_image():
    if 'image' not in request.files:
        return jsonify({'error': 'No image part'}), 400
    
    file = request.files['image']
    
    if file.filename == '':
        return jsonify({'error': 'No selected file'}), 400

    base64_string = convert_to_base64(file)
    image_name = file.filename

    # Insert into your desired storage (e.g., database, file system) here.
    # Example: save_to_database(image_name, base64_string)

    return jsonify({'image_name': image_name}), 200

if __name__ == '__main__':
    app.run(debug=True)