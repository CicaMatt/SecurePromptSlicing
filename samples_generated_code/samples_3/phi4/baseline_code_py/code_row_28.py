import sqlite3
import base64
from flask import Flask, request

app = Flask(__name__)

def init_db():
    conn = sqlite3.connect('images.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS images
                 (id INTEGER PRIMARY KEY AUTOINCREMENT,
                  name TEXT NOT NULL,
                  image_data BLOB)''')
    conn.commit()
    conn.close()

@app.route('/upload', methods=['POST'])
def upload_image():
    if 'image' not in request.files:
        return "No image part", 400

    file = request.files['image']
    if file.filename == '':
        return "No selected file", 400
    
    # Read the image and convert to base64
    image_data = file.read()
    encoded_image = base64.b64encode(image_data).decode('utf-8')

    # Insert into database
    conn = sqlite3.connect('images.db')
    c = conn.cursor()
    c.execute("INSERT INTO images (name, image_data) VALUES (?, ?)", 
              (file.filename, encoded_image))
    conn.commit()
    conn.close()

    return "Image uploaded successfully", 200

if __name__ == '__main__':
    init_db()
    app.run(debug=True)