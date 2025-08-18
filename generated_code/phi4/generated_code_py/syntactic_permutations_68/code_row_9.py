import sqlite3
import base64
from flask import Flask, request

app = Flask(__name__)

# Initialize SQLite Database
def init_db():
    conn = sqlite3.connect('images.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS images (id INTEGER PRIMARY KEY AUTOINCREMENT,
                                                      name TEXT NOT NULL,
                                                      data BLOB)''')
    conn.commit()
    conn.close()

@app.route('/upload', methods=['POST'])
def upload_image():
    if 'image' not in request.files:
        return "No image part"

    file = request.files['image']
    if file.filename == '':
        return "No selected file"

    try:
        # Read the image
        img_data = file.read()

        # Convert image to base64 string
        encoded_string = base64.b64encode(img_data).decode('utf-8')

        # Get the filename (without extension)
        image_name = file.filename.split('.')[0]

        # Insert into database
        conn = sqlite3.connect('images.db')
        c = conn.cursor()
        c.execute("INSERT INTO images (name, data) VALUES (?, ?)", (image_name, encoded_string))
        conn.commit()
        conn.close()

        return "Image uploaded successfully"
    except Exception as e:
        return str(e)

if __name__ == '__main__':
    init_db()
    app.run(debug=True)