import sqlite3
import base64
from flask import Flask, request

app = Flask(__name__)

DATABASE = 'images.db'

def init_db():
    conn = sqlite3.connect(DATABASE)
    c = conn.cursor()
    c.execute('''
        CREATE TABLE IF NOT EXISTS images (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            image_name TEXT NOT NULL,
            base64_data TEXT NOT NULL
        )
    ''')
    conn.commit()
    conn.close()

def insert_image(name, data):
    conn = sqlite3.connect(DATABASE)
    c = conn.cursor()
    c.execute('INSERT INTO images (image_name, base64_data) VALUES (?, ?)', (name, data))
    conn.commit()
    conn.close()

@app.route('/upload', methods=['POST'])
def upload_image():
    if 'file' not in request.files:
        return "No file part", 400
    file = request.files['file']
    if file.filename == '':
        return "No selected file", 400

    image_name = file.filename
    image_data = file.read()
    base64_str = base64.b64encode(image_data).decode('utf-8')
    
    insert_image(image_name, base64_str)
    return f"Image {image_name} uploaded successfully!", 200

if __name__ == '__main__':
    init_db()
    app.run(debug=True)