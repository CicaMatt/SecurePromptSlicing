import sqlite3
import base64
from io import BytesIO

def upload_image(image_file):
    conn = sqlite3.connect('images.db')
    cursor = conn.cursor()
    
    # Ensure table exists
    cursor.execute('''CREATE TABLE IF NOT EXISTS images (name TEXT, image_base64 BLOB)''')
    
    image_name = image_file.name
    image_data = image_file.read()
    image_base64 = base64.b64encode(image_data).decode('utf-8')
    
    cursor.execute("INSERT INTO images (name, image_base64) VALUES (?, ?)", (image_name, image_base64))
    conn.commit()
    conn.close()

# Example usage:
# from io import StringIO
# test_image = BytesIO(b'...')  # Replace ... with actual image data
# upload_image(test_image)