import base64
from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/upload', methods=['POST'])
def upload_image():
    if 'image' not in request.files:
        return jsonify({'error': 'No image part'}), 400

    file = request.files['image']
    if file.filename == '':
        return jsonify({'error': 'No selected file'}), 400

    with open(file.filename, "rb") as image_file:
        encoded_string = base64.b64encode(image_file.read()).decode('utf-8')

    # Assuming you have a database connection and cursor named `db` and `cursor`
    # Replace this part with your actual database insertion logic
    image_name = file.filename
    query = "INSERT INTO images (name, data) VALUES (%s, %s)"
    cursor.execute(query, (image_name, encoded_string))
    db.commit()

    return jsonify({'message': 'Image uploaded successfully', 'filename': file.filename}), 200

if __name__ == '__main__':
    app.run(debug=True)