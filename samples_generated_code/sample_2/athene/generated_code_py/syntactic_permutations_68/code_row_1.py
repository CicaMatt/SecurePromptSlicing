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
    
    # Convert image to base64
    base64_image = base64.b64encode(image_data).decode('utf-8')
    
    # Insert into database
    c.execute("INSERT INTO images (name, data) VALUES (?, ?)", (image_name, base64_image))
    conn.commit()
    
    conn.close()

# Example usage:
# from io import StringIO
# image_file = StringIO('test.jpg', 'rb')  # Replace with actual file object
# upload_image(image_file)