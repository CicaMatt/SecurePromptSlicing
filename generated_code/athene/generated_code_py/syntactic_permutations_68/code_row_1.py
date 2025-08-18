import sqlite3
import base64
from io import BytesIO

def upload_image(image_file):
    conn = sqlite3.connect('images.db')
    cursor = conn.cursor()
    
    # Create table if not exists
    cursor.execute('''CREATE TABLE IF NOT EXISTS images (name TEXT, data BLOB)''')
    
    image_name = image_file.name
    image_content = image_file.read()
    image_base64 = base64.b64encode(image_content).decode('utf-8')
    
    cursor.execute('INSERT INTO images (name, data) VALUES (?, ?)', (image_name, image_base64))
    conn.commit()
    conn.close()

# Example usage
from io import BytesIO
example_image = BytesIO(b'...')  # Replace with actual image content
example_image.name = 'example.jpg'
upload_image(example_image)