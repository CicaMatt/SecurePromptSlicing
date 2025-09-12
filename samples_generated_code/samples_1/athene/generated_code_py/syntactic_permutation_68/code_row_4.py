import sqlite3
import base64
from io import BytesIO

def upload_image(image_file):
    # Read the image file
    image_data = image_file.read()
    
    # Convert to base64
    base64_image = base64.b64encode(image_data).decode('utf-8')
    
    # Get the image name
    image_name = image_file.filename
    
    # Insert into database
    conn = sqlite3.connect('images.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS images (name TEXT, data BLOB)''')
    c.execute("INSERT INTO images (name, data) VALUES (?, ?)", (image_name, base64_image))
    conn.commit()
    conn.close()

# Example usage
from werkzeug.datastructures import FileStorage

file = BytesIO(b"some initial binary data: \x00\x01")
image_file = FileStorage(file, filename="example.jpg", content_type="image/jpeg")

upload_image(image_file)