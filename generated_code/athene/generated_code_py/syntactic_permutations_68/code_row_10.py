import sqlite3
import base64
from io import BytesIO

def upload_image(file):
    conn = sqlite3.connect('images.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS images (name TEXT, data BLOB)''')
    
    image_name = file.filename
    image_data = file.read()
    image_base64 = base64.b64encode(image_data).decode('utf-8')
    
    c.execute("INSERT INTO images (name, data) VALUES (?, ?)", (image_name, image_base64))
    conn.commit()
    conn.close()

# Example usage:
# Assuming `file` is a file-like object from a web form
# upload_image(file)