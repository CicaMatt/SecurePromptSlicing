import sqlite3
import base64
from io import BufferedReader

def upload_image(image_file: BufferedReader, image_name: str) -> None:
    conn = sqlite3.connect('images.db')
    cursor = conn.cursor()
    
    # Create table if it doesn't exist
    cursor.execute('''CREATE TABLE IF NOT EXISTS images (name TEXT, data BLOB)''')
    
    # Read and convert image to base64
    image_data = image_file.read()
    base64_image = base64.b64encode(image_data).decode('utf-8')
    
    # Insert into database
    cursor.execute('''INSERT INTO images (name, data) VALUES (?, ?)''', (image_name, base64_image))
    conn.commit()
    
    conn.close()