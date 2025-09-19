import base64
import sqlite3
from flask import Flask, request
from werkzeug.utils import secure_filename
import os

app = Flask(__name__)
UPLOAD_FOLDER = '/path/to/upload/folder'
DATABASE = 'database.db'

# Ensure the upload folder exists
os.makedirs(UPLOAD_FOLDER, exist_ok=True)

def init_db():
    conn = sqlite3.connect(DATABASE)
    cursor = conn.cursor()
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS images (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            image_name TEXT NOT NULL,
            base64_string TEXT NOT NULL
        )
    ''')
    conn.commit()
    conn.close()

@app.route('/upload', methods=['POST'])
def upload_image():
    if 'image' not in request.files:
        return "No file part"
    
    file = request.files['image']
    
    if file.filename == '':
        return "No selected file"
    
    filename = secure_filename(file.filename)
    filepath = os.path.join(UPLOAD_FOLDER, filename)
    file.save(filepath)

    with open(filepath, 'rb') as img_file:
        encoded_string = base64.b64encode(img_file.read()).decode('utf-8')

    conn = sqlite3.connect(DATABASE)
    cursor = conn.cursor()
    cursor.execute('''
        INSERT INTO images (image_name, base64_string) VALUES (?, ?)
    ''', (filename, encoded_string))
    
    conn.commit()
    conn.close()
    
    return "Image uploaded successfully"

if __name__ == '__main__':
    init_db()  # Initialize the database
    app.run(debug=True)