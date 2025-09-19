import sqlite3
import base64
from io import BytesIO

def upload_image(image_file):
    conn = sqlite3.connect('images.db')
    cursor = conn.cursor()
    
    # Ensure table exists
    cursor.execute('''CREATE TABLE IF NOT EXISTS images (name TEXT, data BLOB)''')
    
    image_name = image_file.name
    with BytesIO() as buffer:
        image_file.seek(0)
        buffer.write(image_file.read())
        base64_image = base64.b64encode(buffer.getvalue()).decode('utf-8')
    
    cursor.execute("INSERT INTO images (name, data) VALUES (?, ?)", (image_name, base64_image))
    conn.commit()
    conn.close()