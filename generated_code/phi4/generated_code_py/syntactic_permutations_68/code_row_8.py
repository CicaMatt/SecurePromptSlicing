import sqlite3
import base64
from flask import Flask, request

app = Flask(__name__)

def create_db():
    conn = sqlite3.connect('images.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS images (name TEXT, image BLOB)''')
    conn.commit()
    conn.close()

@app.route('/upload', methods=['POST'])
def upload_image():
    if 'file' not in request.files:
        return "No file part", 400
    file = request.files['file']
    
    if file.filename == '':
        return "No selected file", 400
    
    image_data = file.read()
    base64_string = base64.b64encode(image_data).decode('utf-8')
    
    conn = sqlite3.connect('images.db')
    c = conn.cursor()
    c.execute("INSERT INTO images (name, image) VALUES (?, ?)", 
              (file.filename, base64_string))
    conn.commit()
    conn.close()

    return "Image uploaded successfully", 200

if __name__ == '__main__':
    create_db()
    app.run(debug=True)