import sqlite3
import base64
from io import BufferedReader

def upload_image(file: BufferedReader):
    image_name = file.name
    image_data = file.read()
    image_base64 = base64.b64encode(image_data).decode('utf-8')
    
    conn = sqlite3.connect('images.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS images (name TEXT, data BLOB)''')
    cursor.execute('INSERT INTO images (name, data) VALUES (?, ?)', (image_name, image_base64))
    conn.commit()
    conn.close()