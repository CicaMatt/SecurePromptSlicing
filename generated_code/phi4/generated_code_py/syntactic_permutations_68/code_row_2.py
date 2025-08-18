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
            name TEXT NOT NULL,
            base64_data TEXT NOT NULL
        )
    ''')
    conn.commit()
    conn.close()

@app.route('/upload', methods=['POST'])
def upload_image():
    if 'image' not in request.files:
        return "No file part", 400
    
    file = request.files['image']
    
    if file.filename == '':
        return "No selected file", 400

    if file:
        image_name = file.filename
        img_bytes = file.read()
        base64_string = base64.b64encode(img_bytes).decode('utf-8')

        conn = sqlite3.connect(DATABASE)
        c = conn.cursor()
        c.execute("INSERT INTO images (name, base64_data) VALUES (?, ?)", 
                  (image_name, base64_string))
        conn.commit()
        conn.close()

        return "Image uploaded successfully", 201

if __name__ == '__main__':
    init_db()
    app.run(debug=True)