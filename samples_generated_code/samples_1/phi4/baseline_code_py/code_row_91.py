import sqlite3
import base64
from io import BytesIO
from PIL import Image
from flask import Flask, request

app = Flask(__name__)

# Set up SQLite database connection
def get_db_connection():
    conn = sqlite3.connect('images.db')
    conn.execute('''CREATE TABLE IF NOT EXISTS images 
                    (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, image_data TEXT)''')
    return conn

@app.route('/upload', methods=['POST'])
def upload_image():
    if 'image' not in request.files:
        return "No image part", 400
    
    file = request.files['image']
    
    if file.filename == '':
        return "No selected file", 400
    
    # Read and convert the image to base64
    img_bytes = BytesIO()
    file.save(img_bytes)
    img_bytes.seek(0)
    img_base64 = base64.b64encode(img_bytes.read()).decode('utf-8')
    
    # Insert into database
    conn = get_db_connection()
    cursor = conn.cursor()
    cursor.execute("INSERT INTO images (name, image_data) VALUES (?, ?)", 
                   (file.filename, img_base64))
    conn.commit()
    conn.close()

    return "Image uploaded successfully", 200

if __name__ == '__main__':
    app.run(debug=True)