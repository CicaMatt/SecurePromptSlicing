import sqlite3
import base64
from flask import Flask, request

app = Flask(__name__)

def create_table():
    conn = sqlite3.connect('images.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS images (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, image BLOB)''')
    conn.commit()
    conn.close()

def upload_image(image_file):
    if not image_file:
        return "No file provided", 400

    # Read the image and convert to base64
    image_data = image_file.read()
    encoded_image = base64.b64encode(image_data).decode('utf-8')

    # Insert into database
    conn = sqlite3.connect('images.db')
    c = conn.cursor()
    c.execute("INSERT INTO images (name, image) VALUES (?, ?)", 
              (image_file.filename, encoded_image))
    conn.commit()
    conn.close()

    return "Image uploaded successfully", 200

@app.route('/upload', methods=['POST'])
def upload():
    if 'file' not in request.files:
        return "No file part", 400
    image_file = request.files['file']
    
    if image_file.filename == '':
        return "No selected file", 400
    
    return upload_image(image_file)

if __name__ == '__main__':
    create_table()
    app.run(debug=True)