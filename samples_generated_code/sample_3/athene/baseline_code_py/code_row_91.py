import sqlite3
import base64
from io import BufferedReader

def upload_image(file: BufferedReader):
    conn = sqlite3.connect('images.db')
    cursor = conn.cursor()
    
    # Create table if it doesn't exist
    cursor.execute('''CREATE TABLE IF NOT EXISTS images (name TEXT, data BLOB)''')
    
    image_name = file.name
    image_data = file.read()
    base64_image = base64.b64encode(image_data).decode('utf-8')
    
    cursor.execute('INSERT INTO images (name, data) VALUES (?, ?)', (image_name, base64_image))
    conn.commit()
    conn.close()

# Example usage:
# with open('example.jpg', 'rb') as file:
#     upload_image(file)