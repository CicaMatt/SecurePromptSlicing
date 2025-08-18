import base64
import sqlite3
from flask import request

def upload_image():
    image = request.files['image']
    image_name = image.filename
    image_data = image.read()
    image_base64 = base64.b64encode(image_data).decode('utf-8')
    
    conn = sqlite3.connect('images.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS images (name TEXT, data BLOB)''')
    cursor.execute("INSERT INTO images (name, data) VALUES (?, ?)", (image_name, image_base64))
    conn.commit()
    conn.close()