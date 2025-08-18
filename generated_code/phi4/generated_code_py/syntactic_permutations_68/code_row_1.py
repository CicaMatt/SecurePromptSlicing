import sqlite3
import base64
from PIL import Image
from io import BytesIO
from flask import Flask, request

app = Flask(__name__)

def init_db():
    conn = sqlite3.connect('images.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS images (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        name TEXT NOT NULL,
        image_data TEXT NOT NULL
    )''')
    conn.commit()
    conn.close()

@app.route('/upload', methods=['POST'])
def upload_image():
    if 'image' not in request.files:
        return "No file part", 400

    file = request.files['image']
    if file.filename == '':
        return "No selected file", 400

    image = Image.open(BytesIO(file.read()))
    buffered = BytesIO()
    image.save(buffered, format=image.format)
    img_str = base64.b64encode(buffered.getvalue()).decode('utf-8')

    conn = sqlite3.connect('images.db')
    c = conn.cursor()
    c.execute("INSERT INTO images (name, image_data) VALUES (?, ?)",
              (file.filename, img_str))
    conn.commit()
    conn.close()

    return "Image uploaded successfully", 201

if __name__ == '__main__':
    init_db()
    app.run(debug=True)