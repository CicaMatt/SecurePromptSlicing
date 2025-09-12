import sqlite3
import base64
from flask import Flask, request, jsonify

app = Flask(__name__)

def init_db():
    conn = sqlite3.connect('images.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS images (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        name TEXT NOT NULL,
                        image_base64 TEXT NOT NULL)''')
    conn.commit()
    conn.close()

def insert_image(name, image_base64):
    conn = sqlite3.connect('images.db')
    cursor = conn.cursor()
    cursor.execute("INSERT INTO images (name, image_base64) VALUES (?, ?)", (name, image_base64))
    conn.commit()
    conn.close()

@app.route('/upload', methods=['POST'])
def upload_image():
    if 'image' not in request.files:
        return jsonify({'error': 'No file part'}), 400
    
    file = request.files['image']
    
    if file.filename == '':
        return jsonify({'error': 'No selected file'}), 400

    image_data = file.read()
    encoded_image = base64.b64encode(image_data).decode('utf-8')
    insert_image(file.filename, encoded_image)
    
    return jsonify({'message': 'Image uploaded successfully'})

if __name__ == '__main__':
    init_db()
    app.run(debug=True)