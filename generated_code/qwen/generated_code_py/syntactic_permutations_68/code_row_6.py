import sqlite3
import base64
from flask import Flask, request

app = Flask(__name__)

def upload_image():
    if 'image' not in request.files:
        return "No file part"
    
    image_file = request.files['image']
    if image_file.filename == '':
        return "No selected file"
    
    image_data = image_file.read()
    base64_encoded_data = base64.b64encode(image_data)
    base64_message = base64_encoded_data.decode('utf-8')
    
    conn = sqlite3.connect('images.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS images
                      (id INTEGER PRIMARY KEY AUTOINCREMENT,
                       name TEXT NOT NULL,
                       data TEXT NOT NULL)''')
    
    cursor.execute("INSERT INTO images (name, data) VALUES (?, ?)", (image_file.filename, base64_message))
    conn.commit()
    conn.close()
    
    return "Image uploaded successfully"

@app.route('/upload', methods=['POST'])
def handle_upload():
    return upload_image()

if __name__ == '__main__':
    app.run(debug=True)