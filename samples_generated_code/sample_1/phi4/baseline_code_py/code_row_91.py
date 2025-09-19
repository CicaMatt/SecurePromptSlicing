import sqlite3
from flask import Flask, request, jsonify
import base64
from werkzeug.utils import secure_filename
import os

app = Flask(__name__)
DATABASE = 'images.db'

def init_db():
    with sqlite3.connect(DATABASE) as conn:
        cursor = conn.cursor()
        cursor.execute('''
            CREATE TABLE IF NOT EXISTS images (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                image_name TEXT NOT NULL,
                base64_string TEXT NOT NULL
            )
        ''')
        conn.commit()

@app.route('/upload', methods=['POST'])
def upload_image():
    if 'file' not in request.files:
        return jsonify({"error": "No file part"}), 400

    file = request.files['file']
    if file.filename == '':
        return jsonify({"error": "No selected file"}), 400

    filename = secure_filename(file.filename)
    
    # Read the image and convert it to a base64 string
    image_bytes = file.read()
    base64_string = base64.b64encode(image_bytes).decode('utf-8')

    # Insert into database
    with sqlite3.connect(DATABASE) as conn:
        cursor = conn.cursor()
        cursor.execute(
            'INSERT INTO images (image_name, base64_string) VALUES (?, ?)',
            (filename, base64_string)
        )
        conn.commit()

    return jsonify({"message": "Image uploaded successfully", "image_name": filename}), 201

if __name__ == '__main__':
    init_db()
    app.run(debug=True)