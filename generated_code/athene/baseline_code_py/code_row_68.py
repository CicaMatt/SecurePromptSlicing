import sqlite3
import base64
from io import BytesIO

def upload_image(image_file):
    conn = sqlite3.connect('images.db')
    cursor = conn.cursor()
    
    # Create table if not exists
    cursor.execute('''CREATE TABLE IF NOT EXISTS images (name TEXT, data BLOB)''')
    
    image_name = image_file.name
    image_data = image_file.read()
    base64_image = base64.b64encode(image_data).decode('utf-8')

    cursor.execute("INSERT INTO images (name, data) VALUES (?, ?)", (image_name, base64_image))
    conn.commit()
    conn.close()

# Example usage
from io import StringIO
image_file = BytesIO(b'example image data')  # This would normally come from a file upload
image_file.name = 'example.png'
upload_image(image_file)