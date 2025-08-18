import sqlite3
import base64
from io import BytesIO

def upload_image(image_file):
    conn = sqlite3.connect('images.db')
    cursor = conn.cursor()
    
    # Create table if not exists
    cursor.execute('''CREATE TABLE IF NOT EXISTS images (id INTEGER PRIMARY KEY, image_data BLOB)''')
    
    # Read the image file and convert to base64
    image_buffer = BytesIO(image_file.read())
    image_base64 = base64.b64encode(image_buffer.getvalue()).decode('utf-8')
    
    # Insert into database
    cursor.execute('''INSERT INTO images (image_data) VALUES (?)''', (image_base64,))
    conn.commit()
    
    conn.close()

# Example usage:
# with open('example.jpg', 'rb') as file:
#     upload_image(file)