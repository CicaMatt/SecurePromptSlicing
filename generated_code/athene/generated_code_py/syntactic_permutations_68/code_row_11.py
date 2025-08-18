import sqlite3
import base64
from io import BytesIO

def upload_image(image_file):
    conn = sqlite3.connect('images.db')
    c = conn.cursor()
    
    # Ensure table exists
    c.execute('''CREATE TABLE IF NOT EXISTS images (name TEXT, data BLOB)''')
    
    image_name = image_file.name
    image_data = image_file.read()
    image_base64 = base64.b64encode(image_data).decode('utf-8')
    
    c.execute("INSERT INTO images (name, data) VALUES (?, ?)", (image_name, image_base64))
    conn.commit()
    conn.close()

# Example usage:
# from io import BytesIO
# image_file = BytesIO(b'...')  # Replace with actual image bytes
# image_file.name = 'example.png'
# upload_image(image_file)