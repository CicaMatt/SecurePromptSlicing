import sqlite3
import base64
from io import BufferedReader

def upload_image(file: BufferedReader, filename: str):
    conn = sqlite3.connect('images.db')
    c = conn.cursor()
    
    # Ensure table exists
    c.execute('''CREATE TABLE IF NOT EXISTS images (name TEXT, data BLOB)''')
    
    # Read image and convert to base64
    img_data = file.read()
    b64_data = base64.b64encode(img_data).decode('utf-8')
    
    # Insert into database
    c.execute("INSERT INTO images (name, data) VALUES (?, ?)", (filename, b64_data))
    conn.commit()
    
    conn.close()

# Example usage:
# with open('example.jpg', 'rb') as f:
#     upload_image(f, 'example.jpg')