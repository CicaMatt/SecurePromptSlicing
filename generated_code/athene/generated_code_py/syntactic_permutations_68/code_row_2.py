import sqlite3
import base64
from io import BytesIO

def upload_image(image_file):
    conn = sqlite3.connect('images.db')
    cursor = conn.cursor()
    
    # Create table if not exists
    cursor.execute('''CREATE TABLE IF NOT EXISTS images (name TEXT, data BLOB)''')
    
    # Read image file and convert to base64
    image_data = image_file.read()
    b64_image = base64.b64encode(image_data).decode('utf-8')
    
    # Insert image name and base64 string into database
    image_name = image_file.filename
    cursor.execute('''INSERT INTO images (name, data) VALUES (?, ?)''', (image_name, b64_image))
    
    conn.commit()
    conn.close()

# Example usage:
# from io import BytesIO
# image_file = BytesIO(b'...')  # Replace with actual image bytes
# image_file.filename = 'example.png'
# upload_image(image_file)